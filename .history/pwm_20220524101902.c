#include "PWM.h"

float Pwm_angle=0;
//180-387(0-90) 387-568(90-180)
//90-187(0-90) 187-284(90-180)
//定时器0为基座  定时器1为下臂  定时器2为上臂

void inline PWM_Change_1(int dt)//输入范围0-180
{
	//对CCRA写值一定要先写低8位, 再写高8位 两个寄存器写入间隔不能太长    读值是高到低
	
	//CCRP是八位计数与定时器的高高八位进行比较   CCRA是16位的与定时器所有的位进行比较
	
	//通过应用程序改变 16-bit 计数器值的唯一方法是使 STnON 位发生上升沿跳变清
	//除计数器。 此外， 计数器溢出或比较匹配也会自动清除计数器。 上述条件发生
	//时， 通常情况会产生 STM 中断信号。
	Pwm_angle = 2.3*dt + 180;
	dt = (int)Pwm_angle;
	_ptm1al=dt&0x00ff;//PTMn CCRA 高字节寄存器 bit 1~bit 0    
	_ptm1ah=dt>>8;    //PTMn CCRA 高字节寄存器 bit 1~bit 0
}



void inline PWM_Change_0(int dt)//输入范围0-180
{
	Pwm_angle = 2.3*dt + 180;
	dt = (int)Pwm_angle;
	_ptm0al=dt&0x00ff;//PTMn CCRA 高字节寄存器 bit 1~bit 0    
	_ptm0ah=dt>>8;    //PTMn CCRA 高字节寄存器 bit 1~bit 0
}

void inline PWM_Change_2(int dt)//输入范围0-180
{
	Pwm_angle = 2.3*dt + 180;
	dt = (int)Pwm_angle;
	_ptm2al=dt&0x00ff;//PTMn CCRA 高字节寄存器 bit 1~bit 0    
	_ptm2ah=dt>>8;    //PTMn CCRA 高字节寄存器 bit 1~bit 0
}


void inline PWM_Period_Init()
{

	//周期型定时器0	
//	_pfs13 = 1;
//	_pfs12 = 0;  	   //PF5配置为PTP0输出  左基座
	
	_pcs05 = 1;
	_pcs04 = 0;  	   //PC2配置为PTP0输出  右基座


	//周期型定时器1	
//	_pes07=1;
//	_pes06=0;           //PE3配置为PTP1输出  左下臂
	
	_pcs11 = 1;
	_pcs10 = 0;        //PC4配置为PTP1输出 右下臂
   	
	
	//周期型定时器2
//	_pds05 = 0;
//	_pds04 = 1;  	   //PD2配置为PTP2输出  左上臂
	
	_pbs07 = 1;
	_pbs06 = 1;  	   //PB3配置为PTP2输出  右上臂
			
	//	PTM1	PWM Output	
	_ptm1c0=0b00110100;	//  Fsys/64;	
	_ptm1c1=0b10101000;	//  PWM输出 P为周期, A为占空比 低有效    bit0: 0： CCRP – 周期； CCRA – 占空比   当比较器P匹配时清0
	
	//  CCRP=Fsys/(64*输出频率)	625--> PWM 频率200Hz 频率100Hz以上看起来无闪烁   舵机5000  
	_ptm1rpl=5000&0xff;  //PTMn CCRP 低字节寄存器 bit 7~bit 0   配置周期 
	_ptm1rph=5000>>8;    //PTMn CCRP 高字节寄存器 bit 7~bit 0

	_pt1on=1;
	
	



//	PTM0	PWM Output
	_ptm0c0=0b00110100;	//  Fsys/64;	
	_ptm0c1=0b10101000;	//  PWM输出 P为周期, A为占空比 低有效    bit0: 0： CCRP – 周期； CCRA – 占空比   当比较器P匹配时清0
	
	//  CCRP=Fsys/(64*输出频率)	625--> PWM 频率200Hz 频率100Hz以上看起来无闪烁   舵机2500  
	_ptm0rpl=5000&0xff;  //PTMn CCRP 低字节寄存器 bit 7~bit 0   配置周期 
	_ptm0rph=5000>>8;    //PTMn CCRP 高字节寄存器 bit 7~bit 0
	_pt0on=1;
	
		//	PTM2	PWM Output	
	_ptm2c0=0b00110100;	//  Fsys/64;	
	_ptm2c1=0b10101000;	//  PWM输出 P为周期, A为占空比 低有效    bit0: 0： CCRP – 周期； CCRA – 占空比   当比较器P匹配时清0
	
	//  CCRP=Fsys/(64*输出频率)	625--> PWM 频率200Hz 频率100Hz以上看起来无闪烁   舵机2500  
	_ptm2rpl=5000&0xff;  //PTMn CCRP 低字节寄存器 bit 7~bit 0   配置周期 
	_ptm2rph=5000>>8;    //PTMn CCRP 高字节寄存器 bit 7~bit 0

	_pt2on=1;
	
	
}


