#include "time.h"

void time2_Init(void)    //定时器2初始化
{
	_stm2c0=0;                 //计数频率为8MHz/4=2MHz  即计数一次为0.5us
	_stm2c1=0b11000001;		  //定时器2功能选择寄存器，选择为定时/计数器模式

	_stm2al=0x40;               //16M初值为40000，计数时间为10ms
	_stm2ah=0x9C;
	
	_stm2ae=1;                 //STM2 比较器 A 匹配中断控制位使能
	_st2on=1;                   //开启定时器
	_mf4e=1;                    //多功能中断使能
	_emi=1;                    //开启总中断	
}

//中断函数
//DEFINE_ISR(time2,0x38)
//{
//	_emi=0;                    //关闭总中断
//	time2_count++;
//	if(time2_count==100)
//	{
//		time2_count=0;
//		LED_Port=~LED_Port;           //LED1状态取反
//	}
//	_stm2af=0;            //清除定时器中断标志位
//	_emi=1;                    //开启总中断
//}