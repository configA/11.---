#include "Cls_init.h"



void Cls_init()
{
	_wdtc=0b10101111;				//关看门狗
	_emi=1;                    //开启总中断
	_rstc=0b10101010;				//为其他值上电自动复位一次
	_hircc |= 0b00001000;//时钟频率为16M
	inituart();//串口0初始化
	//inituart1();//串口1初始化
	key_Init();//按键初始化
	LED_init();//LED初始化
	time2_Init();//定时器2初始化
	
	//---MUP-6050初始化
//	IIC_init();//iic初始化
//	initMPU6050();//6050初始化
//	
//	
//	if (getDeviceID())	//验证连接是否正常(读取MPU6050的I2C地址)
//	{
//		send_buff("验证成功\r\n");
//		if(!(dmpInitialize()))	//加载并配置运动库
//			while(1);		
//	}
//	writeBit(0x6A,2,1);	//复位 FIFO
//	delay_ms(30);
//	writeBit(0x6A,7,1);	//使能DMP
//	send_buff("加载并配置运动库成功\r\n");
	
	//---舵机初始化
	PWM_Period_Init(); //默认PTM定时器0为PC2 默认PTM定时器1为PC4 默认PTM定时器2为PB3
	
}



