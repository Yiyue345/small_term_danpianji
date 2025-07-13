#include "reg52.h"
#include "smg.h"
#include "delay.h"
#include "ds1302.h"
// 共阴极数码管字形码
// 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 灭, -, .
unsigned char zixing[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x00, 0x40, 0x80};
unsigned char weix[8] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f}; // 位选（低电平有效）
unsigned char duanx[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // 初始化为灭（不显示）

void showLed() {
    static unsigned char index = 0;

    // 使用SelectHC573函数安全地选择数码管位选通道（Y6）
    SelectHC573(6);
	P0 = weix[index];

    // 使用SelectHC573函数安全地选择数码管段选通道（Y7）
	SelectHC573(7);
	P0 = duanx[index];
    
    delayMs(1); // 确保数码管有足够时间显示
    
    // 关闭所有选择，避免干扰
    // SelectHC573(0);
    P0 = 0x00; // 清除段选
    
    index++;
    if (index >= 8) {
        index = 0;
    }
}

void updateLed(unsigned char index, unsigned char digit) {
    if (index < 8 && digit < 13) { // 增加数字范围检查
        duanx[index] = zixing[digit]; 
    }
}

void addDot(unsigned char index) {
    if (index < 8) {
        // 为指定位置的数码管添加小数点
        // 注意：这需要修改字形码，添加小数点位
        if (duanx[index] < 10) { // 只有数字才能添加小数点
            // 这里需要创建带小数点的字形码
            // 暂时简化处理，可以扩展字形数组来支持带小数点的显示
        }
    }
}

void clearLed() {
    updateLed(0, 11);
    updateLed(1, 11);
    updateLed(2, 11);
    updateLed(3, 11);
    updateLed(4, 11);
    updateLed(5, 11);
    updateLed(6, 11);
    updateLed(7, 11);

    showLed();
}

void syncBufTime() {
    // 显示当前时间缓冲区中的时间
    updateLed(0, cur_time_buf[2] / 10);  // 时的十位
    updateLed(1, cur_time_buf[2] % 10);  // 时的个位
    updateLed(2, 11);                    // 分隔符 "-"
    updateLed(3, cur_time_buf[1] / 10);  // 分的十位
    updateLed(4, cur_time_buf[1] % 10);  // 分的个位
    updateLed(5, 11);                    // 分隔符 "-"
    updateLed(6, cur_time_buf[0] / 10);  // 秒的十位
    updateLed(7, cur_time_buf[0] % 10);  // 秒的个位

    // showLed();
}
