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
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//使能定时器3时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
	
	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE); //Timer3部分重映射  TIM3_CH2->PB5    
 
   //设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOB.5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO

	TIM_DeInit(TIM2);
	
   //初始化TIM3
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//初始化TIM3 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	
	TIM_OCInitStructure.TIM_Pulse = 500;
	
	TIM_OC2Init(TIM2, &TIM_OCInitStructure); //根据T指定的参数初始化外设TIM3 OC2

	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
 
	TIM_Cmd(TIM2, ENABLE);  //使能TIM3
	
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

