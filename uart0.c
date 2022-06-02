#include "uart0.h"	
//发送一个单字符
void send_char(char s)
{
		_txr_rxr0=s;
		while(!_txif0);	
}
//发送一个字符串，注意如果发送的是字符数组，末尾必须加上'\0'，否则将会出错
void send_buff(char *s)
{
	while(*s)
	{
		send_char(*s);
		s++;
	}
}

//发送一个单字符
void send_char_unsigned(unsigned char s)
{
		_txr_rxr0=s;
		while(!_txif0);	
}


//发送一个字符串，注意如果发送的是字符数组，末尾必须加上'\0'，否则将会出错
void send_buff_unsigned(unsigned char *s)
{
	while(*s)
	{
		send_char_unsigned(*s);
		s++;
	}
}


//初始化串口0
void inituart(){
	_wdtc=0b10101111;      //关闭看门狗
	_pas1=0b11000000;      //PA7为TX0功能、PA6为RX0功能
	_u0cr1=0b10000000; //使能UART0，8-bit数据传输，关闭奇偶校验功能，1位停止位，不发送暂停字。
	_u0cr2=0b11100100;  //使能发送器，使能接收器，高速波特率，关闭地址检测功能，关闭RX0唤醒功能，使能接收器中断功能，关闭发送器空闲中断，关闭发送器已空中断
	
	_brg0=103;  //配置波特率   BR = 时钟频率 / [16 (N+1)]  所以 N = [时钟频率 / (需要的波特率×16)] - 1
	//9600(8M) : 51 4800(8M) : 103     57600(16M)  16   9600(16M)  103
 	_ur0e = 1;     //开启中断标志位
	_mf5e=1;        
	_emi=1;
}
//从串口接收一个字符串，存入数组中，停止符为c，注：接收到的串口数据最后，必须要加停止符号c，才能正确接收，并存入字符数组
int get_buff(char *rbuff,char c){
	  	int data_count=0;
	    char  rdata;
	    while(1){
    		while(!_rxif0);
	    	rdata =_txr_rxr0;
	    	if(rdata==c)
			{
				rbuff[data_count]='\0';
				return data_count;
			}
			rbuff[data_count]=rdata;
			data_count++;
	    }
}

/*
//串口中断，当有数据发送给串口时，单片机收到这个数据，并通过串口再发回去
DEFINE_ISR(UART0,0x3C)
{
 
	char buff[100]={'\0'};
	get_buff(buff,'\n');//获取一串字符串（该字符串要有换行符号）
	send_buff(buff);//把接收到的字符串再发送出去
	_ur0f = 0;	
				
}
*/