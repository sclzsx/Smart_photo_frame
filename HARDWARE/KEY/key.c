#include "key.h"
#include "delay.h"

void KEY_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);//ʹ��PORTA,PORTCʱ��

			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;			
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
			GPIO_Init(GPIOA, &GPIO_InitStructure);				
			GPIO_SetBits(GPIOA,GPIO_Pin_10);	

			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;			
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
			GPIO_Init(GPIOB, &GPIO_InitStructure);				
			GPIO_SetBits(GPIOB,GPIO_Pin_12);	
	
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //���ó���������
			GPIO_Init(GPIOB, &GPIO_InitStructure);
			
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //���ó���������
			GPIO_Init(GPIOB, &GPIO_InitStructure);
		 
			GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
			GPIO_Init(GPIOB, &GPIO_InitStructure);
} 

//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//����ֵ��
//0��û���κΰ�������
//KEY0_PRES��KEY0����
//KEY1_PRES��KEY1����
//WKUP_PRES��WK_UP���� 
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>WK_UP!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(KEY0==1||KEY1==1||WK_UP==1))
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(KEY0==1)return KEY0_PRES;
		else if(KEY1==1)return KEY1_PRES;
		else if(WK_UP==1)return WKUP_PRES; 
	}else if(KEY0==0&&KEY1==0&&WK_UP==0)key_up=1; 	     
	return 0;// �ް�������
}

