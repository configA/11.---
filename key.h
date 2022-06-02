#ifndef __KEY_H
#define __KEY_H	

#include "HT66F2390.h"


#define key _pb5     
#define keyc _pbc5       //输入输出模式选择寄存器
#define keyPU _pbpu5     //设置为上拉模式，保证是高电平


void key_Init(void);
int key_Scan(void); 
void delay_ms(unsigned int del);						//延时del*200指令周期
#endif
