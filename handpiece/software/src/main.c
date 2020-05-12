
#include <stdint.h>

#include <avr/io.h>
#include <avr/sleep.h>

#include "usi_i2c_slave.h"

#define HANDPIECE_ADDRESS 0x10

extern char* USI_Slave_register_buffer[];

union Device_Data
{
	struct Joy_Data
	{
		uint16_t joy_x;
		uint16_t joy_y;
		uint8_t buttons;
	} joy_data;
	char bytes[sizeof(struct Joy_Data)];
} data;

int main (void)
{	
    ADMUX = (0 << ADLAR) |     // do not left shift result (for 10-bit values)
            (0 << REFS2) |     // Sets ref. voltage to Vcc, bit 2
            (0 << REFS1) |     // Sets ref. voltage to Vcc, bit 1   
            (0 << REFS0) |     // Sets ref. voltage to Vcc, bit 0
            (0 << MUX3)  |
            (0 << MUX2)  |
            (1 << MUX1)  |
            (0 << MUX0);

    ADCSRA = (1 << ADEN)  |     // Enable ADC 
             (1 << ADPS2) |     // set prescaler to 64, bit 2 
             (1 << ADPS1) |     // set prescaler to 64, bit 1 
             (0 << ADPS0);      // set prescaler to 64, bit 0  

	// Setup the pointers for all of the data structures
	for (uint8_t i = 0; i < sizeof(union Device_Data); i++)
	{
		USI_Slave_register_buffer[i] = &data.bytes[i];
	}

	// Setup the I2C interface
	USI_I2C_Init(HANDPIECE_ADDRESS);

	while (1) {
		// Start ADC conversion
		ADCSRA |= (1 << ADSC);
	
		// Wait for the current conversion to complete.
		while (ADCSRA & (1 << ADSC) );

		// If reading ADC2 (PB4), then read it as the x-axis
		if ((ADMUX & (1<< MUX0)) == 0x0)
		{
			data.joy_data.joy_x = (ADCH << 8) | ADCL;

			// Switch to the other ADC
			ADMUX |= (1 << MUX0);
		}
		// Else, it must be ADC3 (PB3), then read it as the y-axis
		else
		{
			data.joy_data.joy_y = (ADCH << 8) | ADCL;
			
			// Switch to the other ADC
			ADMUX &= ~(1 << MUX0);
		}
	}

	return 0; // Return the mandatory result value. It is "0" for success.
}
