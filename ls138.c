#include "ls138.h"
void SelectHC573(unsigned char channel){
	switch(channel)	{
		case 4:
			P2 = (P2 & 0x1f) | 0x80;		//Y4���0��ѡ��LED����,���������
			break;
        
		case 5:
			P2 = (P2 & 0x1f) | 0xa0;		//Y5���0��ѡ��������ͼ̵�������
			break;
        
		case 6:
			P2 = (P2 & 0x1f) | 0xc0;		//Y6���0��ѡ�������λѡ
			break;
        
		case 7:
			P2 = (P2 & 0x1f) | 0xe0;		//Y7���0��ѡ������ܶ���
			break;
        
		case 0:
			P2 = (P2 & 0x1f) | 0x00;		//������������ѡ��
			break;
	}
}