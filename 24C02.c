#include "iic.h"
#include "24C02.h"
/*----------------------------------------------------------------
                    向有子地址器件发送多字节数据函数               
功能:     从启动总线到发送地址，子地址,数据，结束总线的全过程,
			从器件地址sla，子地址suba，发送内容是s指向的内容，发送no个字节。
           如果返回1表示操作成功，否则操作有误。
注意：    使用前必须已结束总线。
----------------------------------------------------------------*/
void sendBytesTo24C02(unsigned char suba,unsigned char *p,unsigned char no)
{
   	unsigned char i;
		for(i=0;i<no;i++) { 
   		IIC_Start();               	//启动总线
   		IIC_SendByte(ADDR_24C02); 	//发送器件地址
   		IIC_WaitAck();
			IIC_SendByte(suba);         //发送器件子地址
      IIC_WaitAck();
			IIC_SendByte(*p);            //发送数据
			IIC_WaitAck();
     	IIC_Stop();                  //结束总线
      p++;
			suba++;
    } 

}


/*----------------------------------------------------------------
                    向有子地址器件读取多字节数据函数               
功能:     从启动总线到发送地址，子地址,读数据，结束总线的全过程,从器件
          地址sla，子地址suba，读出的内容放入s指向的存储区，读no个字节。
           如果返回1表示操作成功，否则操作有误。
注意：    使用前必须已结束总线。
----------------------------------------------------------------*/
void recBytesFrom24C02(unsigned char suba,unsigned char *p,unsigned char no)
{
		unsigned char i;
   	IIC_Start();               //启动总线			 
   	IIC_SendByte(ADDR_24C02);             //发送器件地址
		IIC_WaitAck();   	
		IIC_SendByte(suba);            //发送器件子地址
		IIC_WaitAck();
   	IIC_Start();
   	IIC_SendByte(ADDR_24C02+1);				//读动作 1
		IIC_WaitAck();
  	
		for(i=0;i<no-1;i++) { 
     	*p=IIC_RecByte();              //发送数据
      	IIC_Ack(1);                //发送就答位 
     	p++;
    } 
   	*p=IIC_RecByte();
    IIC_Ack(0);                 //发送非应位
    IIC_Stop();                    //结束总线
}