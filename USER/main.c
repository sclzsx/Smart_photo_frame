#include "delay.h"
#include "sys.h"
#include "lcd.h"
//#include "touch.h"
#include "gui.h"
//#include "test.h"
#include "key.h"
#include "music.h"
#include "sys.h"
#include "usart.h"
#include "malloc.h"  
#include "MMC_SD.h"  
#include "spi.h"
#include "flash.h"
//#include "24cxx.h" 
//#include "myiic.h"
#include "ds18b20.h"
#include "ff.h"  
#include "exfuns.h"
#include "fontupd.h"
#include "text.h"	
#include "piclib.h"	
#include "string.h"	
#include "DS1302.h"
//#include "HMC5883.h"

/*���ŷ���
DS1302
CLK   B1 
DAT   B0
RST   C13

AT24C02
SDA   B0
SCL   B1

DS18B20
DAT   A15

LED0  A10   
LED1  B12
BEEP  B3

COMPASS
SCL   B4
SDA   A13 
DRDY  A14

KEY   K0 K1 WKUP
B6    B5    B7

LCD
TCS   A2    CLK   A5
PEN   A11   FCS   A15
MISO  A6    MOSI  A7
GND         NC
VDD   V3    GND
BL    A9    VDD   
DB15  B15   SDCS  A3
DB13  B13   DB14  B14
DB11  B11   DB12  B12
DB9   B9    DB10  B10
DB7         DB8   B8 
DB5         DB6
DB3         DB4
DB1         DB2
RST   A4    DB0
WR    A0    RD    A1
CS    A8    RS    A12
*/



u8 key;				//��ֵ


u16 pic_get_tnum(u8 *path)
{	  
	u8 res;
	u16 rval=0;
 	DIR tdir;	 		//��ʱĿ¼
	FILINFO tfileinfo;	//��ʱ�ļ���Ϣ	
	u8 *fn;	 			 			   			     
    res=f_opendir(&tdir,(const TCHAR*)path); 	//��Ŀ¼
  	tfileinfo.lfsize=_MAX_LFN*2+1;				//���ļ�����󳤶�
	tfileinfo.lfname=mymalloc(tfileinfo.lfsize);//Ϊ���ļ������������ڴ�
	if(res==FR_OK&&tfileinfo.lfname!=NULL)
	{
		while(1)//��ѯ�ܵ���Ч�ļ���
		{
	        res=f_readdir(&tdir,&tfileinfo);       		//��ȡĿ¼�µ�һ���ļ�
	        if(res!=FR_OK||tfileinfo.fname[0]==0)break;	//������/��ĩβ��,�˳�		  
     		fn=(u8*)(*tfileinfo.lfname?tfileinfo.lfname:tfileinfo.fname);			 
			res=f_typetell(fn);	
			if((res&0XF0)==0X50)//ȡ����λ,�����ǲ���ͼƬ�ļ�	
			{
				rval++;//��Ч�ļ�������1
			}	    
		}  
	} 
	return rval;
}


