#include <reg52.h>
#include "I2C.h"
#include <intrins.h>

sbit I2C_SCL=P2^1;
sbit I2C_SDA=P2^0;

void Delay5ms() 
{  
    unsigned int i, j;
    for(i=5;i>0;i--)
        for(j=112;j>0;j--);
}

void I2C_Delay(void) 
{
    unsigned char i;
    _nop_(); _nop_(); _nop_(); _nop_();  
    i = 2; while (--i);  
}

void I2C_Start(void)
{
	I2C_SDA=1;
	I2C_SCL=1;
    I2C_Delay();
	I2C_SDA=0;
    I2C_Delay(); 
	I2C_SCL=0;
}


void I2C_Stop(void)
{
	I2C_SDA=0;
	I2C_SCL=1;
    I2C_Delay();
	I2C_SDA=1;
    I2C_Delay();	
}

void I2C_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		I2C_SDA=Byte&(0x80>>i);
	    I2C_Delay();
		I2C_SCL=1;
	    I2C_Delay();
		I2C_SCL=0;
	}
}


unsigned char I2C_ReceiveByte(void)
{
	unsigned char i,Byte=0x00;
	I2C_SDA=1;
	for(i=0;i<8;i++)
	{
		I2C_SCL=1;
	    I2C_Delay();
		if(I2C_SDA){Byte|=(0x80>>i);}
		I2C_SCL=0;
		I2C_Delay();
	}
	return Byte;
}

void I2C_SendAck(unsigned char AckBit)
{
	I2C_SDA=~AckBit;
    I2C_Delay();
	I2C_SCL=1;
    I2C_Delay();
	I2C_SCL=0;
	I2C_SDA = 1;
	I2C_Delay();
}

unsigned char I2C_ReceiveAck(void)
{
	unsigned char AckBit;
	I2C_SDA=1;
	I2C_Delay();
	I2C_SCL=1;
	I2C_Delay();

	AckBit=I2C_SDA;
	if (I2C_SDA) {
		I2C_Stop();
	}
	I2C_SCL=0;
	return ~AckBit;
}
void AT24C02_WriteByte(unsigned char WordAddress,unsigned char Data)
{
	I2C_Start();
	I2C_SendByte(ADDR_24C02);
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress);
	I2C_ReceiveAck();
	I2C_SendByte(Data);
	I2C_ReceiveAck();
	I2C_Stop();
	Delay5ms();
}


unsigned char AT24C02_ReadByte(unsigned char WordAddress)
{
	unsigned char Data;
	I2C_Start();
	I2C_SendByte(ADDR_24C02);
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress);
	I2C_ReceiveAck();
	I2C_Start();
	I2C_SendByte(ADDR_24C02|0x01);
	I2C_ReceiveAck();
	Data=I2C_ReceiveByte();
	I2C_SendAck(1);
	I2C_Stop();
	return Data;
}
unsigned int PCF_ReadIN1()
{
	
	unsigned int Data;
	
	I2C_Start();
	I2C_SendByte(0x90);
	// I2C_ReceiveAck();
	if (!I2C_ReceiveAck()) return 0xFF;
	I2C_SendByte(0x01);
	// I2C_ReceiveAck();
	if (!I2C_ReceiveAck()) return 0xFF;
	I2C_Stop();
	
	I2C_Start();
	I2C_SendByte(0x91);
	// I2C_ReceiveAck();
	if (!I2C_ReceiveAck()) return 0xFF;

	Data=I2C_ReceiveByte();
	I2C_SendAck(0);
	I2C_Stop();
	
	Data = (unsigned int)(Data * 5000.0 / 255);
	
	return Data;
	
}


unsigned int PCF_ReadIN0()
{
	
	unsigned int Data;
	
	I2C_Start();
	I2C_SendByte(0x90);
	// I2C_ReceiveAck();
	if (!I2C_ReceiveAck()) return 0xFF;
	I2C_SendByte(0x00);
	// I2C_ReceiveAck();
	if (!I2C_ReceiveAck()) return 0xFF;
	I2C_Stop();
	
	I2C_Start();
	I2C_SendByte(0x91);
	// I2C_ReceiveAck();
	if (!I2C_ReceiveAck()) return 0xFF;

	Data=I2C_ReceiveByte();
	I2C_SendAck(0);
	I2C_Stop();
	
	Data = (unsigned int)(Data * 5000.0 / 255);
	
	return Data;
	
}
