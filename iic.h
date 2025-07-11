#ifndef __I2C_H__
#define __I2C_H__  
//void IIC_Start(void);
//void IIC_Stop(void);
//void IIC_SendByte(unsigned char byt);
//unsigned char IIC_RecByte(void);
//bit IIC_WaitAck(void);
//void IIC_Ack(unsigned char ackbit);
//void Delay_IIC(unsigned char time);
void sendBytesTo24C02(unsigned char suba,unsigned char *p,unsigned char no);
void recBytesFrom24C02(unsigned char suba,unsigned char *p,unsigned char no);

unsigned char Read_PCF8591(unsigned char com );

#endif