void my_show_pic(void)
{
	u8 res;
 	DIR picdir;	 		//ͼƬĿ¼
	FILINFO picfileinfo;//�ļ���Ϣ
	u8 *fn;   			//���ļ���
	u8 *pname;			//��·�����ļ���
	u16 totpicnum; 		//ͼƬ�ļ�����
	u16 curindex;		//ͼƬ��ǰ����
	u8 pause=0;			//��ͣ���
	u8 t;
	u16 temp;
	u16 *picindextbl;	//ͼƬ������ 		 
	
	POINT_COLOR=RED;      
 	while(font_init()) 	//����ֿ�
	{	    
		LCD_ShowString(60,50,200,16,16,"Font Error!");
		delay_ms(200);				  
		LCD_Fill(60,50,240,66,WHITE);//�����ʾ	     
		delay_ms(200);				  
	}  	 
 	Show_Str(60,50,200,16,"Mini STM32������",16,0);				    	 
	Show_Str(60,70,200,16,"ͼƬ��ʾ����",16,0);				    	 
	Show_Str(60,90,200,16,"KEY0:NEXT KEY1:PREV",16,0);				    	 
	Show_Str(60,110,200,16,"WK_UP:PAUSE",16,0);				    	 
	Show_Str(60,130,200,16,"����ԭ��@ALIENTEK",16,0);				    	 
	Show_Str(60,150,200,16,"2014��3��14��",16,0);
	
 	while(f_opendir(&picdir,"0:/PICTURE"))//��ͼƬ�ļ���
 	{	    
		Show_Str(60,170,240,16,"PICTURE�ļ��д���!",16,0);
		delay_ms(200);				  
		LCD_Fill(60,170,240,186,WHITE);//�����ʾ	     
		delay_ms(200);				  
	}  
	totpicnum=pic_get_tnum("0:/PICTURE"); //�õ�����Ч�ļ���
  	while(totpicnum==NULL)//ͼƬ�ļ�Ϊ0		
 	{	    
		Show_Str(60,170,240,16,"û��ͼƬ�ļ�!",16,0);
		delay_ms(200);				  
		LCD_Fill(60,170,240,186,WHITE);//�����ʾ	     
		delay_ms(200);				  
	}
	
  picfileinfo.lfsize=_MAX_LFN*2+1;						//���ļ�����󳤶�
	picfileinfo.lfname=mymalloc(picfileinfo.lfsize);	//Ϊ���ļ������������ڴ�
 	pname=mymalloc(picfileinfo.lfsize);				//Ϊ��·�����ļ��������ڴ�
 	picindextbl=mymalloc(2*totpicnum);				//����2*totpicnum���ֽڵ��ڴ�,���ڴ��ͼƬ����
 	while(picfileinfo.lfname==NULL||pname==NULL||picindextbl==NULL)//�ڴ�������
 	{	    
		Show_Str(60,170,240,16,"�ڴ����ʧ��!",16,0);
		delay_ms(200);				  
		LCD_Fill(60,170,240,186,WHITE);//�����ʾ	     
		delay_ms(200);				  
	}  	
	//��¼����
    res=f_opendir(&picdir,"0:/PICTURE"); //��Ŀ¼
	if(res==FR_OK)
	{
		curindex=0;//��ǰ����Ϊ0
		while(1)//ȫ����ѯһ��
		{
			temp=picdir.index;								//��¼��ǰindex
	        res=f_readdir(&picdir,&picfileinfo);       		//��ȡĿ¼�µ�һ���ļ�
	        if(res!=FR_OK||picfileinfo.fname[0]==0)break;	//������/��ĩβ��,�˳�		  
     		fn=(u8*)(*picfileinfo.lfname?picfileinfo.lfname:picfileinfo.fname);			 
			res=f_typetell(fn);	
			if((res&0XF0)==0X50)//ȡ����λ,�����ǲ���ͼƬ�ļ�	
			{
				picindextbl[curindex]=temp;//��¼����
				curindex++;
			}	    
		} 
	}
	
	Show_Str(60,170,240,16,"��ʼ��ʾ...",16,0); 
	delay_ms(1500);
	piclib_init();										//��ʼ����ͼ	   	   
	curindex=0;											//��0��ʼ��ʾ
   	res=f_opendir(&picdir,(const TCHAR*)"0:/PICTURE"); 	//��Ŀ¼
	while(res==FR_OK)//�򿪳ɹ�
	{	
		dir_sdi(&picdir,picindextbl[curindex]);			//�ı䵱ǰĿ¼����	   
        res=f_readdir(&picdir,&picfileinfo);       		//��ȡĿ¼�µ�һ���ļ�
        if(res!=FR_OK||picfileinfo.fname[0]==0)break;	//������/��ĩβ��,�˳�
     	fn=(u8*)(*picfileinfo.lfname?picfileinfo.lfname:picfileinfo.fname);			 
		strcpy((char*)pname,"0:/PICTURE/");				//����·��(Ŀ¼)
		strcat((char*)pname,(const char*)fn);  			//���ļ������ں���
 		LCD_Clear(BLACK);
 		ai_load_picfile(pname,0,0,lcddev.width,lcddev.height,1);//��ʾͼƬ    
		Show_Str(2,2,240,16,pname,16,1); 				//��ʾͼƬ����
		t=0;
		
		while(1) 
		{
			key=KEY_Scan(0);		//ɨ�谴��
			if(t>250)key=1;			//ģ��һ�ΰ���KEY0    
			if((t%20)==0)LED0=!LED0;//LED0��˸,��ʾ������������.
			if(key==KEY1_PRES)		//��һ��
			{
				if(curindex)curindex--;
				else curindex=totpicnum-1;
				break;
			}else if(key==KEY0_PRES)//��һ��
			{
				curindex++;		   	
				if(curindex>=totpicnum)curindex=0;//��ĩβ��ʱ��,�Զ���ͷ��ʼ
				break;
			}else if(key==WKUP_PRES)
			{
				pause=!pause;
				LED1=!pause; 	//��ͣ��ʱ��LED1��.  
			}
			if(pause==0)t++;
			delay_ms(10); 
		}					    
		res=0;  
	} 											  
	myfree(picfileinfo.lfname);	//�ͷ��ڴ�			    
	myfree(pname);				//�ͷ��ڴ�			    
	myfree(picindextbl);		//�ͷ��ڴ�			 	
}
	

