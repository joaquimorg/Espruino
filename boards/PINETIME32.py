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
 'name' : "PineTime.js",
 'link' :  [ "https://www.pine64.org/pinetime/" ],
 #'espruino_page_link' : 'Bangle.js',
 #'default_console' : "EV_BLUETOOTH",
 'default_console' : "EV_SERIAL1",
 'default_console_tx' : "D11",
 'default_console_rx' : "D30",
 'default_console_baudrate' : "115200",

 'variables' : 3000, # How many variables are allocated for Espruino to use. RAM will be overflowed if this number is too high and code won't compile.
 'bootloader' : 1,
 'binary_name' : 'espruino_pinetime32.hex',
 'build' : {
   'optimizeflags' : '-Os',
   'libraries' : [
     'BLUETOOTH',
     'TERMINAL',
     'GRAPHICS',
     #'LCD_SPI',
     #'LCD_SPI_UNBUF',
     #'TENSORFLOW',
     #'JIT'
   ],
   'makefile' : [     
     #'BLACKLIST=boards/BANGLEJS.blocklist', # force some stuff to be removed to save space   
     #'DEFINES += -DESPR_HWVERSION=2',
     #'DEFINES += -DBANGLEJS_F18',
     'DEFINES += -DCONFIG_NFCT_PINS_AS_GPIOS', # Allow the reset pin to work
     #'DEFINES += -DESPR_HWVERSION=2 -DBANGLEJS -DBANGLEJS_Q3',
     #'DEFINES += -DESPR_DCDC_ENABLE', # Ensure DCDC converter is enabled
     'DEFINES += -DSPISENDMANY_BUFFER_SIZE=2048',
     'DEFINES += -DSPIFLASH_SHARED_SPI',
     'DEFINES += -DPINETIME',
     'USE_LCD_SPI_UNBUF=1',
     'USE_DEBUGGER=0',
     'DEFINES += -DUSE_LCD_ST7789V',
     'DEFINES += -DBUTTONPRESS_TO_REBOOT_BOOTLOADER',
     #'DEFINES += -DESPR_BOOTLOADER_SPIFLASH', # Allow bootloader to flash direct from SPI flash
     #'DEFINES += -DDFU_APP_DATA_RESERVED=0', # allow firmware updates right up to the amount of available flash
     'DEFINES += -DNRF_BLE_GATT_MAX_MTU_SIZE=53 -DNRF_BLE_MAX_MTU_SIZE=53', # increase MTU from default of 23
     'LDFLAGS += -Xlinker --defsym=LD_APP_RAM_BASE=0x2c40', # set RAM base to match MTU     
     #'DEFINES += -DCENTRAL_LINK_COUNT=2 -DNRF_SDH_BLE_CENTRAL_LINK_COUNT=2', # allow two outgoing connections at once  
     #'LDFLAGS += -Xlinker --defsym=LD_APP_RAM_BASE=0x3000', # set RAM base to match MTU=53 + CENTRAL_LINK_COUNT=2
     'DEFINES += -DBLUETOOTH_NAME_PREFIX=\'"PineTime.js"\'',
     'DEFINES += -DBLUETOOTH_ADVERTISING_INTERVAL=200', # since we don't care as much about ~20uA battery usage, raise this to make getting a connection faster
     #'ESPR_BLUETOOTH_ANCS=1', # Enable ANCS (Apple notifications) support
     'DEFINES += -DCUSTOM_GETBATTERY=jswrap_pinetime_getBattery',
     #'DEFINES += -DESPR_UNICODE_SUPPORT=1',
     #'DEFINES += -DESPR_NO_SOFTWARE_SERIAL=1',
     'DEFINES += -DDUMP_IGNORE_VARIABLES=\'"g\\0"\'',
     'DEFINES += -DESPR_GRAPHICS_INTERNAL=1',
     'DEFINES += -DUSE_FONT_6X8 -DGRAPHICS_PALETTED_IMAGES',
     'DEFINES += -DNO_DUMP_HARDWARE_INITIALISATION', # don't dump hardware init - not used and saves 1k of flash
     'DEFINES += -DESPR_NO_LINE_NUMBERS=1', # we execute mainly from flash, so line numbers can be worked out
     'DEFINES += -DAPP_TIMER_OP_QUEUE_SIZE=4', # Bangle.js accelerometer poll handler needs something else in queue size
     'DEFINES += -DNRF_DFU_BLE_ADV_NAME=\'"DFU PineTime"\'',
     'DFU_PRIVATE_KEY=targets/nrf5x_dfu/dfu_private_key.pem',
     'DFU_SETTINGS=--application-version 0xff --hw-version 52 --sd-req 0x8C,0x91',
     'INCLUDE += -I$(ROOT)/libs/pinetime -I$(ROOT)/libs/misc',
     'WRAPPERSOURCES += libs/pinetime/lcd_st7789v.c',
     'WRAPPERSOURCES += libs/pinetime/jswrap_pinetime.c',     
     #'WRAPPERSOURCES += libs/graphics/jswrap_font_12x20.c',
     #'WRAPPERSOURCES += libs/pinetime/jswrap_font_24.c',
     #'SOURCES += libs/misc/nmea.c',
     #'SOURCES += libs/misc/stepcount.c',
     #'SOURCES += libs/misc/heartrate.c',
     #'SOURCES += libs/misc/hrm_analog.c',
     'JSMODULESOURCES += libs/js/pinetime/locale.min.js',
     'JSMODULESOURCES += libs/js/banglejs/locale.min.js',
     'NRF_BL_DFU_INSECURE=1',
     #'LINKER_BOOTLOADER=targetlibs/nrf5x_12/nrf5x_linkers/banglejs_dfu.ld',
     'LINKER_BOOTLOADER=targetlibs/nrf5x_12/nrf5x_linkers/pinetime_dfu.ld',
     #'LINKER_ESPRUINO=targetlibs/nrf5x_12/nrf5x_linkers/banglejs_espruino.ld',
     'LINKER_ESPRUINO=targetlibs/nrf5x_12/nrf5x_linkers/pinetime_espruino.ld',
   ]
 }
};


