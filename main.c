#include "reg52.h"
#include "ls138.h"
#include "smg.h"
#include "delay.h"
#include "iic.h"
#include "keyboard.h"

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
	while (1) {
		unsigned char key = readKey();
		if (key) {
			updateLed(1, key % 9);
		}
		showLed();
	}
	
}