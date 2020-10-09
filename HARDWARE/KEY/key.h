#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"

#define KEY0  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)//��ȡ����0
#define KEY1  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)//��ȡ����1
#define WK_UP  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7) //��ȡ����2 
 
#define KEY0_PRES	1		//KEY0  
#define KEY1_PRES	2		//KEY1 
#define WKUP_PRES	3		//KEY2  

#define LED0 PAout(10)
#define LED1 PBout(12)

void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8 mode);  	//����ɨ�躯��					    
#endif
