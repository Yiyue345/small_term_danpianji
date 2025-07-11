#ifndef DS1302_H
#define DS1302_H
#include "reg52.h"

// DS1302硬件连接定义 (根据实际硬件连接修改)
sbit DS1302_CLK = P2^3;  // 时钟线
sbit DS1302_DAT = P2^2;  // 数据线  
sbit DS1302_RST = P2^4;  // 复位线

// 控制宏定义
#define RST_CLR (DS1302_RST = 0)
#define RST_SET (DS1302_RST = 1)
#define SCK_CLR (DS1302_CLK = 0)
#define SCK_SET (DS1302_CLK = 1)
#define DAT_CLR (DS1302_DAT = 0)
#define DAT_SET (DS1302_DAT = 1)

// DS1302寄存器地址定义
#define Ds1302_sec_add   0x80  // 秒寄存器写地址
#define Ds1302_min_add   0x82  // 分寄存器写地址
#define Ds1302_hour_add  0x84  // 时寄存器写地址
#define Ds1302_date_add  0x86  // 日寄存器写地址
#define Ds1302_month_add 0x88  // 月寄存器写地址
#define Ds1302_week_add  0x8a  // 星期寄存器写地址
#define Ds1302_year_add  0x8c  // 年寄存器写地址
#define Ds1302_wp_add    0x8e  // 写保护寄存器地址

// 全局变量声明
extern unsigned char cur_time_buf[7]; // 存储转换后的十进制时间

// 函数声明
void Ds1302_Init(void);
void Ds1302_Write_Time(void);
void Ds1302_Read_Time(void);
void Ds1302_Write_Byte(unsigned char addr, unsigned char dat);
unsigned char Ds1302_Read_Byte(unsigned char addr);

#endif // DS1302_H