# Linux Guide to SMT32 for EE329
## Important Update
The original guide demonstrated how to install the arm gcc toolchain and issue commands by hand to compile, link, and flash. To create a streamlined, more reliable process where users can use the STM32CubeIDE, the toolchains have been properly packaged to resolve issues encountered when downloading the IDE from the company webpage. 
# New Guide:
To resolve issues encountered potentially by non-LFS distros, non-X11 DE, etc., the reproducible package manager nix should be installed
```
$ sh <(curl --proto '=https' --tlsv1.2 -L https://nixos.org/nix/install) --no-daemon
```
Then to install and run the STM32CubeIDE: 
```
cd stm32cubeide.nix
nix develop
stm32cubeide
```
To install the STM32CubeMX, which can be used to create projects:
```
cd stm32cubemx
nix develop
stm32cubemxapp
```
# Old Guide:
## Install 
Upon cloning repository, change all mentions of stm32_demo to your projects name by running the commands below. Ex:
```
git clone https://github.com/stuntangel/stm32-linux-example my_project
make rename
```
## Setup
ensure that gcc-arm-embedded-13 and st-flash are installed. Ex:
```
sudo apt-get install -y gcc-arm-embedded-13 st-flash
```
## Linking and creating object files 
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
