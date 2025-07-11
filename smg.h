#ifndef _SMG_H_
#define _SMG_H_
#include "reg52.h"
#include "ls138.h"

void showLed();
void updateLed(unsigned char index, unsigned char digit);//��λ�ô���ʾ����
void addDot(unsigned char index); 

#endif