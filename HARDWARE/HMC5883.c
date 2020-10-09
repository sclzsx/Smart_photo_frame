#include "HMC5883.h"
#include "math.h"

I2C_SCL SCL;
I2C_SDA SDA;
Senser5883 	Magnetic;
void delay(u32 m)
{
    while(m--)
    {
    }
}
void GPIO_Output_I2C_Configuration(GPIO_TypeDef* SDA, u16 GPIO_Pin)
{
    GPIO_InitTypeDef GPIO_Initstructure;
    GPIO_Initstructure.GPIO_Pin = GPIO_Pin;
    GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Initstructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(SDA, &GPIO_Initstructure);
}
void GPIO_Input_I2C_Configuration(GPIO_TypeDef* SDA, u16 GPIO_Pin)
{
    GPIO_InitTypeDef GPIO_Initstructure;
    GPIO_Initstructure.GPIO_Pin = GPIO_Pin;
    GPIO_Initstructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(SDA, &GPIO_Initstructure);
}
/*IIC总线启动*/
void I2C_Start ()//I2C开始
{
    GPIO_Output_I2C_Configuration(SCL.GPIOx, SCL.GPIO_Pin); //SCL置输出
    GPIO_Output_I2C_Configuration(SDA.GPIOx, SDA.GPIO_Pin); //SDA置输出
    GPIO_SetBits(SDA.GPIOx, SDA.GPIO_Pin);//SDA=1;
    delay(10);
    GPIO_SetBits(SCL.GPIOx, SCL.GPIO_Pin);//SCL=1;
    delay(10);
    GPIO_ResetBits(SDA.GPIOx, SDA.GPIO_Pin);//SDA=0;
    delay(10);
    GPIO_ResetBits(SCL.GPIOx, SCL.GPIO_Pin);//SCL=0;
    delay(10);
}

/*IIC总线结束*/
void I2C_Stop () //I2C结束
{
    GPIO_Output_I2C_Configuration(SDA.GPIOx, SDA.GPIO_Pin);  //SDA置输出
    GPIO_ResetBits(SDA.GPIOx, SDA.GPIO_Pin);//SDA=0;
    delay(10);
    GPIO_SetBits(SCL.GPIOx, SCL.GPIO_Pin);//SCL=1;
    delay(10);
    GPIO_SetBits(SDA.GPIOx, SDA.GPIO_Pin);//SDA=1;
    delay(10);
}

/*主机检查从机的响应信号*/
int I2C_Slave_ACK(void)    //  检查从机应答信号,返回0有ACK,返回1无ACK
{
    int ACK;
    u8  s1;
    GPIO_Input_I2C_Configuration(SDA.GPIOx, SDA.GPIO_Pin); //SDA置输入
    GPIO_SetBits(SCL.GPIOx, SCL.GPIO_Pin);//SCL=1;
    delay(10);
    s1 = GPIO_ReadInputDataBit(SDA.GPIOx, SDA.GPIO_Pin);
    if (s1)
    {
        ACK = 1;
    }
    else
    {
        ACK = 0;
    }
    GPIO_ResetBits(SCL.GPIOx, SCL.GPIO_Pin);//SCL=0;
    delay(10);
    return(ACK);
}

/*主机发送IIC总线上一个字节数据*/
void I2C_SendByte(u8 data)   //发送一个字节
{
    u8 i;          //发送8位
    GPIO_Output_I2C_Configuration(SDA.GPIOx, SDA.GPIO_Pin);  //SDA置输出
    for(i = 0; i < 8; i++)
    {
        if((data & 0x80) == 0x80)
        {
            GPIO_SetBits(SDA.GPIOx, SDA.GPIO_Pin);
        }//SDA=1，写 1
        else
        {
            GPIO_ResetBits(SDA.GPIOx, SDA.GPIO_Pin);
        }//SDA=0，写 0
        GPIO_SetBits(SCL.GPIOx, SCL.GPIO_Pin);  //SCL=1;
        delay(10);                     //在时钟大于4u秒期间写数据
        GPIO_ResetBits(SCL.GPIOx, SCL.GPIO_Pin);//SCL=0;
        delay(10);
        data = data << 1;
    }
}

