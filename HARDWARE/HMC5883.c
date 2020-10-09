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
/*IIC��������*/
void I2C_Start ()//I2C��ʼ
{
    GPIO_Output_I2C_Configuration(SCL.GPIOx, SCL.GPIO_Pin); //SCL�����
    GPIO_Output_I2C_Configuration(SDA.GPIOx, SDA.GPIO_Pin); //SDA�����
    GPIO_SetBits(SDA.GPIOx, SDA.GPIO_Pin);//SDA=1;
    delay(10);
    GPIO_SetBits(SCL.GPIOx, SCL.GPIO_Pin);//SCL=1;
    delay(10);
    GPIO_ResetBits(SDA.GPIOx, SDA.GPIO_Pin);//SDA=0;
    delay(10);
    GPIO_ResetBits(SCL.GPIOx, SCL.GPIO_Pin);//SCL=0;
    delay(10);
}

/*IIC���߽���*/
void I2C_Stop () //I2C����
{
    GPIO_Output_I2C_Configuration(SDA.GPIOx, SDA.GPIO_Pin);  //SDA�����
    GPIO_ResetBits(SDA.GPIOx, SDA.GPIO_Pin);//SDA=0;
    delay(10);
    GPIO_SetBits(SCL.GPIOx, SCL.GPIO_Pin);//SCL=1;
    delay(10);
    GPIO_SetBits(SDA.GPIOx, SDA.GPIO_Pin);//SDA=1;
    delay(10);
}

/*�������ӻ�����Ӧ�ź�*/
int I2C_Slave_ACK(void)    //  ���ӻ�Ӧ���ź�,����0��ACK,����1��ACK
{
    int ACK;
    u8  s1;
    GPIO_Input_I2C_Configuration(SDA.GPIOx, SDA.GPIO_Pin); //SDA������
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

/*��������IIC������һ���ֽ�����*/
void I2C_SendByte(u8 data)   //����һ���ֽ�
{
    u8 i;          //����8λ
    GPIO_Output_I2C_Configuration(SDA.GPIOx, SDA.GPIO_Pin);  //SDA�����
    for(i = 0; i < 8; i++)
    {
        if((data & 0x80) == 0x80)
        {
            GPIO_SetBits(SDA.GPIOx, SDA.GPIO_Pin);
        }//SDA=1��д 1
        else
        {
            GPIO_ResetBits(SDA.GPIOx, SDA.GPIO_Pin);
        }//SDA=0��д 0
        GPIO_SetBits(SCL.GPIOx, SCL.GPIO_Pin);  //SCL=1;
        delay(10);                     //��ʱ�Ӵ���4u���ڼ�д����
        GPIO_ResetBits(SCL.GPIOx, SCL.GPIO_Pin);//SCL=0;
        delay(10);
        data = data << 1;
    }
}

/*��������IIC������һ���ֽ�����*/
u8 I2C_ReciveByte(void)             //����һ���ֽ�
{
    u8 s1 = 0, temp1 = 0;
    u8 i;
    GPIO_Input_I2C_Configuration(SDA.GPIOx, SDA.GPIO_Pin); //SDA������
    for(i = 0; i < 8; i++)
    {
        temp1 = temp1 << 1;
        GPIO_SetBits(SCL.GPIOx, SCL.GPIO_Pin);  //SCL=1;
        delay(10);   //��ʱ�Ӵ���4u���ڼ������
        s1 = GPIO_ReadInputDataBit(SDA.GPIOx, SDA.GPIO_Pin);
        if(s1)                   //�� 1
        {
            temp1 = temp1 | 0x01;
        }
        else                     //�� 0
        {
            temp1 = temp1 & 0xfe;
        }
        GPIO_ResetBits(SCL.GPIOx, SCL.GPIO_Pin);//SCL=0;
        delay(10);
    }
    return(temp1);
}

/*������IC���߷����������ź�*/
void I2C_ack(void)          //  �����������ź�
{
    GPIO_Output_I2C_Configuration(SDA.GPIOx, SDA.GPIO_Pin);  //SDA�����;
    GPIO_ResetBits(SDA.GPIOx, SDA.GPIO_Pin);//SDA=0;
    delay(10);
    GPIO_ResetBits(SCL.GPIOx, SCL.GPIO_Pin);  //SCL=1;
    delay(10);
    GPIO_ResetBits(SCL.GPIOx, SCL.GPIO_Pin);//SCL=0;
}

/*������IC���߷��Ͳ��������ź�*/
void I2C_nack(void)          //  ���Ͳ��������ź�
{
    GPIO_Output_I2C_Configuration(SDA.GPIOx, SDA.GPIO_Pin);  //SDA����� ;
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
    /************��������******************/
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
