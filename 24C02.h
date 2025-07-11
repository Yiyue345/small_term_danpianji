#ifndef __24C02_H__
#define __24C02_H__
#include <reg52.h>
#define ADDR_24C02    0xA0  //24C02Æ÷¼þµØÖ·
void sendBytesTo24C02(unsigned char suba,unsigned char *p,unsigned char no);
void recBytesFrom24C02(unsigned char suba,unsigned char *p,unsigned char no);
#endif