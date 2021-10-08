	signed char i=0,m=0,n=0;

	#define red 1
	#define orange 2
	#define yellow 3
	#define green 4
	#define cyan 5
	#define blue 6
	#define purple 7
	#define white 8
	#define none 9

//Sending a logical 0
void Send_bit_0(void)
{
	PORTB|=(1<<1);
	asm("nop");
	PORTB&=~(1<<1);
	asm("nop");
}

//Sending a logical 1
void Send_bit_1(void)
{
	PORTB|=(1<<1);
	for (i=0;i<2;i++)asm("nop");
	PORTB&=~(1<<1);
	asm("nop");
}

//Sending color
void Send_Byte(unsigned char redshade, unsigned char greenshade, unsigned char blueshade)
{
	signed char i;
	for(i=7;i>=0;i--)
	{
		if(greenshade&(1<<i))Send_bit_1();
		else Send_bit_0();
	}
	for(i=7;i>=0;i--)
	{
		if(redshade&(1<<i))Send_bit_1();
		else Send_bit_0();
	}
	for(i=7;i>=0;i--)
	{
		if(blueshade&(1<<i))Send_bit_1();
		else Send_bit_0();
	}
}

//Sending a color by name
void Send_color(unsigned char c)
{
	switch(c)
	{
		case 1: Send_Byte(0x2F,0x00,0x00);break;//red
		case 2: Send_Byte(0x2F,0x1E,0x00);break;//orange
		case 3: Send_Byte(0x2F,0x2F,0x00);break;//yellow
		case 4: Send_Byte(0x00,0x2F,0x00);break;//green
		case 5: Send_Byte(0x00,0x2F,0x2F);break;//cyan
		case 6: Send_Byte(0x00,0x00,0x2F);break;//blue
		case 7: Send_Byte(0x2F,0x00,0x2F);break;//purple
		case 8: Send_Byte(0x2F,0x2F,0x2F);break;//white
		case 9: Send_Byte(0x00,0x00,0x00);break;//none

	}
}

//single-color glow
void SetLine(int t,unsigned char redshade, unsigned char greenshade, unsigned char blueshade)
{
	for (int j = t;j>0;j--)
	{
		Send_Byte(redshade,greenshade,blueshade);
	}
	_delay_ms(100);
}

//animation of color movement
void shift (int t,unsigned char r1, unsigned char g1,unsigned char b1, unsigned char r2, unsigned char g2,unsigned char b2,_Bool *flag)
{

	for (int i=0;i<t;i++)
	{
		for (int j=0;j<t;j++)
		{
			if (*flag)
			{
				break;
			}
			if (j==i)
			{
				Send_Byte(r1,g1,b1);
			}
			else Send_Byte(r2,g2,b2);
		}
		_delay_ms(100);
		if (*flag)
		{
			break;
		}
	}

}

//rainbow animation
void shift_rainbow(int t, _Bool *flag)
{
	unsigned char a[t+8];
		a[0]=9;
	for (int i=1;i<=t+7;i++)
	{
		if (i<8)
		{
			a[i]=8-i;
		} else a[i]=9;

	}

	for (int st=0;st<t+8;st++)
	{
		for (int l = 8;l<t+8;l++)
		{
			Send_color(a[l]);
		}
		for (int o = t+7;o>0;o--)
		{
			a[o]=a[o-1];
		}
		_delay_ms(100);
		if (*flag)
		{
			break;
		}
	}
}

//slow color change
void change_color(int t, _Bool *flag)
{
	int shade;
	for(shade=0;shade<70;shade++)
	{
		for (int i=0;i<(t/5);i++)
		{
			Send_Byte(shade,70-shade,0x2F);
			Send_Byte(0x2F,shade,0x2F);
			Send_Byte(0x2F,0x2F,70-shade);
			Send_Byte(shade,70-shade,shade);
			Send_Byte(70-shade,shade,0x2F);
		}
		_delay_ms(50);
		if (*flag)
		{
			break;
		}
	}
	for(shade=70;shade>0;shade--)
	{
		for (int i=0;i<(t/5);i++)
		{
			if (*flag)
			{
				break;
			}
			Send_Byte(shade,70-shade,0x2F);
			Send_Byte(0x2F,shade,0x2F);
			Send_Byte(0x2F,0x2F,70-shade);
			Send_Byte(shade,70-shade,shade);
			Send_Byte(70-shade,shade,0x2F);
		}
		_delay_ms(50);
		if (*flag)
		{
			break;
		}
	}

}
