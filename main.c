/*
 * Sunrise.c
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


//Функция обработки прерывания по внешнему порту INT0
ISR(INT0_vect)
{
	n++;             // инкрементировать n
	if(n>4)n=0;
}
void _port_ini(void)
{
	CLKPR|=(1<<3);
	//Выход PA3 на светодиод
	DDRB|=(1<<1);
	//Вывод PD2 на вход для подключения кнопки
	DDRB&=~(1<<2);
	PORTB&=~(1<<2);
}


int main(void)
{
	sei();//Глобальное разрешение прерываний
	//Регистр управления прерываниями для входа INT0
	GIMSK|=(1<<INT0);//разрешить прерывание для входа INT0
	//Регистр настройки условий срабатываний для входа INT0
	MCUCR|=(1<<ISC01);//условие: спадающий фронт на INT0
	_port_ini();
	_delay_ms(500);
	while(1)
	{
		switch (n)//Режим свечения светодиодов, в зависимости от "n"
		{
			case 0:shift(NumLight,0xFF,0xFF,0xFF,0x00,0x00,0xFF);break;
			case 1:shift(NumLight,0x00,0xFF,0x00,0xFF,0xFF,0xFF);break;
			case 2:shift_rainbow(NumLight);break;
			case 3:change_color(NumLight);break;
			case 4:SetLine(NumLight,0xFF,0xFF,0xFF);break;
		}
		
		
	}
}
