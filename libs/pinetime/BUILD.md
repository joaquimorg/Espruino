# build bootloader 
$make clean && RELEASE=1 BOARD=PINETIME32 BOOTLOADER=1 make

# build Espruino
$make clean && RELEASE=1 BOARD=PINETIME32 make

# build DFU
$make clean && RELEASE=1 BOARD=PINETIME32 DFU_UPDATE_BUILD=1 make



-- 
# send to pinetime 

#bootloader
> openocd.exe -c "tcl_port disabled" -c "gdb_port 3333" -c "telnet_port 4444" -f interface/stlink.cfg -c 'transport select hla_swd' -f target/nrf52.cfg -c "program bootloader_espruino_pinetime32.hex" -c reset -c shutdown

#softdevice
> openocd.exe -c "tcl_port disabled" -c "gdb_port 3333" -c "telnet_port 4444" -f interface/stlink.cfg -c 'transport select hla_swd' -f target/nrf52.cfg -c "program s132_nrf52_3.1.0_softdevice.hex" -c reset -c shutdown

#espruino
> openocd.exe -c "tcl_port disabled" -c "gdb_port 3333" -c "telnet_port 4444" -f interface/stlink.cfg -c 'transport select hla_swd' -f target/nrf52.cfg -c "program espruino_pinetime32.hex" -c reset -c shutdown