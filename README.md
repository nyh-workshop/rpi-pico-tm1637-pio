# rpi-pico-tm1637-pio
## Basic Demonstration of the Raspberry Pi Pico's PIO module with TM1637 display module.

This is an attempt to use the PIO module in the Raspberry Pi Pico to control the TM1637 display module.

The TM1637 module interface is not *actually* using the I2C despite its protocol vaguely resembles one. In other words, it's not I2C compatible.

Normally this module is driven by bit banging by firmware for other popular microcontrollers.

Here, this Raspberry Pi's PIO module does all the bit-banging to the module without a lot of firmware assistance. The only firmware work is to send data to the PIO's FIFO and to initialize the PIO unit.

Since there aren't a lot of instructions in the PIO module (only 9), trying to make this code very compact and flexible can be a very complicated approach.

For now, the temporary workaround is to continue sending two control commands and then one command with data to the module.

To print something out inside, you may need to send:
- First byte = 0x88 (the 3 least significant bits are brightness values)
- Second byte = 0x44 (the second byte must 0x44 because we are dealing with Fixed Address mode - sending one addr, then one command. The PIO module here is programmed to do only that mode)
- Third byte = 0xCx (address - 0xC0 - 0xC5)
- Fourth byte = data for that address in the 3rd byte.

The limitations are it couldn't read the keys and couldn't continuously send more than one data per address.
