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
 #'default_console' : "EV_SERIAL1",
 'default_console' : "EV_SERIAL1",
 'default_console_tx' : "D25",
 'default_console_rx' : "D14",
 'default_console_baudrate' : "115200",
 'variables' : 5000, # How many variables are allocated for Espruino to use. RAM will be overflowed if this number is too high and code won't compile.
                      # Currently leaves around 38k of free stack - *loads* more than we need
 #'io_buffer_size' : 512, # How big is the input buffer (in 4 byte words). Default on nRF52 is 256
 'bootloader' : 0,
 'binary_name' : 'espruino_%v_pinetime40.hex',
 'build' : {
   'optimizeflags' : '-Os',
   'libraries' : [
     'BLUETOOTH',
     'TERMINAL',
     'GRAPHICS',
     'LCD_SPI'
   ],
   'makefile' : [
     'DEFINES += -DPINETIME40',
    
     #'DEFINES+=-DESPR_USE_SPI3 -DSPISENDMANY_BUFFER_SIZE=240',
     'DEFINES+=-DCONFIG_NFCT_PINS_AS_GPIOS', # Allow the reset pin to work
     #'DEFINES+=-DBUTTONPRESS_TO_REBOOT_BOOTLOADER',
     'DEFINES+=-DBLUETOOTH_NAME_PREFIX=\'"Espruino PineTime40"\'',
     #'DEFINES+=-DCUSTOM_GETBATTERY=jswrap_banglejs_getBattery',
     'DEFINES+=-DDUMP_IGNORE_VARIABLES=\'"g\\0"\'',
     'DEFINES+=-DESPR_GRAPHICS_INTERNAL=1',
     'DEFINES+=-DUSE_FONT_6X8 -DGRAPHICS_PALETTED_IMAGES -DESPR_GRAPHICS_16BIT -DGRAPHICS_ANTIALIAS',
     'DEFINES+=-DNO_DUMP_HARDWARE_INITIALISATION', # don't dump hardware init - not used and saves 1k of flash 
     'INCLUDE += -I$(ROOT)/libs/pinetime40 -I$(ROOT)/libs/misc',
     #'JSMODULESOURCES += libs/js/graphical_menu.min.js',     
     'WRAPPERSOURCES += libs/pinetime40/jswrap_pinetime40.c',  
     'WRAPPERSOURCES += libs/graphics/jswrap_font_6x15.c',
     'WRAPPERSOURCES += libs/graphics/jswrap_font_12x20.c',

     'JSMODULESOURCES += libs/js/banglejs/locale.min.js',

     #'INCLUDE += -I$(ROOT)/libs/banglejs -I$(ROOT)/libs/misc',
     #'WRAPPERSOURCES += libs/banglejs/jswrap_bangle.c',
     #'WRAPPERSOURCES += libs/graphics/jswrap_font_6x15.c',
     #'WRAPPERSOURCES += libs/graphics/jswrap_font_12x20.c',
     #'SOURCES += libs/misc/unistroke.c',
     #'WRAPPERSOURCES += libs/misc/jswrap_unistroke.c',
     #'DEFINES += -DESPR_BANGLE_UNISTROKE=1',

     'NRF_SDK15=1',
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
  'LED1' : { 'pin' : 'D36', 'novariable':True}, 
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
            'pin_charging' : 'D29', # active low
            'pin_voltage' : 'D31'
          },
#  'HEARTRATE' : {
#            'device' : 'VC31', 'addr' : 0x33,            
#            'pin_sda' : 'D24', 
#            'pin_scl' : 'D32', 
#            'pin_en' : 'D21', 
#            'pin_int' : 'D22'
#          },
#  'ACCEL' : {
#            'device' : 'KX023', 'addr' : 0x1e,
#            'pin_sda' : 'D38',
#            'pin_scl' : 'D37'
#          },
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
  #pinutils.findpin(pins, "PD2", True)["functions"]["ADC1_IN0"]=0;
  #pinutils.findpin(pins, "PD3", True)["functions"]["ADC1_IN1"]=0;
  #pinutils.findpin(pins, "PD4", True)["functions"]["ADC1_IN2"]=0;
  #pinutils.findpin(pins, "PD5", True)["functions"]["ADC1_IN3"]=0;
  #pinutils.findpin(pins, "PD28", True)["functions"]["ADC1_IN4"]=0;
  #pinutils.findpin(pins, "PD29", True)["functions"]["ADC1_IN5"]=0;
  #pinutils.findpin(pins, "PD30", True)["functions"]["ADC1_IN6"]=0;
  pinutils.findpin(pins, "PD31", True)["functions"]["ADC1_IN7"]=0;
  # Make buttons and LEDs negated
  pinutils.findpin(pins, "PD34", True)["functions"]["NEGATED"]=0;
  pinutils.findpin(pins, "PD15", True)["functions"]["NEGATED"]=0;
  pinutils.findpin(pins, "PD29", True)["functions"]["NEGATED"]=0;
  pinutils.findpin(pins, "PD36", True)["functions"]["NEGATED"]=0;

  # everything is non-5v tolerant
  for pin in pins:
    pin["functions"]["3.3"]=0;
  #The boot/reset button will function as a reset button in normal operation. Pin reset on PD21 needs to be enabled on the nRF52832 device for this to work.
  return pins
