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

/*引脚分配
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



u8 key;				//键值


u16 pic_get_tnum(u8 *path)
{	  
	u8 res;
	u16 rval=0;
 	DIR tdir;	 		//临时目录
	FILINFO tfileinfo;	//临时文件信息	
	u8 *fn;	 			 			   			     
    res=f_opendir(&tdir,(const TCHAR*)path); 	//打开目录
  	tfileinfo.lfsize=_MAX_LFN*2+1;				//长文件名最大长度
	tfileinfo.lfname=mymalloc(tfileinfo.lfsize);//为长文件缓存区分配内存
	if(res==FR_OK&&tfileinfo.lfname!=NULL)
	{
		while(1)//查询总的有效文件数
		{
	        res=f_readdir(&tdir,&tfileinfo);       		//读取目录下的一个文件
	        if(res!=FR_OK||tfileinfo.fname[0]==0)break;	//错误了/到末尾了,退出		  
     		fn=(u8*)(*tfileinfo.lfname?tfileinfo.lfname:tfileinfo.fname);			 
			res=f_typetell(fn);	
			if((res&0XF0)==0X50)//取高四位,看看是不是图片文件	
			{
				rval++;//有效文件数增加1
			}	    
		}  
	} 
	return rval;
}


void my_show_pic(void)
{
	u8 res;
 	DIR picdir;	 		//图片目录
	FILINFO picfileinfo;//文件信息
	u8 *fn;   			//长文件名
	u8 *pname;			//带路径的文件名
	u16 totpicnum; 		//图片文件总数
	u16 curindex;		//图片当前索引
	u8 pause=0;			//暂停标记
	u8 t;
	u16 temp;
	u16 *picindextbl;	//图片索引表 		 
	
	POINT_COLOR=RED;      
 	while(font_init()) 	//检查字库
	{	    
		LCD_ShowString(60,50,200,16,16,"Font Error!");
		delay_ms(200);				  
		LCD_Fill(60,50,240,66,WHITE);//清除显示	     
		delay_ms(200);				  
	}  	 
 	Show_Str(60,50,200,16,"Mini STM32开发板",16,0);				    	 
	Show_Str(60,70,200,16,"图片显示程序",16,0);				    	 
	Show_Str(60,90,200,16,"KEY0:NEXT KEY1:PREV",16,0);				    	 
	Show_Str(60,110,200,16,"WK_UP:PAUSE",16,0);				    	 
	Show_Str(60,130,200,16,"正点原子@ALIENTEK",16,0);				    	 
	Show_Str(60,150,200,16,"2014年3月14日",16,0);
	
 	while(f_opendir(&picdir,"0:/PICTURE"))//打开图片文件夹
 	{	    
		Show_Str(60,170,240,16,"PICTURE文件夹错误!",16,0);
		delay_ms(200);				  
		LCD_Fill(60,170,240,186,WHITE);//清除显示	     
		delay_ms(200);				  
	}  
	totpicnum=pic_get_tnum("0:/PICTURE"); //得到总有效文件数
  	while(totpicnum==NULL)//图片文件为0		
 	{	    
		Show_Str(60,170,240,16,"没有图片文件!",16,0);
		delay_ms(200);				  
		LCD_Fill(60,170,240,186,WHITE);//清除显示	     
		delay_ms(200);				  
	}
	
  picfileinfo.lfsize=_MAX_LFN*2+1;						//长文件名最大长度
	picfileinfo.lfname=mymalloc(picfileinfo.lfsize);	//为长文件缓存区分配内存
 	pname=mymalloc(picfileinfo.lfsize);				//为带路径的文件名分配内存
 	picindextbl=mymalloc(2*totpicnum);				//申请2*totpicnum个字节的内存,用于存放图片索引
 	while(picfileinfo.lfname==NULL||pname==NULL||picindextbl==NULL)//内存分配出错
 	{	    
		Show_Str(60,170,240,16,"内存分配失败!",16,0);
		delay_ms(200);				  
		LCD_Fill(60,170,240,186,WHITE);//清除显示	     
		delay_ms(200);				  
	}  	
	//记录索引
    res=f_opendir(&picdir,"0:/PICTURE"); //打开目录
	if(res==FR_OK)
	{
		curindex=0;//当前索引为0
		while(1)//全部查询一遍
		{
			temp=picdir.index;								//记录当前index
	        res=f_readdir(&picdir,&picfileinfo);       		//读取目录下的一个文件
	        if(res!=FR_OK||picfileinfo.fname[0]==0)break;	//错误了/到末尾了,退出		  
     		fn=(u8*)(*picfileinfo.lfname?picfileinfo.lfname:picfileinfo.fname);			 
			res=f_typetell(fn);	
			if((res&0XF0)==0X50)//取高四位,看看是不是图片文件	
			{
				picindextbl[curindex]=temp;//记录索引
				curindex++;
			}	    
		} 
	}
	
	Show_Str(60,170,240,16,"开始显示...",16,0); 
	delay_ms(1500);
	piclib_init();										//初始化画图	   	   
	curindex=0;											//从0开始显示
   	res=f_opendir(&picdir,(const TCHAR*)"0:/PICTURE"); 	//打开目录
	while(res==FR_OK)//打开成功
	{	
		dir_sdi(&picdir,picindextbl[curindex]);			//改变当前目录索引	   
        res=f_readdir(&picdir,&picfileinfo);       		//读取目录下的一个文件
        if(res!=FR_OK||picfileinfo.fname[0]==0)break;	//错误了/到末尾了,退出
     	fn=(u8*)(*picfileinfo.lfname?picfileinfo.lfname:picfileinfo.fname);			 
		strcpy((char*)pname,"0:/PICTURE/");				//复制路径(目录)
		strcat((char*)pname,(const char*)fn);  			//将文件名接在后面
 		LCD_Clear(BLACK);
 		ai_load_picfile(pname,0,0,lcddev.width,lcddev.height,1);//显示图片    
		Show_Str(2,2,240,16,pname,16,1); 				//显示图片名字
		t=0;
		
		while(1) 
		{
			key=KEY_Scan(0);		//扫描按键
			if(t>250)key=1;			//模拟一次按下KEY0    
			if((t%20)==0)LED0=!LED0;//LED0闪烁,提示程序正在运行.
			if(key==KEY1_PRES)		//上一张
			{
				if(curindex)curindex--;
				else curindex=totpicnum-1;
				break;
			}else if(key==KEY0_PRES)//下一张
			{
				curindex++;		   	
				if(curindex>=totpicnum)curindex=0;//到末尾的时候,自动从头开始
				break;
			}else if(key==WKUP_PRES)
			{
				pause=!pause;
				LED1=!pause; 	//暂停的时候LED1亮.  
			}
			if(pause==0)t++;
			delay_ms(10); 
		}					    
		res=0;  
	} 											  
	myfree(picfileinfo.lfname);	//释放内存			    
	myfree(pname);				//释放内存			    
	myfree(picindextbl);		//释放内存			 	
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
 	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString1(60,50,16,"Mini STM32",0);	
	LCD_ShowString1(60,70,16,"DS18B20 TEST",0);	
	LCD_ShowString1(60,90,16,"ATOM@ALIENTEK",0);
	LCD_ShowString1(60,110,16,"2014/3/12",0);		  
 	while(DS18B20_Init())	//DS18B20初始化	
	{
		LCD_ShowString1(60,130,16,"DS18B20 Error",0);
		delay_ms(200);
		LCD_Fill(60,130,239,130+16,WHITE);
 		delay_ms(200);
	}								   
	LCD_ShowString1(60,130,16,"DS18B20 OK",0);
	POINT_COLOR=BLUE;//设置字体为蓝色 
 	LCD_ShowString1(60,150,16,"Temp:   . C",0);	 
	while(1)
	{	    	    
 		if(t%10==0)//每100ms读取一次
		{									  
			temperature=DS18B20_Get_Temp();	
			if(temperature<0)
			{
				LCD_ShowChar1(60+40,150,POINT_COLOR,BACK_COLOR,'-',16,0);			//显示负号
				temperature=-temperature;					//转为正数
			}else LCD_ShowChar1(60+40,150,POINT_COLOR,BACK_COLOR,' ',16,0);			//去掉负号
			LCD_ShowNum(60+40+8,150,temperature/10,2,16);	//显示正数部分	    
   			LCD_ShowNum(60+40+32,150,temperature%10,1,16);	//显示小数部分 		   
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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	SystemInit();//初始化RCC 设置系统主频为72MHZ
	delay_init(72);	     //延时初始化
	LCD_Init();	   //液晶屏初始化
//	uart_init(9600);	 	//串口初始化为9600
  KEY_Init();				//按键初始化 
	LED0=1;
	LED1=1;	
//	Sensor_Init();
	Init_DS1302();
	SPI_Flash_Init();
//	AT24CXX_Init();
//	while(TP_Init()){};  
	
 	mem_init();				//初始化内存池	
 	exfuns_init();			//为fatfs相关变量申请内存  
	
  f_mount(fs[0],"0:",1); 	//挂载SD卡 
 	f_mount(fs[1],"1:",1); 	//挂载FLASH.

//		music_1();
		my_show_pic();
//		my_show_time();
//		my_show_temper();

}

