#include<reg52.h>
#include "gui.h"
#include "math.h"
#include "XPT2046.h"
extern uint Read_AD_Data(uchar cmd);
unsigned char findappro(unsigned char dat1);
void ConnectLine();
unsigned int Date[96],xlabel[96],ylabel[96];

void delay_10us(unsigned char i)
{
	while(i--);
}
char AxisTriangleData[]=
{
	0,5,10,15,20,25,30,35,40,
	35,30,25,20,15,10,5,0,
	5,10,15,20,25,30,35,40,
	35,30,25,20,15,10,5,
	0,5,10,15,20,25,30,35,40,
	35,30,25,20,15,10,5,0,
	5,10,15,20,25,30,35,40,
	35,30,25,20,15,10,5,
	0,5,10,15,20,25,30,35,40,
	35,30,25,20,15,10,5,0,
	5,10,15,20,25,30,35,40,
	35,30,25,20,15,10,5,
};
unsigned char TriangleParam[]=
{
	0x00,0x10,0x20,0x30,0x40,0x50,0x60,0x70,
	0x80,0x90,0xa0,0xb0,0xc0,0xd0,0xe0,0xf0,
	0xff,0xf0,0xe0,0xd0,0xc0,0xb0,0xa0,0x90,
	0x80,0x70,0x60,0x50,0x40,0x30,0x20,0x10,
	0x00,0x10,0x20,0x30,0x40,0x50,0x60,0x70,
	0x80,0x90,0xa0,0xb0,0xc0,0xd0,0xe0,0xf0,
	0xff,0xf0,0xe0,0xd0,0xc0,0xb0,0xa0,0x90,
	0x80,0x70,0x60,0x50,0x40,0x30,0x20,0x10
};

char AxisSquare[]={
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50
};

unsigned char SquareParam[64]=	   //??
{
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff
};

unsigned char findappro(unsigned char dat1)
{
	unsigned char i,apparo=0xff,flag,xlabel1;
	for(i=0;i<32;i++)			   //限位
	{
		if(apparo>abs(dat1-SquareParam[i]))
		{
			apparo=abs(dat1-SquareParam[i]);
			flag=i;
		}
	}
	/*
	加提示
	*/

	xlabel1=(AxisSquare[flag]+40)*(dat1/(SquareParam[flag]))+120;
	//xlabel1=(AxisTriangleData[flag])*(dat1/(TriangleParam[flag]))+120;
	return xlabel1;	
}

void ConnectLine()
{
	unsigned int i;
	xlabel[0]=120;ylabel[0]=20;
	for(i=1;i<=40;i++)
	{
			Date[i]=Read_AD_Data(0xEC);	//未定义？？？
			xlabel[i]=findappro(Date[i]);
			ylabel[i]=15*i+20;
			GUI_Line(xlabel[i-1],ylabel[i-1],xlabel[i],ylabel[i],0xF800);
			delay_10us(4);
	}
}

void DrawGrip()
{
	unsigned char i,j;
		//初始界面文字
	
	GUI_Line(10,10,230,10,BLACK);//标尺x
	for(i=0;i<=10;i++)
		GUI_Line(10+22*i,10,10+22*i,13,BLACK);
	GUI_Line(230,24,230,354,BLACK);//标尺y
	//网格
	for(i=0;i<=15;i++)
		GUI_Line(227,27+22*i,230,27+22*i,BLACK);
	
	for(i=0;i<=14;i++)
		GUI_Line(20,20+20*i,220,20+20*i,BLACK);
	for(j=0;j<=10;j++)
		GUI_Line(20+20*j,20,20+j*20,300,BLACK);
	GUI_Line(20,160,220,162,BLUE);
	GUI_Line(120,20,122,300,BLUE);
	

}

void main()
{
		TFT_Init();
		TFT_ClearScreen(WHITE);	  //刷黑色

		DrawGrip();
		ConnectLine();
		while(1);//?????	
}