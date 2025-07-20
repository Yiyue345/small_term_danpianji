#ifndef __I2C_H__
#define __I2C_H__

#define ADDR_PCF8591  0x90  
#define ADDR_24C02    0xA0  

void I2C_Start(void);
void I2C_Stop(void);
void I2C_SendByte(unsigned char Byte);
unsigned char I2C_ReceiveByte(void);
void I2C_SendAck(unsigned char AckBit);
unsigned char I2C_ReceiveAck(void);

unsigned int PCF_ReadIN1();
unsigned int PCF_ReadIN0();

void AT24C02_WriteByte(unsigned char WordAddress,unsigned char Data);
unsigned char AT24C02_ReadByte(unsigned char WordAddress);

#endif
