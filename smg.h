#ifndef _SMG_H_
#define _SMG_H_
#include "reg52.h"
#include "ls138.h"

// 外部变量声明
extern unsigned char zixing[]; // 数码管字形码数组

void showLed();
void updateLed(unsigned char index, unsigned char digit);//��λ�ô���ʾ����
void addDot(unsigned char index); 

#endif