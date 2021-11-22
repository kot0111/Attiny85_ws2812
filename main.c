/*
 * Attiny85_ws2812.c
 *
 * Created: 15.07.2021 10:11:25
 * Author : kot0111
 */

#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "lib_ws2812.h"
#define NumLight 20
_Bool flag = 0;

//Interrupt handler
ISR(PCINT0_vect)
{
	_delay_ms(10);
	if (PINB&&(1<<2))
	{
		flag=1;
	}
	if (PINB&&(1<<3))
	{
		flag=1;
	}
	if (PINB&&(1<<4))
	{
		flag=1;
	}
}
void _port_ini(void)
{
	CLKPR|=(1<<3);
	//Configuring PB1 as the output pin
	DDRB|=(1<<1);
	//Configuring PB2, PB3, PB4 as the input pin
	DDRB&=~(1<<2|1<<3|1<<4);
	PORTB&=~(1<<2|1<<3|1<<4);
}


int main(void)
{
	sei();//Interrupt enabling
	GIMSK|=(1<<PCIE);//enable interrupt for PCINT0 register
	PCMSK |= 0b00011100;//Configuring interrupts on PCINT2, PCINT3, PCINT4
	_port_ini();
	_delay_ms(500);
	while(1)
	{
		if (flag==1)
		{
			n++;
			if(n>4)n=0;
			flag=0;
		}

		switch (n)//changing the light modes
		{
			case 0:shift(NumLight,0xFF,0xFF,0xFF,0x00,0x00,0xFF,&flag);break;
			case 1:shift(NumLight,0x00,0xFF,0x00,0xFF,0xFF,0xFF,&flag);break;
			case 2:shift_rainbow(NumLight*10,&flag,150);break;
			case 3:change_color(NumLight,&flag);break;
			case 4:SetLine(NumLight,0xFF,0xFF,0xFF);break;
		}


	}
}
