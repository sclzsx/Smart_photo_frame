#include "main.h"

TIME_TypeDef time;
unsigned char time_ascii1[] = "2014-08-13";
unsigned char time_ascii2[] = "10:21:32";
static GPIO_InitTypeDef GPIO_InitStructure;

void DS1302_Configuration(void)
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//50Mʱ���ٶ�
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//50Mʱ���ٶ�
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//50Mʱ���ٶ�
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}


static void DelayNOP(u32 count)
{
	while(count--) NOP();
}

static void DS1302_OUT(void)
{
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

static void DS1302_IN(void)
{
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void DS1302SendByte(u8 byte)
{
	u8	i;

	for(i=0x01;i;i<<=1)
	{
		if(byte&i)	DS1302_OUT_H();
		else	DS1302_OUT_L();
		DS1302_CLK_H();
		DelayNOP(50);		//����ʱ
		DS1302_CLK_L();
	}
}

u8 DS1302ReceiveByte(void)
{
	u8	i,byte=0;

	for(i=0x01;i;i<<=1)
	{
		if(DS1302_IN_X)	byte |= i;
		DS1302_CLK_H();
		DelayNOP(50);		//����ʱ
		DS1302_CLK_L();
	}
	return(byte);
}

void Write1302(u8 addr,u8 data)
{
    DS1302_OUT();
	DS1302_RST_L();
	DS1302_CLK_L();
	DS1302_RST_H();
	DelayNOP(100);
	DS1302SendByte(addr);
	DS1302SendByte(data);
	DelayNOP(100);
	DS1302_RST_L();
}

u8 Read1302(u8 addr)
{
    u8 data=0;

    DS1302_OUT();
	DS1302_RST_L();
	DS1302_CLK_L();
	DS1302_RST_H();
	DelayNOP(100);
	DS1302SendByte(addr|0x01);
	DS1302_IN();
	data = DS1302ReceiveByte();
	DelayNOP(100);
	DS1302_RST_L();
	return(data);
}

//��ȡʱ�亯��
void DS1302_GetTime(u8 *time)
{
//	u8 tmp;
	
	time[0] = Read1302(DS1302_YEAR);
	time[1] = Read1302(DS1302_WEEK);
	time[2] = Read1302(DS1302_MONTH);
	time[3] = Read1302(DS1302_DAY);
	time[4] = Read1302(DS1302_HOUR);
	time[5] = Read1302(DS1302_MINUTE);
	time[6] = Read1302(DS1302_SECOND);	
}

/*
��ȡDS1302�е�RAM
addr:��ַ,��0��30,��31���ֽڵĿռ�
����Ϊ����ȡ������
*/
u8 ReadDS1302Ram(u8 addr)
{
	u8	tmp,res;

	tmp = (addr<<1)|0xc0;
	res = Read1302(tmp);
	return(res);
}

/*
дDS1302�е�RAM
addr:��ַ,��0��30,��31���ֽڵĿռ�
data:Ҫд������
*/
void WriteDS1302Ram(u8 addr,u8 data)
{
	u8	tmp;

	Write1302(DS1302_WRITE,0x00);		//�ر�д����
	tmp = (addr<<1)|0xc0;
	Write1302(tmp,data);
	Write1302(DS1302_WRITE,0x80);		//��д����
}

void ReadDSRam(u8 *p,u8 add,u8 cnt)
{
	u8 i;
	
	if(cnt>30) return;
	for(i=0;i<cnt;i++)
	{
		*p = ReadDS1302Ram(add+1+i);
		p++;
	}
}

void WriteDSRam(u8 *p,u8 add,u8 cnt)
{
	u8 i;
	
	if(cnt>30) return;
	for(i=0;i<cnt;i++)
	{
		WriteDS1302Ram(add+1+i,*p++);
	}
}
  
/*
��ʱ�亯��,˳��Ϊ:��������ʱ����
*/
void Read_DS1302_Time(TIME_TypeDef *tim)
{
	DS1302_OUT();
	DS1302_RST_L();
	DS1302_CLK_L();
	DS1302_RST_H();
	DelayNOP(100);
	DS1302SendByte(0xbf);						//ͻ��ģʽ
	DS1302_IN();
	tim->sec = DS1302ReceiveByte();				//��
	tim->min = DS1302ReceiveByte();				//��
	tim->hour = DS1302ReceiveByte();			//ʱ
	tim->date = DS1302ReceiveByte();			//��
	tim->month = DS1302ReceiveByte();			//��
	tim->week = DS1302ReceiveByte();			//��
	tim->year = DS1302ReceiveByte();					//��
	DS1302ReceiveByte();						//������־�ֽ�
	DelayNOP(100);
	DS1302_RST_L();
}

/*
дʱ�亯��,˳��Ϊ:��������ʱ����
*/
void Write_DS1302_Time(TIME_TypeDef *tim)
{
	Write1302(DS1302_WRITE,0x00);		//�ر�д����
	DS1302_OUT();
	DS1302_RST_L();
	DS1302_CLK_L();
	DS1302_RST_H();
	DelayNOP(100);
	DS1302SendByte(0xbe);					//ͻ��ģʽ
	DS1302SendByte(tim->sec);				//��
	DS1302SendByte(tim->min);				//��
	DS1302SendByte(tim->hour);				//ʱ
	DS1302SendByte(tim->date);				//��
	DS1302SendByte(tim->month);				//��
	DS1302SendByte(tim->week);					//�ܣ����ó���һ��û��ʹ��
	DS1302SendByte(tim->year);				//��
	DS1302SendByte(0x80);				//������־�ֽ�
	DelayNOP(100);
	DS1302_RST_L();
}
void InitClock(void)
{
	u8	tmp;

	DS1302_Configuration();
	tmp = ReadDS1302Ram(0);
	if(tmp^0xa5)
	{
		WriteDS1302Ram(0,0xa5);
		Write1302(DS1302_WRITE,0x00);		//�ر�д����
		Write1302(0x90,0x03);				//��ֹ������
		Write1302(DS1302_HOUR,0x00);		//���ó�24Сʱ��
		Write1302(DS1302_SECOND,0x00);		//ʹ��ʱ������
		Write1302(DS1302_WRITE,0x80);		//��д����
	}
}
void Init_DS1302(void)
{
	u8 i,tt[7],dd1[30],dd2[30];
	InitClock();

	for(i=0;i<30;i++)
	{
		dd1[i] = i;
		dd2[i] = 0;
	}
 
	WriteDSRam(dd1,0,30);
	ReadDSRam(dd2,0,30);
//  	Write_DS1302_Time(&time);
}

