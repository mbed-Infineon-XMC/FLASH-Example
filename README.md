# Blinky Example

The following guide describes the steps to run the first Blinky program on the XMC 4500 Relax Kit board from Infineon.

## Step 1: Download mbed CLI

* [Mbed CLI](https://docs.mbed.com/docs/mbed-os-handbook/en/latest/dev_tools/cli/#installing-mbed-cli) - Download and install mbed CLI.

## Step 2: Import startup project

Import mbed Blinky project from GitHub.

```
https://github.com/mbed-Infineon-XMC/Blinky-Example.git
```

## Step 3: Install ARM GCC toolchain

* [GNU ARM toolchain](https://launchpad.net/gcc-arm-embedded) - Download and install the last stable version of the ARM GCC toolchain.
* Open the file "mbed_settings.py" and add the ARM GCC install path.

Example:
```
#GCC_ARM_PATH = "home/bin/arm_gcc_toolchain/gcc-arm-none-eabi-5_4-2016q2/arm-none-eabi/bin"
```
## Step 4: Compile project

Navigate into the project folder and execute the following command:
```
cd Blinky-Example.git/
mbed compile -m XMC_4500_RELAX_KIT -t GCC_ARM
```
mbed creates a BUID directory where you can find the executables (bin, elf, hex ...).

## Step 5: Flash to board

* [Segger JLink](https://www.segger.com/downloads/jlink) - Install the JLink software for your platform.
* Navigate to the BUILD directory and execute the following JLinkExe commands.
```
$ JLinkExe
J-LINK> device xmc4500-1024
J-LINK> h
J-Link> loadfile Blinky-Example.git.hex
J-Link> r
J-Link> g
```
* Choose SWD, 4000kHz as interface settings!!

## Step 6: If successful..

When everything has gone well, LED1 will blink with 2Hz.

## Step 7: Eclipse IDE & debugging

If you want to compile and debug the project with eclipse follow this guidline:

* First export and create a makefile for the eclipse platform.
```
mbed export -i eclipse_gcc_arm -m XMC_4500_RELAX_KIT
```
* Install Eclipse C/C++ IDE
* [Install Plugins](https://github.com/mhorauer/XMC4500-Barebone-Projects/blob/master/Setup/plugins.asciidoc) - The following tutorial could be helpful.

* [Debugging with eclipse](https://docs.mbed.com/docs/mbed-os-handbook/en/5.3/debugging/debugging_eclipse_pyocd/) - Also take a look to the mbed debuging guidlines.
