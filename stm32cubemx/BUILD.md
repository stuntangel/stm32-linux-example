cd /home/ryan/STMicroelectronics/STM32Cube/STM32CubeProgrammer/bin
STM32_Programmer_CLI -c port=SWD -e all -w ~/STM32CubeIDE/workspace_1.18.0/bootloaderfinal/Debug/bootloaderfinal.bin -v -ob displ -rst
steam-run ./ST-LINK_gdbserver --verify -c config.txt
cd ~/Documents/STM
