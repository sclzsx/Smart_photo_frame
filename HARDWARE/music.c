#include "music.h"

#include "delay.h"

#include"stm32f10x.h"

#define eight delay_ms(p);
#define two delay_ms(2*p);
#define onehalf delay_ms((1.5)*p);
#define one delay_ms(1*p);
#define four delay_ms(4*p);

float A[7]={2093,2349,2637,2794,3136,3520,3951},
      C[7]={523,587,659,698,784,880,988},
      B[7]={1047,1175,1329,1397,1568,1760,1976};
int r=1000,i=10;
  
u16 p=100;
	  
void TIM2_PWM_Init(int arr,int psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//ʹ�ܶ�ʱ��3ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
	
	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE); //Timer3������ӳ��  TIM3_CH2->PB5    
 
   //���ø�����Ϊ�����������,���TIM3 CH2��PWM���岨��	GPIOB.5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO

	TIM_DeInit(TIM2);
	
   //��ʼ��TIM3
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	//��ʼ��TIM3 Channel2 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	
	TIM_OCInitStructure.TIM_Pulse = 500;
	
	TIM_OC2Init(TIM2, &TIM_OCInitStructure); //����Tָ���Ĳ�����ʼ������TIM3 OC2

	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���
 
	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIM3
	
}

void  low1(void) {	TIM2_PWM_Init(1999,136);}
void  low2(void) {	TIM2_PWM_Init(1999,121);}
void  low3(void) {	TIM2_PWM_Init(1999,108);}
void  low4(void) {	TIM2_PWM_Init(1999,102);}
void  low5(void) {	TIM2_PWM_Init(1999,90);}
void  low6(void) {	TIM2_PWM_Init(1999,80);}
void  low7(void) {	TIM2_PWM_Init(1999,71);}
void  mid1(void) {	TIM2_PWM_Init(1999,67);}
void  mid2(void) {	TIM2_PWM_Init(1999,61);}
void  mid3(void) {	TIM2_PWM_Init(1999,53);}
void  mid4(void) {	TIM2_PWM_Init(1999,50);}
void  mid5(void) {	TIM2_PWM_Init(1999,44);}
void  mid6(void) {	TIM2_PWM_Init(1999,39);}
void  mid7(void) {	TIM2_PWM_Init(1999,35);}
void  hig1(void) {	TIM2_PWM_Init(1999,33);}
void  hig2(void) {	TIM2_PWM_Init(1999,29);}
void  hig3(void) {	TIM2_PWM_Init(1999,26);}
void  hig4(void) {	TIM2_PWM_Init(1999,24);}
void  hig5(void) {	TIM2_PWM_Init(1999,21);}
void  hig6(void) {	TIM2_PWM_Init(1999,19);}
void  hig7(void) {	TIM2_PWM_Init(1999,17);}	

void music_1(void)
{
	mid1();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid2();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid3();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
 	mid1();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	
	mid1();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid2();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid3();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
 	mid1();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	
	mid3();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid4();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid5();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(4*p);
	
	mid3();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid4();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid5();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(4*p);
	
	mid5();one GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(1*p);
	mid6();one GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid5();one GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(1*p);
	mid4();one GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid3();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
 	mid1();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	
	mid5();one GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(1*p);
	mid6();one GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid5();one GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(1*p);
	mid4();one GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid3();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
 	mid1();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	
	mid2();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	low5();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid1();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(4*p);
	
	mid2();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	low5();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid1();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);

}
void music_2(void)
{
	mid3();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid3();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid4();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
 	mid5();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	
	mid5();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid4();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid3();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
 	mid2();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	
	mid1();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid1();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid2();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
 	mid3();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	
	
	mid3();onehalf GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid2();one GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid2();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(4*p);
	
	mid3();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid3();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid4();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
 	mid5();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	
	mid5();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid4();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid3();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
 	mid2();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	
	mid1();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid1();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid2();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
 	mid3();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	
	mid2();onehalf GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid1();one GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid1();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(4*p);
	
	mid2();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid2();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid3();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
 	mid1();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	
	mid2();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid3();one GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid4();one GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
 	mid3();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid1();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	
	mid2();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid3();one GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid4();one GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
 	mid3();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid2();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	
	mid1();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid2();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	low5();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(4*p);
	mid3();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	
	mid3();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid3();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid4();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
 	mid5();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	
	mid5();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid4();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid3();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid4();one GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
 	mid2();one GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	
	mid1();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid1();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid2();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
 	mid3();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	
	mid2();onehalf GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid1();one GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(2*p);
	mid1();two GPIO_ResetBits(GPIOB,GPIO_Pin_3);delay_ms(4*p);
	
	
	
}

