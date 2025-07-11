#include "iic.h"
#include "24C02.h"
/*----------------------------------------------------------------
                    �����ӵ�ַ�������Ͷ��ֽ����ݺ���               
����:     ���������ߵ����͵�ַ���ӵ�ַ,���ݣ��������ߵ�ȫ����,
			��������ַsla���ӵ�ַsuba������������sָ������ݣ�����no���ֽڡ�
           �������1��ʾ�����ɹ��������������
ע�⣺    ʹ��ǰ�����ѽ������ߡ�
----------------------------------------------------------------*/
void sendBytesTo24C02(unsigned char suba,unsigned char *p,unsigned char no)
{
   	unsigned char i;
		for(i=0;i<no;i++) { 
   		IIC_Start();               	//��������
   		IIC_SendByte(ADDR_24C02); 	//����������ַ
   		IIC_WaitAck();
			IIC_SendByte(suba);         //���������ӵ�ַ
      IIC_WaitAck();
			IIC_SendByte(*p);            //��������
			IIC_WaitAck();
     	IIC_Stop();                  //��������
      p++;
			suba++;
    } 

}


/*----------------------------------------------------------------
                    �����ӵ�ַ������ȡ���ֽ����ݺ���               
����:     ���������ߵ����͵�ַ���ӵ�ַ,�����ݣ��������ߵ�ȫ����,������
          ��ַsla���ӵ�ַsuba�����������ݷ���sָ��Ĵ洢������no���ֽڡ�
           �������1��ʾ�����ɹ��������������
ע�⣺    ʹ��ǰ�����ѽ������ߡ�
----------------------------------------------------------------*/
void recBytesFrom24C02(unsigned char suba,unsigned char *p,unsigned char no)
{
		unsigned char i;
   	IIC_Start();               //��������			 
   	IIC_SendByte(ADDR_24C02);             //����������ַ
		IIC_WaitAck();   	
		IIC_SendByte(suba);            //���������ӵ�ַ
		IIC_WaitAck();
   	IIC_Start();
   	IIC_SendByte(ADDR_24C02+1);				//������ 1
		IIC_WaitAck();
  	
		for(i=0;i<no-1;i++) { 
     	*p=IIC_RecByte();              //��������
      	IIC_Ack(1);                //���;ʹ�λ 
     	p++;
    } 
   	*p=IIC_RecByte();
    IIC_Ack(0);                 //���ͷ�Ӧλ
    IIC_Stop();                    //��������
}