#include "key.h"
/*

按键初始化函数
设置按键IO口为pa0
且为上拉模式，保证有稳定的高电平
引脚的设置，进入头文件中更改
*/
void delay_ms(unsigned int del)						//延时del*200指令周期
{	unsigned int i;									//fSYS=8MH,延时del*1ms
	for(i=0;i<del;i++) GCC_DELAY(4000);
}	

void key_Init(void)   
{
	keyc =1;   //设置为输入模式
	keyPU = 1; //PxPUn寄存器设置为上拉模式		
}

int key_Scan(void)  //按键扫描函数
{
	if(key == 0)
	{
		delay_ms(10);  //去抖动
		if (key == 0) 
			return 1;
		else 
			return 0;
		while(!key);  //检测按键是否松开
	}
	else 
		return 0;
}

