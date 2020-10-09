#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"
   	   		   
//IO��������
#define SDA_IN()	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;\
	                     GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;\
	                     GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;\
	                     GPIO_Init(GPIOB, &GPIO_InitStruct);
											 
#define SDA_OUT() GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;\
	                     GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;\
	                     GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;\
	                     GPIO_Init(GPIOB, &GPIO_InitStruct);

//#define SDA_IN()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;}
//#define SDA_OUT() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;}

//IO��������	 
#define IIC_SCL    PBout(1) //SCL
#define IIC_SDA    PBout(0) //SDA	 
#define READ_SDA   PBin(0)  //����SDA 

//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif
















