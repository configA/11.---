#include "key.h"
/*

������ʼ������
���ð���IO��Ϊpa0
��Ϊ����ģʽ����֤���ȶ��ĸߵ�ƽ
���ŵ����ã�����ͷ�ļ��и���
*/
void delay_ms(unsigned int del)						//��ʱdel*200ָ������
{	unsigned int i;									//fSYS=8MH,��ʱdel*1ms
	for(i=0;i<del;i++) GCC_DELAY(4000);
}	

void key_Init(void)   
{
	keyc =1;   //����Ϊ����ģʽ
	keyPU = 1; //PxPUn�Ĵ�������Ϊ����ģʽ		
}

int key_Scan(void)  //����ɨ�躯��
{
	if(key == 0)
	{
		delay_ms(10);  //ȥ����
		if (key == 0) 
			return 1;
		else 
			return 0;
		while(!key);  //��ⰴ���Ƿ��ɿ�
	}
	else 
		return 0;
}

