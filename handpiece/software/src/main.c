
#include <stdint.h>

#include <avr/io.h>
#include <util/delay.h>

#include "usi_i2c_slave.h"

#define HANDPIECE_ADDRESS 0x5A

#define BUFFER_SIZE 5

#define JOY_X_HIGH 0
#define JOY_X_LOW  1
#define JOY_Y_HIGH 2
#define JOY_Y_LOW  3
#define BUTTONS    4

extern uint8_t* USI_Slave_register_buffer[];

uint8_t reg_buffer[BUFFER_SIZE];

int main (void)
{	
    // ADC config
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

    // Setup the pointers for all of the data buffers
    for (uint8_t i = 0; i < BUFFER_SIZE; i++)
    {
        USI_Slave_register_buffer[i] = &reg_buffer[i];
    }

    // Setup the I2C interface
    USI_I2C_Init(HANDPIECE_ADDRESS);

    // Enable debug LED
    DDRB |= (1 << PB1) | (1 << PB3) | (1 << PB4);
    PORTB &= ~((1 << PB1) | (1 << PB3) | (1 << PB4));

    // Enable global interrupts
    SREG |= (1 << 7);

    while (1) {
    //     // Start ADC conversion
    //     ADCSRA |= (1 << ADSC);
    
    //     // Wait for the current conversion to complete.
    //     while (ADCSRA & (1 << ADSC) );

    //     // If reading ADC2 (PB4), then read it as the x-axis
    //     if ((ADMUX & (1<< MUX0)) == 0x0)
    //     {
    //         reg_buffer[JOY_X_HIGH] = ADCH;
    //         reg_buffer[JOY_X_LOW]  = ADCL;

    //         // Switch to the other ADC
    //         ADMUX |= (1 << MUX0);
    //     }
    //     // Else, it must be ADC3 (PB3), then read it as the y-axis
    //     else
    //     {
    //         reg_buffer[JOY_Y_HIGH] = ADCH;
    //         reg_buffer[JOY_Y_LOW]  = ADCL;
            
    //         // Switch to the other ADC
    //         ADMUX &= ~(1 << MUX0);

    //         // Bump the button count, just so there is something that will always change for debug
    //         reg_buffer[BUTTONS]++;
    //     }
        
        _delay_ms(300);
    //     // PORTB ^= (1<< PB1);
    }

    return 0; // Return the mandatory result value. It is "0" for success.
}
