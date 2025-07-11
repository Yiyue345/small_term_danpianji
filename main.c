#include "reg52.h"
#include "ls138.h"
#include "smg.h"
#include "delay.h"
#include "iic.h"
#include "keyboard.h"
#include "ds1302.h"

sbit  RST=P2^4;				  
sbit  CLK=P2^3;				   
sbit  DP=P2^2;				   

sbit L1 = P0^0;
sbit L8 = P0^7;

//�ӳٺ���   	   

void delay(unsigned int m)			 
{
	
unsigned int i,j;
for(i=0;i<m;i++)
	
{
   for(j=0;j<121;j++){}      
}
}
//��ʱ��T0
void InitTimer0()
{
	TMOD = 0x01;
	TH0 = (65535 - 50000) / 256;
	TL0 = (65535 - 50000) % 256;
	
	ET0 = 1;
	EA = 1;
	TR0 = 1;
}

// DS1302 ָ��д��
void WriteCommand(unsigned char Command)
{
unsigned char i;
RST=0;
CLK=0;
RST=1;
for(i=8;i>0;i--)
     {
	  DP=Command&0x01;
	  CLK=1;
	  Command>>=1;
	 }
}


//DS1302 ����д��
void WriteData(unsigned char SendDat)
{
unsigned char i;
for(i=8;i>0;i--)
     {
	  DP=SendDat&0x01;
	  CLK=1;
	  SendDat>>=1;
	 }
}


//DS1302 ��ȡ����
unsigned char ReadData()
{
	unsigned char i,RecDat=0;
	for(i=0;i<8;i++)
     {
	  CLK=1;
	  CLK=0;
	  if(DP)RecDat|=0x01<<i;
	 }
	 return(RecDat);
}			

//DS1302���ֽ�����д��Ͷ�ȡ
void WriteByte(unsigned char Command,unsigned char SendDat)
{
	WriteCommand(Command);
	WriteData(SendDat);
	RST=0;
}
unsigned char ReadByte(unsigned char Command)
{
	unsigned char RecDat=0;
	WriteCommand(Command);
	RecDat=ReadData();
	RST=0;
	return(RecDat);
}


//��ʾLED 

void Init_smgled(){


}


void updatesmg(){
 
}

//�жϷ������
unsigned char count = 0;
void serviceTimer0() interrupt 1{
	TH0 = (65535 - 50000) / 256;
	TL0 = (65535 - 50000) % 256;
	
	count++;
	if(count % 10 == 0)
	{
		L1 = ~L1;
	}
	if(count == 100)
	{
		L8 = ~L8;
		count = 0;
	}

}
	
//��main�����������Ŀ�߼�����
void main()	{
	// 初始化定时器
	InitTimer0();
	
	// 初始化DS1302
	Ds1302_Init();
	
	// 延时一下让DS1302稳定
	delay(100);
	
	// 写入默认时间
	Ds1302_Write_Time(); 
	
	// 再次延时
	delay(100);
	
	while (1) {
		// 读取当前时间
		Ds1302_Read_Time();
		
		// 显示时:分:秒 格式
		updateLed(0, cur_time_buf[2] / 10);  // 时的十位
		updateLed(1, cur_time_buf[2] % 10);  // 时的个位
		updateLed(2, 11);                    // 分隔符 "-"
		updateLed(3, cur_time_buf[1] / 10);  // 分的十位
		updateLed(4, cur_time_buf[1] % 10);  // 分的个位
		updateLed(5, 11);                    // 分隔符 "-"
		updateLed(6, cur_time_buf[0] / 10);  // 秒的十位
		updateLed(7, cur_time_buf[0] % 10);  // 秒的个位

		showLed();
		
		// 添加延时，避免读取过于频繁
		delay(10);
	}
	
}