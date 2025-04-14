# Linux Guide to SMT32 for EE329
## Install 
Upon cloning repository, change all mentions of stm32_demo to your projects name. Running the script rename.sh will change the names of all files accordingly. Ex:
```
git clone https://github.com/stuntangel/stm32-linux-example my_project
make rename
```
## Setup
ensure that gcc-arm-embedded-13 and st-flash are installed. Ex:
```
sudo apt-get install -y gcc-arm-embedded-13 st-flash
```
##Linking and creating object files 
```
make link
```
## Compiling to .elf file
```
make compile
```
## Creating the .bin file
```
make elf_to_bin
```
## flashing the .bin file to STM32
```
make flash
```
## Debugging
note: if it complains that it can not write to the usb port, run (where 008 is the port mentioned in the error message):
```
sudo chmod o+w /dev/bus/usb/001/PORT
```
Additionally, make sure the USB port is seen on your computer (either /dev/ttyACM0 or /dev/ttyUSB0
