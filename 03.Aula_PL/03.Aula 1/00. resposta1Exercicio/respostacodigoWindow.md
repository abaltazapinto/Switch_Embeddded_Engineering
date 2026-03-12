/* Replace with your application code */
	DDRA = 0b11000000;
	PORTA = 0b11000000;
	DDRC = 0b11111111;
    while (1) 
    {
		if(PINA == 0b11111110)
		{
			PORTC = 0b01111110;
		}else {
			PORTC = 0b11111111;
		}
    }
	
	
	
int main(void)
{
	DDRA = 0b11000000;
	PORTA = 0b11000000;
	DDRC = 0b11111111;

	uint8_t sw1 = 0b11111110;

	while (1)
	{
		if(PINA == sw1)
		{
			PORTC = 0b11111111;   // todos apagados

			for(int i = 0; i < 8; i++)
			{
				PORTC &= ~(1 << i);   // liga LED
				_delay_ms(1000);
			}
		}
	}
}

PRIMEIRO EXERCICIO

#include <avr/io.h>

#define SW1	0b11111110
#define SW2	0b11111101
#define SW3	0b11111011
#define SW4	0b11110111
#define SW6	0b11011111

#define D1D8	0b01111110
#define D2D7	0b10111101
#define D3D6	0b11011011
#define D4D5	0b11100111

int main(void)
{
    /* Replace with your application code */
	DDRA = 0b11000000;
	PORTA = 0b11000000;
	DDRC = 0b11111111;
    while (1) 
    {
		if (PINA == SW1)
		{
			PORTC &= D1D8;
			//PORTC = PORTC & 0b01111110;
		}
		if (PINA == SW2)
		{
			PORTC &= D2D7;
		}
		if (PINA == SW3)
		{
			PORTC &=D3D6;
		}
		if (PINA == SW4)
		{
			PORTC &= D4D5;
		}
		if (PINA == SW6)
		{
			PORTC = 0b11111111;
		}
    }
}

««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««

Exercicio 2
#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 16000000UL

#define SW1	0b11111110
#define SW2	0b11111101
#define SW3	0b11111011
#define SW4	0b11110111
#define SW6	0b11011111

#define D1D8	0b01111110
#define D2D7	0b10111101
#define D3D6	0b11011011
#define D4D5	0b11100111

int main(void)
{
	/* Replace with your application code */
	DDRA = 0b11000000;
	PORTA = 0b11000000;
	DDRC = 0b11111111;
	while (1)
	{
		PORTC = 0b11111111;
		if(PINA == SW1)
		{
			for(int i = 0; i < 8; i++)
			{
				PORTC &= ~(1 << i);
				_delay_ms(1000);
			}
		}if(PINA == SW2) 
		{
			PORTC = 0b00000000;
			for(int i = 7; i >= 0 ; i--)
			{
				PORTC |= (1 << i);
				_delay_ms(500);
			}
		} else
		{
			PORTC = 0b11111111;
		}
		
	}
}