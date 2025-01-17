#!/bin/false
# This file is part of Espruino, a JavaScript interpreter for Microcontrollers
#
# Copyright (C) 2013 Gordon Williams <gw@pur3.co.uk>
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# ----------------------------------------------------------------------------------------
# This file contains information for a specific board - the available pins, and where LEDs,
# Buttons, and other in-built peripherals are. It is used to build documentation as well
# as various source and header files for Espruino.
# ----------------------------------------------------------------------------------------

import pinutils;

info = {
 'name' : "PineTime40",
 'link' :  [ "https://www.joaquim.org/pinetime-upgrade-board/" ], 
 'default_console' : "EV_SERIAL1", 
 #'default_console' : "EV_TERMINAL", 
 'default_console_tx' : "D25",
 'default_console_rx' : "D14",
 'default_console_baudrate' : "115200",
 #'default_console' : "EV_BLUETOOTH",
  
 'variables' : 7500, # How many variables are allocated for Espruino to use. RAM will be overflowed if this number is too high and code won't compile.
                      # Currently leaves around 38k of free stack - *loads* more than we need
 'io_buffer_size' : 512, # How big is the input buffer (in 4 byte words). Default on nRF52 is 256
 'bootloader' : 1,
 'binary_name' : 'espruino_pinetime40.hex',
 'build' : {
   'optimizeflags' : '-Os -s -z noseparate-code',
   'libraries' : [
     'BLUETOOTH',
     'LVGL',
     #'JIT' # JIT compiler enabled
   ],
   'makefile' : [
     'DEFINES+=-DPINETIME40 -DESPR_HWVERSION=2',
     'DEFINES+=-DNRF_DFU_BLE_ADV_NAME=\'"DFU PineTime40"\'',
     'DEFINES+=-DESPR_USE_SPI3',     
     'DEFINES+=-DCONFIG_NFCT_PINS_AS_GPIOS', # Allow the reset pin to work
     'DEFINES+=-DBLUETOOTH_NAME_PREFIX=\'"Espruino PineTime40"\'',
     'DEFINES+=-DNRF_SDH_BLE_GATT_MAX_MTU_SIZE=131', # 23+x*27 rule as per https://devzone.nordicsemi.com/f/nordic-q-a/44825/ios-mtu-size-why-only-185-bytes
     'DEFINES += -DCENTRAL_LINK_COUNT=2 -DNRF_SDH_BLE_CENTRAL_LINK_COUNT=2', # allow two outgoing connections at once
     'LDFLAGS += -Xlinker --defsym=LD_APP_RAM_BASE=0x3660', # set RAM base to match MTU=131 + CENTRAL_LINK_COUNT=2
     'DEFINES+=-DCUSTOM_GETBATTERY=jswrap_pinetime40_getBattery',
     'DEFINES+=-DSPIFLASH_READ2X', # Read SPI flash at 2x speed using MISO and MOSI for IO
     'DEFINES+=-DDUMP_IGNORE_VARIABLES=\'"g\\0"\'',
     'DEFINES+=-DLVGL',
     'DEFINES+=-DNO_DUMP_HARDWARE_INITIALISATION', # don't dump hardware init - not used and saves 1k of flash 
     'DEFINES+=-DESPR_NO_LINE_NUMBERS=1', # we execute mainly from flash, so line numbers can be worked out
     'INCLUDE += -I$(ROOT)/libs/pinetime40 -I$(ROOT)/libs/pinetime40/bma400 -I$(ROOT)/libs/misc',  
     'WRAPPERSOURCES += libs/pinetime40/jswrap_pinetime40.c',

     'SOURCES += libs/pinetime40/bma400/bma400.c',     

     'SOURCES += libs/lvgl/fonts/ui_font_BigNumbers.c',
     'SOURCES += libs/lvgl/fonts/ui_font_Icons32.c',
     'SOURCES += libs/lvgl/fonts/ui_font_Numbers42.c',
     'SOURCES += libs/lvgl/fonts/ui_font_Numbers64.c',
     'SOURCES += libs/lvgl/fonts/ui_font_OpenSans22.c',
     'SOURCES += libs/lvgl/fonts/ui_font_OpenSans22Bold.c',

     'JSMODULESOURCES += libs/js/pinetime40/locale.min.js',
     'JSMODULESOURCES += libs/js/banglejs/locale.min.js',

     'DFU_SETTINGS=--application-version 0xff --hw-version 52 --sd-req 0x8C,0x91,0xA9,0xAE,0xB6,0xB7',
     'DFU_PRIVATE_KEY=targets/nrf5x_dfu/dfu_private_key_40.pem',
     'DEFINES += -DNRF_BOOTLOADER_NO_WRITE_PROTECT=1', # By default the bootloader protects flash. Avoid this (a patch for NRF_BOOTLOADER_NO_WRITE_PROTECT must be applied first)
     'DEFINES += -DBUTTONPRESS_TO_REBOOT_BOOTLOADER',
     'BOOTLOADER_SETTINGS_FAMILY=NRF52840',
     'DEFINES += -DESPR_BOOTLOADER_SPIFLASH', # Allow bootloader to flash direct from SPI flash

     'NRF_SDK15_3=1',
     'ESPR_BLUETOOTH_ANCS=1' # Enable ANCS (Apple notifications) support
   ]
 }
};


