#include "uart1.h"	


//HT66F2390�����Ŷ����19ҳ��ʼ
//����һ�����ַ�
void send_char1(char s)
{
		_txr_rxr1=s;
		while(!_txif1);	
}



//����һ���ַ�����ע��������͵����ַ����飬ĩβ�������'\0'�����򽫻����
void send_buff1(char *s)
{
	while(*s)
	{
		send_char1(*s);
		s++;
	}
}



//��ʼ������1
void inituart1(){
	_wdtc = 0b10101111;
	_stm2c0=0; 
	_stm2c1|=0b00110001;	
	_pds0|=0b00101000;//PD2 TX1  PD1 RX1 ע�ⲻ��ͬһ��
	_sledc1=0x30;
	_pas0 |= 0b11000000;
	_u1cr1 |= 0b10000000;	//ʹ��UART1��8-bit���ݴ��䣬�ر���żУ�鹦�ܣ�1λֹͣλ����������ͣ�֡�
	_u1cr2 |= 0b11100100;   //����ʹ�� ѡ����ٲ�����(/16)
	_ur1e = 1;//�����жϱ�־λ
	_brg1=16;	//���ò�����   BR = ʱ��Ƶ�� / [16 (N+1)]  ���� N = [ʱ��Ƶ�� / (��Ҫ�Ĳ����ʡ�16)] - 1
	//9600(8M) : 51 4800(8M) : 103     57600(16M)  16
	_mf5e = 1;
	_emi =1;
}
//�Ӵ��ڽ���һ���ַ��������������У�ֹͣ��Ϊc��ע�����յ��Ĵ���������󣬱���Ҫ��ֹͣ����c��������ȷ���գ��������ַ�����
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



