#include "lcd_driver.h"

void Delay(unsigned int dly)
{
    unsigned int i,j;

    for(i=0;i<dly;i++)
    	for(j=0;j<255;j++);
}

void TFT_WriteCmd(unsigned int cmd)
{
	uchar cmdH, cmdL;
	cmdH = cmd >> 8;
	cmdL = cmd & 0x00FF;
	
	
	TFT_WR = 1;	 		  //初始化WR
	TFT_CS = 0;			  //打开片选
	
	TFT_RD = 1;           //选择写
	TFT_RS = 0;			  //选择命令
	
	
	TFT_DATAPORT = cmdH; //放置命令数据
	TFT_WR = 0;			  //写入时序
	TFT_WR = 1;
	TFT_DATAPORT = cmdL;

	TFT_WR = 0;			  //写入时序
	TFT_WR = 1;

	TFT_CS = 1;			  //关闭片选 
}

void TFT_WriteData(unsigned int dat)
{
	 uchar datH, datL;
	datH = dat >> 8;
	datL = dat & 0xFF;
	
	TFT_WR = 1;	 		  //初始化WR
	TFT_CS = 0;			  //打开片选
		
	TFT_RD = 1;           //选择写
	TFT_RS = 1;			  //选择发送数据
	

	TFT_DATAPORT = datH;  //放置命令数据
	TFT_WR = 0;			  //写入时序
	TFT_WR = 1;
	TFT_DATAPORT = datL;	

	TFT_WR = 0;			  //写入时序
	TFT_WR = 1;
	
	TFT_CS = 1;			  //关闭片选
}	 
void WriteData(uint i)
{
	TFT_WR = 1;	 		  //初始化WR
	TFT_CS = 0;			  //打开片选
	
	TFT_RD = 1;           //选择写
	TFT_RS = 1;			  //选择发送数据
	
	TFT_DATAPORT = i;
 
	TFT_WR = 0;			  //写入时序
	TFT_WR = 1;
	
	TFT_CS = 1;			  //关闭片选	
}

void WriteComm(uint i)
{
	TFT_WR = 1;	 		  //初始化WR
	TFT_CS = 0;			  //打开片选
	
	TFT_RD = 1;           //选择写
	TFT_RS = 0;			  //选择发送数据
	
	TFT_DATAPORT = i;
 
	TFT_WR = 0;			  //写入时序
	TFT_WR = 1;
	
	TFT_CS = 1;			  //关闭片选	
}
	 
void TFT_Init(void)
{
	TFT_RST = 1;
	Delay(100);
	TFT_RST = 0;
	Delay(800);
	TFT_RST = 1;
	Delay(800);
	
	TFT_CS = 0;

	//************* Start Initial Sequence **********//	
	WriteComm(0xCB);  
	WriteData(0x39); 
	WriteData(0x2C); 
	WriteData(0x00); 
	WriteData(0x34);  
	WriteData(0x02);   
	 
	WriteComm(0xCF);  
	WriteData (0x00); 
	WriteData (0xa2); //c1
	WriteData (0Xf0);  //30
	 
	WriteComm(0xE8);  
	WriteData (0x84); 	 //85
	WriteData (0x11); 	 //00
	WriteData (0x7a); 	 //79
	
	
	WriteComm(0xEA);  
	WriteData (0x66);  //00
	WriteData (0x00); 
	
	WriteComm(0xED);  
	WriteData (0x55); 	//64
	WriteData (0x01); 	//03
	WriteData (0X23); 	//12
	WriteData (0X01); 	//81
	 
	WriteComm(0xF7);  
	WriteData (0x20); 	//20
	
	
	WriteComm(0xC0);    //Power control 
	WriteData (0x1c);   //VRH[5:0] 	//1c
	 
	WriteComm(0xC1);    //Power control 
	WriteData (0x13);   //SAP[2:0];BT[3:0] 	//13
	 
	WriteComm(0xC5);    //VCM control 
	WriteData (0x23); 
	WriteData (0x3F); 
	 
	WriteComm(0xC7);    //VCM control2 
	WriteData(0xA5); 
	
	WriteComm(0xB1);  
	WriteData (0x00); 
	WriteData (0x17); 
	
	WriteComm(0x3A);  
	WriteData (0x55); 
	
	WriteComm(0xB6);  
	WriteData (0x0A);
	WriteData (0xa2);  //a2	 SS显示方向
	WriteData (0x27);
	WriteData (0x00); 
	 
	WriteComm(0x36);    // Memory Access Control 
	WriteData (0x08); 	  //08	BGR
	 
	WriteComm(0xF2);    // 3Gamma Function Disable 
	WriteData (0x02); 	//00
	 
	WriteComm(0x26);    //Gamma curve selected 
	WriteData (0x01); 
	 
	WriteComm(0xE0);    //Set Gamma 
	WriteData (0x0F); 
	WriteData (0x14); 
	WriteData (0x13); 
	WriteData (0x0C); 
	WriteData (0x0E); 
	WriteData (0x05); 
	WriteData (0x45); 
	WriteData (0x85); 
	WriteData (0x36); 
	WriteData (0x09); 
	WriteData (0x14); 
	WriteData (0x05); 
	WriteData (0x09); 
	WriteData (0x03); 
	WriteData (0x00); 
	 
	WriteComm(0XE1);    //Set Gamma 
	WriteData (0x00); 
	WriteData (0x24); 
	WriteData (0x26); 
	WriteData (0x03); 
	WriteData (0x0F); 
	WriteData (0x04); 
	WriteData (0x3F); 
	WriteData (0x14); 
	WriteData (0x52); 
	WriteData (0x04); 
	WriteData (0x10); 
	WriteData (0x0E); 
	WriteData (0x38); 
	WriteData (0x39); 
	WriteData (0x0F); 

	WriteComm(0x2A );
	WriteData(0x00);
	WriteData(0x00);
	WriteData(0x00);
	WriteData(0xEF);

	WriteComm(0x2B );
	WriteData(0x00);
	WriteData(0x00);
	WriteData(0x01);
	WriteData(0x3F);
	 
	WriteComm(0x11);    //Exit Sleep 
	Delay(120); 
	
	WriteComm(0x29);    //Display on
	
}

void TFT_SetWindow(unsigned int xStart,unsigned int yStart,unsigned int xEnd,unsigned int yEnd)
{
	WriteComm(0x2A);
	TFT_WriteData(xStart);
	TFT_WriteData(xEnd);
   
    WriteComm(0x2b);
	TFT_WriteData(yStart);
	TFT_WriteData(yEnd);

	TFT_WriteCmd(0x2c);
}


void TFT_ClearScreen(unsigned int color)
{
	unsigned int i,j;

	TFT_SetWindow(0,0,TFT_XMAX-1,TFT_YMAX-1);
	for(i=0;i<TFT_XMAX;i++)
	{
	    for(j=0;j<TFT_YMAX;j++)
		{ 
			TFT_WriteData(color);
		}
	}
}	 
