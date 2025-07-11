#include "reg52.h"
#include "smg.h"
#include "delay.h"
// 共阴极数码管字形码
// 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 灭, -, .
unsigned char zixing[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x00, 0x40, 0x80};
unsigned char weix[8] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f}; // 位选（低电平有效）
unsigned char duanx[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // 初始化为灭（不显示）

void showLed() {
    static unsigned char index = 0;

    P2 = 0xc0;
	P0 = weix[index];


	P2 = 0xe0;
	
	P0 = duanx[index];
    
    
    delayMs(1); // 确保数码管有足够时间显示
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