#ifndef __HMC5883_H
#define __HMC5883_H
#include <stm32f10x.h>
#include <stdio.h>
#define			ADXL345Wcmd			0xa6
#define			ADXL345Rcmd			0xa7
#define			HMC5883LWcmd		0x3c
#define			HMC5883LRcmd		0x3d
typedef struct
{
    GPIO_TypeDef* GPIOx;
    u16 GPIO_Pin;
} I2C_SCL;

typedef struct
{
    GPIO_TypeDef* GPIOx;
    u16 GPIO_Pin;
} I2C_SDA;

typedef struct
{
    s16 x;
    s16 y;
    s16 z;
    float Angle;
    float magnetic;

} Senser5883;

extern Senser5883 	Magnetic;
void Sensor_Init(void);//引脚设置，请看此函数。
void Sensor_Read(void);
void delay_us(u32 m);
#endif
