#include <reg52.h>
#include "keyboard.h"
#include "delay.h"

#define KEY P1



bit isKeyInput(void){
	unsigned char tmp;
	//�а�������1��û�а�������0
	KEY=0XF0;//ʹ4������P1.3~P1.0�����0
	tmp=KEY;//��ȡ����ֵ
	tmp=tmp&0xf0;//ֻ�������ߵ�ֵ
	if(tmp!=0xf0){
		return 1;
	}
	else {
		return 0;
	}
}

unsigned char KeyScan(void){
	//����ɨ����̣��õ������ļ��롣
	//����Ĺ��ɣ���4λ���������룬��4λ���������ɨ����
	//�а���������ɨ���룻û�а�������0xff

	KEY=0XFF;

	//ɨ��P1.0���ڵ���
	{
		KEY=0XFE;//1111 1110
		if(KEY==0X7E)   return 7; //0111 1110   s1
		if(KEY==0XBE) 	return 11; //1011 1110
		if(KEY==0XDE)   return 15; //1101 1110   s3
		if(KEY==0XEE) 	return 19; //1110 1110
	}

	//ɨ��P1.1���ڵ���
	{
		KEY=0XFD;//1111 1101
		if(KEY==0X7D)   return 6; //0111 1101   
		if(KEY==0XBD) 	return 10; //1011 1101
		if(KEY==0XDD)   return 14; //1101 1101   
		if(KEY==0XED) 	return 18; //1110 1101
	}
	
	//ɨ��P1.2���ڵ���
	{
		KEY=0XFB;//1111 1011
		if(KEY==0X7B)   return 5; //0111 1011   
		if(KEY==0XBB) 	return 9; //1011 1011
		if(KEY==0XDB)   return 13; //1101 1011   
		if(KEY==0XEB) 	return 17; //1110 1011
	}

	//ɨ��P1.3���ڵ���
	{
		KEY=0XF7;//1111 0111
		if(KEY==0X77)   return 4; //0111 0111   
		if(KEY==0XB7) 	return 8; //1011 0111
		if(KEY==0XD7)   return 12; //1101 0111   
		if(KEY==0XE7) 	return 16; //1110 0111
	}
	
	
	return 0;
		
}

void WaitKeyRelease(void){
	unsigned char tmp;
	//�ȴ������ɿ���ֻ���ɿ�֮�󣬺������˳�
	while(1){
		KEY=0XF0;//ʹ4������P1.3~P1.0�����0
		tmp=KEY;//��ȡ����ֵ
		tmp=tmp&0xf0;//ֻ�������ߵ�ֵ
		if(tmp==0xf0){//1111 0000 ���߶�Ϊ1���ɿ�
			break ;
		}
	}
	
}

unsigned char readKey(){
	unsigned char keycode=0;
	if(isKeyInput()){
		delayMs(2);
		if(isKeyInput()){
			keycode=KeyScan();
			WaitKeyRelease();
		}
	}	
	return keycode;
		
}
