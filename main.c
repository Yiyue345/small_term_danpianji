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


// 定时器T0初始化
void InitTimer0()
{
	TMOD = 0x01;
	TH0 = (65535 - 50000) / 256;
	TL0 = (65535 - 50000) % 256;
	
	ET0 = 1;
	EA = 1;
	TR0 = 1;
}

void Init_smgled(){

}


void updatesmg(){
 
}

// 定时器T0中断服务函数
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
	
unsigned char second, minute, hour, key;
void main()	{

	// // 初始化定时器
	// InitTimer0();
	
	// // 初始化DS1302
	// Ds1302_Init();
	
	// // 延时一下让DS1302稳定
	// delay(100);
	
	// // 写入默认时间
	// Ds1302_Write_Time(); 
	
	// // 再次延时
	// delay(100);

	SelectHC573(1);
	Ds1302_Init();

	Ds1302_Write_Byte(0x8e, 0x00); // 禁止写保护
	// Ds1302_Write_Byte(0x80, 0x00); // 使能写操作
	// 写入默认时间
	Ds1302_Init_Time(); 
	Ds1302_Write_Byte(0x8e, 0x80); // 启用写保护
	
	clearLed(); 

	
	while (1) {
		key = readKey(); // 扫描按键

		if (key == 7) {
			while (1) {
				// 读取当前时间
				Ds1302_Read_Time();
				
				// 显示时-分-秒 格式
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
				delayMs(1);
				key = readKey();

				if (key == 7) {
					clearLed();
					break;
				}
			}
		

		}
		
	}
	
}