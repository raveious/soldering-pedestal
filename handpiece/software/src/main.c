
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	for (;;) {
		_delay_ms(1000);
	}

	return 0; // Return the mandatory result value. It is "0" for success.
}