chip = {
  'part' : "NRF52840",
  'family' : "NRF52",
  'package' : "AQFN73",
  'ram' : 256,
  'flash' : 1024,
  'speed' : 64,
  'usart' : 2,
  'spi' : 1,
  'i2c' : 1,
  'adc' : 1,
  'dac' : 0,
  'saved_code' : {
    'address' : 0x60000000, # put this in external spiflash (see below)
    'page_size' : 4096,
    'pages' : 1024, # Entire 4MB of external flash
    'flash_available' : 512 - ((31 + 8 + 2)*4) # Softdevice uses 31 pages of flash, bootloader 8, FS 2. Each page is 4 kb.
  },
};

# p0.1 = 1
# p1.1 = 33
#

devices = {
  'BTN1' : { 'pin' : 'D34', 'pinstate' : 'IN_PULLUP' }, # Pin negated in software  
  'LED1' : { 'pin' : 'D36', 'novariable' : True}, 
  'LCD' : {
            'width' : 240, 'height' : 240, 
            'bpp' : 16,
            'bitrate': 32000000,
            'controller' : 'st7789v',
            'pin_dc' : 'D6',
            'pin_cs' : 'D8',
            'pin_rst' : 'D11',
            'pin_sck' : 'D41',
            'pin_mosi' : 'D12',
            'pin_bl' : 'D36', # backlight pwm
          },
  'TOUCH' : {
            'device' : 'CST816S', 'addr' : 0x15,
            'pin_sda' : 'D39',
            'pin_scl' : 'D38',
            'pin_rst' : 'D13',
            'pin_irq' : 'D15'
          },
  'VIBRATE' : { 'pin' : 'D4' },
  'BAT' : {
            'pin_charging' : 'D29', # active low, input pullup
            'pin_voltage' : 'D31'
          },
  'HEARTRATE' : {
            'device' : 'HRS3300', 'addr' : 0x44,            
            'pin_sda' : 'D39', 
            'pin_scl' : 'D38'
          },
  'ACCEL' : {
            'device' : 'BMA400', 'addr' : 0x14,
            'pin_sda' : 'D39',
            'pin_scl' : 'D38',
            'pin_int' : 'D33'
          },
  'SPIFLASH' : {
            'pin_cs' : 'D17',
            'pin_sck' : 'D22',
            'pin_mosi' : 'D20', # D0
            'pin_miso' : 'D24', # D1
            'pin_wp' : 'D32', # D2
            'pin_rst' : 'D16', # D3
            'size' : 4096*1024, # 4MB
            'memmap_base' : 0x60000000 # map into the address space (in software)
          }
};

# left-right, or top-bottom order
board = {
};


def get_pins():
  pins = pinutils.generate_pins(0,47) # 48 General Purpose I/O Pins.
  pinutils.findpin(pins, "PD0", True)["functions"]["XL1"]=0;
  pinutils.findpin(pins, "PD1", True)["functions"]["XL2"]=0;
  pinutils.findpin(pins, "PD31", True)["functions"]["ADC1_IN7"]=0;
  # Make buttons and LEDs negated
  pinutils.findpin(pins, "PD4", True)["functions"]["NEGATED"]=0;
  pinutils.findpin(pins, "PD36", True)["functions"]["NEGATED"]=0;

  # everything is non-5v tolerant
  for pin in pins:
    pin["functions"]["3.3"]=0;
  #The boot/reset button will function as a reset button in normal operation. Pin reset on PD21 needs to be enabled on the nRF52832 device for this to work.
  return pins
