#include "uart0.h"	
//����һ�����ַ�
void send_char(char s)
{
		_txr_rxr0=s;
		while(!_txif0);	
}
//����һ���ַ�����ע��������͵����ַ����飬ĩβ�������'\0'�����򽫻����
void send_buff(char *s)
{
	while(*s)
	{
		send_char(*s);
		s++;
	}
}

//����һ�����ַ�
void send_char_unsigned(unsigned char s)
{
		_txr_rxr0=s;
		while(!_txif0);	
}


//����һ���ַ�����ע��������͵����ַ����飬ĩβ�������'\0'�����򽫻����
void send_buff_unsigned(unsigned char *s)
{
	while(*s)
	{
		send_char_unsigned(*s);
		s++;
	}
}


//��ʼ������0
void inituart(){
	_wdtc=0b10101111;      //�رտ��Ź�
	_pas1=0b11000000;      //PA7ΪTX0���ܡ�PA6ΪRX0����
	_u0cr1=0b10000000; //ʹ��UART0��8-bit���ݴ��䣬�ر���żУ�鹦�ܣ�1λֹͣλ����������ͣ�֡�
	_u0cr2=0b11100100;  //ʹ�ܷ�������ʹ�ܽ����������ٲ����ʣ��رյ�ַ��⹦�ܣ��ر�RX0���ѹ��ܣ�ʹ�ܽ������жϹ��ܣ��رշ����������жϣ��رշ������ѿ��ж�
	
	_brg0=103;  //���ò�����   BR = ʱ��Ƶ�� / [16 (N+1)]  ���� N = [ʱ��Ƶ�� / (��Ҫ�Ĳ����ʡ�16)] - 1
	//9600(8M) : 51 4800(8M) : 103     57600(16M)  16   9600(16M)  103
 	_ur0e = 1;     //�����жϱ�־λ
	_mf5e=1;        
	_emi=1;
}
//�Ӵ��ڽ���һ���ַ��������������У�ֹͣ��Ϊc��ע�����յ��Ĵ���������󣬱���Ҫ��ֹͣ����c��������ȷ���գ��������ַ�����
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
//�����жϣ��������ݷ��͸�����ʱ����Ƭ���յ�������ݣ���ͨ�������ٷ���ȥ
DEFINE_ISR(UART0,0x3C)
{
 
	char buff[100]={'\0'};
	get_buff(buff,'\n');//��ȡһ���ַ��������ַ���Ҫ�л��з��ţ�
	send_buff(buff);//�ѽ��յ����ַ����ٷ��ͳ�ȥ
	_ur0f = 0;	
				
}
*/