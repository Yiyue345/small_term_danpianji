#include "ls138.h"
void SelectHC573(unsigned char channel){
	switch(channel)	{
		case 4:
			P2 = (P2 & 0x1f) | 0x80;		//Y4输出0，选择LED控制,发光二极管
			break;
        
		case 5:
			P2 = (P2 & 0x1f) | 0xa0;		//Y5输出0，选择蜂鸣器和继电器控制
			break;
        
		case 6:
			P2 = (P2 & 0x1f) | 0xc0;		//Y6输出0，选择数码管位选
			break;
        
		case 7:
			P2 = (P2 & 0x1f) | 0xe0;		//Y7输出0，选择数码管段码
			break;
        
		case 0:
			P2 = (P2 & 0x1f) | 0x00;		//所有锁存器不选择
			break;
	}
}