void my_show_time(void)
{
 	time.year = 0x14;	
 	time.month = 0x08;
 	time.date = 0x13;
 	time.week = 0x03;
 	time.hour = 0x13;
 	time.min = 0x00;
 	time.sec = 0x50;
 	Write_DS1302_Time(&time);				
	while(1)
	{
		Read_DS1302_Time(&time);		
		LCD_ShowNum(0,30,2,1,16);	
		LCD_ShowNum(20,30,0,1,16);
		LCD_ShowNum(40,30,time.year>>4,1,16);	
		LCD_ShowNum(60,30,time.year&0x0f,1,16);
		LCD_ShowString(80,30,200,16,16,"-");
			
		LCD_ShowNum(100,30,time.month>>4,1,16);	
		LCD_ShowNum(120,30,time.month&0x0f,1,16);
		LCD_ShowString(140,30,200,16,16,"-");
			
		LCD_ShowNum(160,30,time.date>>4,1,16);	
		LCD_ShowNum(180,30,time.date&0x0f,1,16);

		LCD_ShowNum(0,50,time.hour>>4,1,16);	
		LCD_ShowNum(20,50,time.hour&0x0f,1,16);
		LCD_ShowString(40,50,200,16,16,":");

		LCD_ShowNum(60,50,time.min>>4,1,16);	
		LCD_ShowNum(80,50,time.min&0x0f,1,16);
		LCD_ShowString(100,50,200,16,16,":");

		LCD_ShowNum(120,50,time.sec>>4,1,16);	
		LCD_ShowNum(140,50,time.sec&0x0f,1,16);

		LCD_ShowNum(0,70,time.week&0x07,1,16);
	}	
}

void my_show_temper(void)
{
	u8 t;
	short temperature;  	
 	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString1(60,50,16,"Mini STM32",0);	
	LCD_ShowString1(60,70,16,"DS18B20 TEST",0);	
	LCD_ShowString1(60,90,16,"ATOM@ALIENTEK",0);
	LCD_ShowString1(60,110,16,"2014/3/12",0);		  
 	while(DS18B20_Init())	//DS18B20��ʼ��	
	{
		LCD_ShowString1(60,130,16,"DS18B20 Error",0);
		delay_ms(200);
		LCD_Fill(60,130,239,130+16,WHITE);
 		delay_ms(200);
	}								   
	LCD_ShowString1(60,130,16,"DS18B20 OK",0);
	POINT_COLOR=BLUE;//��������Ϊ��ɫ 
 	LCD_ShowString1(60,150,16,"Temp:   . C",0);	 
	while(1)
	{	    	    
 		if(t%10==0)//ÿ100ms��ȡһ��
		{									  
			temperature=DS18B20_Get_Temp();	
			if(temperature<0)
			{
				LCD_ShowChar1(60+40,150,POINT_COLOR,BACK_COLOR,'-',16,0);			//��ʾ����
				temperature=-temperature;					//תΪ����
			}else LCD_ShowChar1(60+40,150,POINT_COLOR,BACK_COLOR,' ',16,0);			//ȥ������
			LCD_ShowNum(60+40+8,150,temperature/10,2,16);	//��ʾ��������	    
   			LCD_ShowNum(60+40+32,150,temperature%10,1,16);	//��ʾС������ 		   
		}				   
	 	delay_ms(10);
		t++;
		if(t==20)
		{
			t=0;
			LED0=!LED0;
		}
	}	
}


int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	SystemInit();//��ʼ��RCC ����ϵͳ��ƵΪ72MHZ
	delay_init(72);	     //��ʱ��ʼ��
	LCD_Init();	   //Һ������ʼ��
//	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
  KEY_Init();				//������ʼ�� 
	LED0=1;
	LED1=1;	
//	Sensor_Init();
	Init_DS1302();
	SPI_Flash_Init();
//	AT24CXX_Init();
//	while(TP_Init()){};  
	
 	mem_init();				//��ʼ���ڴ��	
 	exfuns_init();			//Ϊfatfs��ر��������ڴ�  
	
  f_mount(fs[0],"0:",1); 	//����SD�� 
 	f_mount(fs[1],"1:",1); 	//����FLASH.

//		music_1();
		my_show_pic();
//		my_show_time();
//		my_show_temper();

}

