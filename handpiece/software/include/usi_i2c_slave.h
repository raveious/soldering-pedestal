/*-----------------------------------------------------*\
|  USI I2C Slave Driver                                 |
|                                                       |
| This library provides a robust, interrupt-driven I2C  |
| slave implementation built on the ATTiny Universal    |
| Serial Interface (USI) hardware.  Slave operation is  |
| implemented as a register bank, where each 'register' |
| is a pointer to an 8-bit variable in the main code.   |
| This was chosen to make I2C integration transparent   |
| to the mainline code and making I2C reads simple.     |
| This library also works well with the Linux I2C-Tools |
| utilities i2cdetect, i2cget, i2cset, and i2cdump.     |
|                                                       |
| Adam Honse (GitHub: CalcProgrammer1) - 7/29/2012      |
|            -calcprogrammer1@gmail.com                 |
\*-----------------------------------------------------*/
#ifndef USI_I2C_SLAVE_H
#define USI_I2C_SLAVE_H

#include <avr/io.h>
#include <avr/interrupt.h>

//Microcontroller Dependent Definitions
#define DDR_USI             DDRB
#define PORT_USI            PORTB
#define PIN_USI             PINB
#define PIN_USI_SCL         PINB2
#define PIN_USI_SDA         PINB0
#define PORT_USI_SCL        PB2
#define PORT_USI_SDA        PB0

//USI I2C Initialize
//  address - If slave, this parameter is the slave address
void USI_I2C_Init(char address);

#endif