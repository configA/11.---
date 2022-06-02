#include "uart1.h"	


//HT66F2390的引脚定义从19页开始
//发送一个单字符
void send_char1(char s)
{
		_txr_rxr1=s;
		while(!_txif1);	
}



//发送一个字符串，注意如果发送的是字符数组，末尾必须加上'\0'，否则将会出错
void send_buff1(char *s)
{
	while(*s)
	{
		send_char1(*s);
		s++;
	}
}



//初始化串口1
void inituart1(){
	_wdtc = 0b10101111;
	_stm2c0=0; 
	_stm2c1|=0b00110001;	
	_pds0|=0b00101000;//PD2 TX1  PD1 RX1 注意不在同一行
	_sledc1=0x30;
	_pas0 |= 0b11000000;
	_u1cr1 |= 0b10000000;	//使能UART1，8-bit数据传输，关闭奇偶校验功能，1位停止位，不发送暂停字。
	_u1cr2 |= 0b11100100;   //接收使能 选择高速波特率(/16)
	_ur1e = 1;//开启中断标志位
	_brg1=16;	//配置波特率   BR = 时钟频率 / [16 (N+1)]  所以 N = [时钟频率 / (需要的波特率×16)] - 1
	//9600(8M) : 51 4800(8M) : 103     57600(16M)  16
	_mf5e = 1;
	_emi =1;
}
//从串口接收一个字符串，存入数组中，停止符为c，注：接收到的串口数据最后，必须要加停止符号c，才能正确接收，并存入字符数组
int get_buff1(char *rbuff,char c){
	  	int data_count=0;
	    char  rdata;
	    while(1){
    		while(!_rxif1); 
	    	rdata =_txr_rxr1;
	    	if(rdata==c)
			{
				rbuff[data_count]='\0';
				return data_count;
			}
			rbuff[data_count]=rdata;
			data_count++;
	    }
}



