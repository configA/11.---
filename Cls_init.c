#include "Cls_init.h"



void Cls_init()
{
	_wdtc=0b10101111;				//�ؿ��Ź�
	_emi=1;                    //�������ж�
	_rstc=0b10101010;				//Ϊ����ֵ�ϵ��Զ���λһ��
	_hircc |= 0b00001000;//ʱ��Ƶ��Ϊ16M
	inituart();//����0��ʼ��
	//inituart1();//����1��ʼ��
	key_Init();//������ʼ��
	LED_init();//LED��ʼ��
	time2_Init();//��ʱ��2��ʼ��
	
	//---MUP-6050��ʼ��
//	IIC_init();//iic��ʼ��
//	initMPU6050();//6050��ʼ��
//	
//	
//	if (getDeviceID())	//��֤�����Ƿ�����(��ȡMPU6050��I2C��ַ)
//	{
//		send_buff("��֤�ɹ�\r\n");
//		if(!(dmpInitialize()))	//���ز������˶���
//			while(1);		
//	}
//	writeBit(0x6A,2,1);	//��λ FIFO
//	delay_ms(30);
//	writeBit(0x6A,7,1);	//ʹ��DMP
//	send_buff("���ز������˶���ɹ�\r\n");
	
	//---�����ʼ��
	PWM_Period_Init(); //Ĭ��PTM��ʱ��0ΪPC2 Ĭ��PTM��ʱ��1ΪPC4 Ĭ��PTM��ʱ��2ΪPB3
	
}



