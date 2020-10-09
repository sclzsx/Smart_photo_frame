
#ifndef _ZQWL_DS1302_H_
#define _ZQWL_DS1302_H_



#define NOP() __NOP

#define DS1302_CLK_H()	(GPIOC->BSRR=GPIO_Pin_15)
#define DS1302_CLK_L()	(GPIOC->BRR=GPIO_Pin_15)

#define DS1302_RST_H()	(GPIOD->BSRR=GPIO_Pin_7)
#define DS1302_RST_L()	(GPIOD->BRR=GPIO_Pin_7)

#define DS1302_OUT_H()	(GPIOB->BSRR=GPIO_Pin_9)
#define DS1302_OUT_L()	(GPIOB->BRR=GPIO_Pin_9)
											
#define DS1302_IN_X		(GPIOB->IDR&GPIO_Pin_9)

#define Time_24_Hour	0x00	//24时制控制	
#define Time_Start		0x00	//开始走时

#define DS1302_SECOND	0x80	//DS1302各寄存器操作命令定义
#define DS1302_MINUTE	0x82
#define DS1302_HOUR		0x84
#define DS1302_DAY		0x86
#define DS1302_MONTH	0x88
#define DS1302_WEEK		0x8A
#define DS1302_YEAR		0x8C
#define DS1302_WRITE	0x8E
#define DS1302_POWER	0x90


typedef struct
{
	u8	year;
	u8	month;
	u8	date;
	u8	week;
	u8	hour;
	u8	min;
	u8	sec;
}TIME_TypeDef;

extern TIME_TypeDef time;
extern unsigned char time_ascii1[];
extern unsigned char time_ascii2[];
extern void InitClock(void);
extern void ReadDS1302Clock(u8 *p);
extern void WriteDS1302Clock(u8 *p);
extern void ReadDSRam(u8 *p,u8 add,u8 cnt);
extern void WriteDSRam(u8 *p,u8 add,u8 cnt);
extern void Init_DS1302(void);
void Read_DS1302_Time(TIME_TypeDef *tim);
void Write_DS1302_Time(TIME_TypeDef *tim);

#endif

