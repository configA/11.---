#ifndef __KEY_H
#define __KEY_H	

#include "HT66F2390.h"


#define key _pb5     
#define keyc _pbc5       //�������ģʽѡ��Ĵ���
#define keyPU _pbpu5     //����Ϊ����ģʽ����֤�Ǹߵ�ƽ


void key_Init(void);
int key_Scan(void); 
void delay_ms(unsigned int del);						//��ʱdel*200ָ������
#endif
