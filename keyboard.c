#include <reg52.h>
#include "keyboard.h"
#include "delay.h"

#define KEY P1



bit isKeyInput(void){
	unsigned char tmp;
	//有按键返回1，没有按键返回0
	KEY=0XF0;//使4个行线P1.3~P1.0都输出0
	tmp=KEY;//读取按键值
	tmp=tmp&0xf0;//只保留列线的值
	if(tmp!=0xf0){
		return 1;
	}
	else {
		return 0;
	}
}

unsigned char KeyScan(void){
	//逐行扫描键盘，得到按键的键码。
	//键码的构成：高4位是列输入码，低4位是行输出的扫描码
	//有按键，返回扫描码；没有按键返回0xff

	KEY=0XFF;

	//扫描P1.0所在的行
	{
		KEY=0XFE;//1111 1110
		if(KEY==0X7E)   return 7; //0111 1110   s1
		if(KEY==0XBE) 	return 11; //1011 1110
		if(KEY==0XDE)   return 15; //1101 1110   s3
		if(KEY==0XEE) 	return 19; //1110 1110
	}

	//扫描P1.1所在的行
	{
		KEY=0XFD;//1111 1101
		if(KEY==0X7D)   return 6; //0111 1101   
		if(KEY==0XBD) 	return 10; //1011 1101
		if(KEY==0XDD)   return 14; //1101 1101   
		if(KEY==0XED) 	return 18; //1110 1101
	}
	
	//扫描P1.2所在的行
	{
		KEY=0XFB;//1111 1011
		if(KEY==0X7B)   return 5; //0111 1011   
		if(KEY==0XBB) 	return 9; //1011 1011
		if(KEY==0XDB)   return 13; //1101 1011   
		if(KEY==0XEB) 	return 17; //1110 1011
	}

	//扫描P1.3所在的行
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
	//等待按键松开，只有松开之后，函数才退出
	while(1){
		KEY=0XF0;//使4个行线P1.3~P1.0都输出0
		tmp=KEY;//读取按键值
		tmp=tmp&0xf0;//只保留列线的值
		if(tmp==0xf0){//1111 0000 列线都为1。松开
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