chip = {
  'part' : "NRF52832",
  'family' : "NRF52",
  'package' : "QFN48",
  'ram' : 64,
  'flash' : 512,
  'speed' : 64,
  'usart' : 1,
  'spi' : 2, # hardware supports 1, but we don't use these
  'i2c' : 1, # hardware supports 1, but we don't use these
  'adc' : 1,
  'dac' : 0,
  #'saved_code' : {
  #  'address' : 0x60000000, # put this in external spiflash (see below)
  #  'page_size' : 4096,
  #  'pages' : 1024, # Entire 4MB of external flash
  #  'flash_available' : 512 - ((31 + 8 + 2)*4) # Softdevice uses 31 pages of flash, bootloader 8, FS 2. Each page is 4 kb.
  #},

  'saved_code' : {
    'address' : ((118 - 9) * 4096), # Bootloader takes pages 120-127, FS takes 118-119
    'page_size' : 4096,
    'pages' : 9,
    'flash_available' : 512 - ((31 + 8 + 2 + 9)*4) # Softdevice uses 31 pages of flash, bootloader 8, FS 2, code 10. Each page is 4 kb.
  },
};

devices = {
  'BTN1' : { 'pin' : 'D13', 'pinstate' : 'IN_PULLUP' },
  'LED1' : { 'pin' : 'D14', 'novariable':True },
  'VIBRATE' : { 'pin' : 'D16' },
  'LCD' : {
            'width' : 240, 'height' : 240, 'bpp' : 16,
            'controller' : 'st7789v',
            'pin_mosi' : 'D3',
            'pin_sck' : 'D2',
            'pin_cs' : 'D25',
            'pin_dc' : 'D18',
            'pin_rst' : 'D26',
            'pin_bl' : 'D14',
          },
  'TOUCH' : {
            'device' : 'CST816S', 'addr' : 0x15,
            'pin_sda' : 'D6',
            'pin_scl' : 'D7',
            'pin_rst' : 'D10',
            'pin_irq' : 'D28'
          },
  'BAT' : {
            'pin_charging' : 'D12', # active low, input pullup
            'pin_voltage' : 'D31'
          },
  #'HEARTRATE' : {
  #          'device' : 'analog',
  #          'pin_analog' : 'D29'
  #        },
  #'ACCEL' : {
  #          'device' : 'KX023', 'addr' : 0x1e,
  #          'pin_sda' : 'D15',
  #          'pin_scl' : 'D14'
  #        },
  #'SPIFLASH' : {
  #          'pin_cs' : 'D5',
  #          'pin_sck' : 'D2',
  #          'pin_mosi' : 'D3', 
  #          'pin_miso' : 'D4', 
  #          'size' : 4096*1024, # 4MB
  #          'memmap_base' : 0x60000000 # map into the address space (in software)
  #        },
};

# left-right, or top-bottom order
board = {
};

def get_pins():
  pins = pinutils.generate_pins(0,31) # 32 General Purpose I/O Pins.
  pinutils.findpin(pins, "PD0", True)["functions"]["XL1"]=0;
  pinutils.findpin(pins, "PD1", True)["functions"]["XL2"]=0;
  pinutils.findpin(pins, "PD2", True)["functions"]["ADC1_IN0"]=0;
  pinutils.findpin(pins, "PD3", True)["functions"]["ADC1_IN1"]=0;
  pinutils.findpin(pins, "PD4", True)["functions"]["ADC1_IN2"]=0;
  pinutils.findpin(pins, "PD5", True)["functions"]["ADC1_IN3"]=0;
  pinutils.findpin(pins, "PD28", True)["functions"]["ADC1_IN4"]=0;
  pinutils.findpin(pins, "PD29", True)["functions"]["ADC1_IN5"]=0;
  pinutils.findpin(pins, "PD30", True)["functions"]["ADC1_IN6"]=0;
  pinutils.findpin(pins, "PD31", True)["functions"]["ADC1_IN7"]=0;
  # negate buttons
  pinutils.findpin(pins, "PD16", True)["functions"]["NEGATED"]=0;
  pinutils.findpin(pins, "PD12", True)["functions"]["NEGATED"]=0;
  #pinutils.findpin(pins, "PD14", True)["functions"]["NEGATED"]=0;
  pinutils.findpin(pins, "PD13", True)["functions"]["NEGATED"]=0;
  

  # everything is non-5v tolerant
  for pin in pins:
    pin["functions"]["3.3"]=0;
  #The boot/reset button will function as a reset button in normal operation. Pin reset on PD21 needs to be enabled on the nRF52832 device for this to work.
  return pins
