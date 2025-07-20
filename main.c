#include "reg52.h"
#include "ls138.h"
#include "smg.h"
#include "delay.h"
#include "keyboard.h"
#include "ds1302.h"
#include "I2C.h"

sbit  RST=P2^4;				  
sbit  CLK=P2^3;				   
sbit  DP=P2^2;				   

sbit L1 = P0^0;
sbit L8 = P0^7;

unsigned char second, minute, hour, key, choose = 0, flag = 0, timerMode = 0;
unsigned int v = 0;
sbit I2C_SCL=P2^1;
sbit I2C_SDA=P2^0;
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
	if(count % 20 == 0 && timerMode == 4) {
		// 先显示完整的时间，确保所有位置都有正确的数字
		syncBufTime();
		
		// 然后根据选择的位置进行闪烁
		if (flag == 0) {
			flag = 1;
			// 闪烁时将选中的位置设为空白（或关闭）
			if (choose == 0) {
				updateLed(0, 10);  // 10 对应空白
				updateLed(1, 10);
			}
			else if (choose == 1) {
				updateLed(3, 10);
				updateLed(4, 10);
			}
			else if (choose == 2) {
				updateLed(6, 10);
				updateLed(7, 10);
			}
		}
		else {
			flag = 0;
			// 恢复显示时，所有位置都会在syncBufTime()中被正确设置
			// 不需要额外操作，因为上面已经调用了syncBufTime()
		}
	}
	if(count == 100)
	{
		count = 0;
	}
}
	

void main()	{

	I2C_SCL = 1;
	I2C_SDA = 1;
	v = PCF_ReadIN0();
	// 初始化定时器
	InitTimer0();
	
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
				syncBufTime(); // 显示当前时间
				showLed(); 
				
				// 添加延时，避免读取过于频繁
				delayMs(1);
				key = readKey();

				if (key == 7) {
					clearLed();
					break;
				} 
				else if (key == 4) {
					timerMode = 4;
					// 进入设置时间模式
					clearLed();
					syncBufTime();
					while (1) {
						// 在设置模式下，不要频繁调用showLed()
						// 让中断函数来处理显示和闪烁
						showLed();

						key = readKey();

						if (key == 7) {
							clearLed();
							timerMode = 0;
							choose = 0;
							Ds1302_Write_Time();
							break;
						} 
						else if (key == 4) {
							choose++;
							choose %= 3;
						}
						else if (key == 11) {
							// 进入设置秒
							if (choose == 2) {
								cur_time_buf[0]++;
								if (cur_time_buf[0] >= 60) {
									cur_time_buf[0] = 0;
								}
							} 
							// 进入设置分
							else if (choose == 1) {
								cur_time_buf[1]++;
								if (cur_time_buf[1] >= 60) {
									cur_time_buf[1] = 0;
								}
							} 
							// 进入设置时
							else if (choose == 0) {
								cur_time_buf[2]++;
								if (cur_time_buf[2] >= 24) {
									cur_time_buf[2] = 0;
								}
							}
						}

						else if (key == 10) {
							// 进入设置秒
							if (choose == 2) {
								cur_time_buf[0]--;
								if (cur_time_buf[0] < 0) {
									cur_time_buf[0] = 59;
								}
							} 
							// 进入设置分
							else if (choose == 1) {
								cur_time_buf[1]--;
								if (cur_time_buf[1] < 0) {
									cur_time_buf[1] = 59;
								}
							} 
							// 进入设置时
							else if (choose == 0) {
								cur_time_buf[2]--;
								if (cur_time_buf[2] < 0) {
									cur_time_buf[2] = 23;
								}
							}
						}
						
						showLed();
					}
				}
			}
		

		}
		else if (key == 6) {
			clearLed();
			while (1) {
				ET0 = 0; // 关闭定时器中断
				v = PCF_ReadIN0();
				ET0 = 1; // 重新开启定时器中断

				updateLed(0, 11);
				updateLed(1, 1);
				updateLed(2, 11);
				updateLed(3, 10);

				updateLed(4, v / 1000);
				updateLed(5, (v % 1000) / 100);
				updateLed(6, (v % 100) / 10);
				updateLed(7, v % 10);

				showLed();

				key = readKey();
				if (key == 7) {
					clearLed();
					break;
				}
			}
		}
		
	}
	
}