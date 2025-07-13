#include "reg52.h"
#include "ds1302.h"

unsigned char code READ_RTC_ADDR[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d}; // RTC读地址
unsigned char code WRITE_RTC_ADDR[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c}; // RTC写地址
// 修改默认时间为BCD格式：23时59分55秒，07日，07月，21年，星期6
unsigned char TIME[7] = {0x55, 0x59, 0x23, 0x07, 0x07, 0x06, 0x21}; 
// 秒，分，时，日，月，年，星期
unsigned char cur_time_buf[7]; // 存储转换后的十进制时间

// DS1302底层通信函数
void Ds1302_Write_Byte(unsigned char addr, unsigned char dat) {
    unsigned char i;
    
    RST_SET; // 启动传输

    for (i = 0; i < 8; i++) {
        DS1302_DAT = addr & (0x01 << i);
        SCK_SET;
        SCK_CLR;
    }

    for (i = 0; i < 8; i++) {
        DS1302_DAT = dat & (0x01 << i);
        SCK_SET;
        SCK_CLR;
    }

    RST_CLR; // 结束传输

    // DS1302_DAT = addr & 0x01; // 设置数据线为地址最低位
    
    // SCK_SET;
    // SCK_CLR;

    // 发送地址字节
    // for (i = 0; i < 8; i++) {
    //     SCK_CLR;
    //     if (addr & 0x01) {
    //         DAT_SET;
    //     } else {
    //         DAT_CLR;
    //     }
    //     addr >>= 1;
    //     SCK_SET;
    // }
    
    // // 发送数据字节
    // for (i = 0; i < 8; i++) {
    //     SCK_CLR;
    //     if (dat & 0x01) {
    //         DAT_SET;
    //     } else {
    //         DAT_CLR;
    //     }
    //     dat >>= 1;
    //     SCK_SET;
    // }
    
}
// 111
unsigned char Ds1302_Read_Byte(unsigned char addr) {
    unsigned char i, dat = 0x00;
    RST_CLR; // 复位DS1302
    SCK_CLR;

    RST_SET; // 启动传输
    for (i = 0; i < 8; i++) {
        DS1302_DAT = addr & (0x01 << i);
        SCK_SET;
        SCK_CLR;
    }
   
    for (i = 0; i < 8; i++) {
        
        if (DS1302_DAT) {
            dat |= (0x01 << i);
        }
        SCK_SET;
        SCK_CLR; 

   }
    DAT_CLR;
    RST_CLR;
    return dat;
    
    // // 发送地址字节
    // for (i = 0; i < 8; i++) {
    //     SCK_CLR;
    //     if (addr & 0x01) {
    //         DAT_SET;
    //     } else {
    //         DAT_CLR;
    //     }
    //     addr >>= 1;
    //     SCK_SET;
    // }
    
    // // 读取数据字节前，需要将数据线设置为输入
    // // 读取数据字节
    // for (i = 0; i < 8; i++) {
    //     SCK_CLR;
    //     SCK_SET;
    //     if (DS1302_DAT) {
    //         dat |= (0x01 << i);
    //     }
    // }
    
    // RST_CLR; // 结束传输
    // SCK_CLR; // 确保时钟线为低

    
}

void Ds1302_Init(void) {
    RST_CLR;
    SCK_CLR;

    // 首先解除写保护
    Ds1302_Write_Byte(0x8e, 0x00);
    // 启动时钟（清除秒寄存器的CH位）
    // Ds1302_Write_Byte(Ds1302_sec_add, 0x00);
    // 重新启用写保护
    Ds1302_Write_Byte(0x8e, 0x80);
}

void Ds1302_Init_Time(void) {
    unsigned char i;
    
    Ds1302_Write_Byte(0x8e, 0x00); // 禁止写保护
    for (i = 0; i < 7; i++) {
        Ds1302_Write_Byte(WRITE_RTC_ADDR[i], TIME[i]);
    }
    Ds1302_Write_Byte(0x8e, 0x80); // 允许写保护
    
}

void Ds1302_Write_Time(void) {
    unsigned char i;
    
    Ds1302_Write_Byte(0x8e, 0x00); // 禁止写保护
    for (i = 0; i < 7; i++) {
        // 正确的十进制到BCD码转换
        TIME[i] = (cur_time_buf[i] / 10) * 16 + (cur_time_buf[i] % 10);
        Ds1302_Write_Byte(WRITE_RTC_ADDR[i], TIME[i]);
    }
    Ds1302_Write_Byte(0x8e, 0x80); // 允许写保护
    
}

void Ds1302_Read_Time(void) {
    unsigned char i, temp;
    
    for (i = 0; i < 7; i++) {
        TIME[i] = Ds1302_Read_Byte(READ_RTC_ADDR[i]);
    }

    for (i = 0; i < 7; i++) {
        temp = TIME[i] / 16;
        cur_time_buf[i] = TIME[i] % 16;
        cur_time_buf[i] += temp * 10; // 转换BCD码
    }
}

