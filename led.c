#include "MyType.h"	

void LED_init()
{
	
	LED_PortC=0;					//设置 LED_Port 为输出模式
	LED_Port1=1;					//设置 LED_Port 初值 为开
	
	LED_PortC2=0;					//设置 LED_Port2 为输出模式
	LED_Port2=1;					//设置 LED_Port2 初值 为开
}