/*主机接收IIC总线上一个字节数据*/
u8 I2C_ReciveByte(void)             //接受一个字节
{
    u8 s1 = 0, temp1 = 0;
    u8 i;
    GPIO_Input_I2C_Configuration(SDA.GPIOx, SDA.GPIO_Pin); //SDA置输入
    for(i = 0; i < 8; i++)
    {
        temp1 = temp1 << 1;
        GPIO_SetBits(SCL.GPIOx, SCL.GPIO_Pin);  //SCL=1;
        delay(10);   //在时钟大于4u秒期间读数据
        s1 = GPIO_ReadInputDataBit(SDA.GPIOx, SDA.GPIO_Pin);
        if(s1)                   //读 1
        {
            temp1 = temp1 | 0x01;
        }
        else                     //读 0
        {
            temp1 = temp1 & 0xfe;
        }
        GPIO_ResetBits(SCL.GPIOx, SCL.GPIO_Pin);//SCL=0;
        delay(10);
    }
    return(temp1);
}

/*主机向IC总线发送连续读信号*/
void I2C_ack(void)          //  发送连续读信号
{
    GPIO_Output_I2C_Configuration(SDA.GPIOx, SDA.GPIO_Pin);  //SDA置输出;
    GPIO_ResetBits(SDA.GPIOx, SDA.GPIO_Pin);//SDA=0;
    delay(10);
    GPIO_ResetBits(SCL.GPIOx, SCL.GPIO_Pin);  //SCL=1;
    delay(10);
    GPIO_ResetBits(SCL.GPIOx, SCL.GPIO_Pin);//SCL=0;
}

/*主机向IC总线发送不连续读信号*/
void I2C_nack(void)          //  发送不连续读信号
{
    GPIO_Output_I2C_Configuration(SDA.GPIOx, SDA.GPIO_Pin);  //SDA置输出 ;
    GPIO_SetBits(SDA.GPIOx, SDA.GPIO_Pin);//SDA=1;
    delay(10);
    GPIO_SetBits(SCL.GPIOx, SCL.GPIO_Pin);  //SCL=1;
    delay(10);
    GPIO_ResetBits(SCL.GPIOx, SCL.GPIO_Pin);//SCL=0;
    delay(10);
}

void Write_HMC5883(u8 Address, u8 Dat)
{
    I2C_Start();
    I2C_SendByte(HMC5883LWcmd);
    I2C_Slave_ACK();
    I2C_SendByte(Address);
    I2C_Slave_ACK();
    I2C_SendByte(Dat);
    I2C_Slave_ACK();
    I2C_Stop();
}

u8 HMC5883LRead(u8 adrr)
{
    char p;
    I2C_Start();
    I2C_SendByte(HMC5883LWcmd);
    I2C_Slave_ACK();
    I2C_SendByte(adrr);
    I2C_Slave_ACK();
    I2C_Start();
    I2C_SendByte(HMC5883LRcmd);
    I2C_Slave_ACK();
    p = I2C_ReciveByte();
    I2C_nack();
    I2C_Stop();
    return p;
}
void Sensor_Init(void)
{
    /************引脚设置******************/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
	
    SDA.GPIOx = GPIOA;
    SDA.GPIO_Pin = GPIO_Pin_13;
    SCL.GPIOx = GPIOB;
    SCL.GPIO_Pin = GPIO_Pin_4;
    /**************************************/

//     Write_HMC5883(0x00, 0x64);
//     Write_HMC5883(0x01, 0xE0);
//     Write_HMC5883(0x02, 0x00);
	  Write_HMC5883(0x00, 0x19);//75hz
    Write_HMC5883(0x01, 0xe0);//8.1gs
    Write_HMC5883(0x02, 0x00);//Continuous-Measurement Mode
}
void Sensor_Read(void)
{ 
		u16 YData, ZData,XData;
		Write_HMC5883(0x00, 0x78);
		Write_HMC5883(0x01, 0xe0);
		Write_HMC5883(0x02, 0x00);
		XData = HMC5883LRead(0x03) << 8 | HMC5883LRead(0x04);
		YData = HMC5883LRead(0x07) << 8 | HMC5883LRead(0x08);
		ZData = HMC5883LRead(0x05) << 8 | HMC5883LRead(0x06);

    Magnetic.x = (s16)XData;
    Magnetic.y = (s16)YData;
    Magnetic.z = (s16)ZData;
    Magnetic.magnetic =4.35* sqrt(pow(Magnetic.x, 2) + pow(Magnetic.y, 2) + pow(Magnetic.z, 2));
    Magnetic.Angle = atan2((double)Magnetic.y, (double)Magnetic.x) * (180 / 3.14159265) + 180;
}
