#include "time.h"

void time2_Init(void)    //��ʱ��2��ʼ��
{
	_stm2c0=0;                 //����Ƶ��Ϊ8MHz/4=2MHz  ������һ��Ϊ0.5us
	_stm2c1=0b11000001;		  //��ʱ��2����ѡ��Ĵ�����ѡ��Ϊ��ʱ/������ģʽ

	_stm2al=0x40;               //16M��ֵΪ40000������ʱ��Ϊ10ms
	_stm2ah=0x9C;
	
	_stm2ae=1;                 //STM2 �Ƚ��� A ƥ���жϿ���λʹ��
	_st2on=1;                   //������ʱ��
	_mf4e=1;                    //�๦���ж�ʹ��
	_emi=1;                    //�������ж�	
}

//�жϺ���
//DEFINE_ISR(time2,0x38)
//{
//	_emi=0;                    //�ر����ж�
//	time2_count++;
//	if(time2_count==100)
//	{
//		time2_count=0;
//		LED_Port=~LED_Port;           //LED1״̬ȡ��
//	}
//	_stm2af=0;            //�����ʱ���жϱ�־λ
//	_emi=1;                    //�������ж�
//}