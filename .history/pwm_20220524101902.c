#include "PWM.h"

float Pwm_angle=0;
//180-387(0-90) 387-568(90-180)
//90-187(0-90) 187-284(90-180)
//��ʱ��0Ϊ����  ��ʱ��1Ϊ�±�  ��ʱ��2Ϊ�ϱ�

void inline PWM_Change_1(int dt)//���뷶Χ0-180
{
	//��CCRAдֵһ��Ҫ��д��8λ, ��д��8λ �����Ĵ���д��������̫��    ��ֵ�Ǹߵ���
	
	//CCRP�ǰ�λ�����붨ʱ���ĸ߸߰�λ���бȽ�   CCRA��16λ���붨ʱ�����е�λ���бȽ�
	
	//ͨ��Ӧ�ó���ı� 16-bit ������ֵ��Ψһ������ʹ STnON λ����������������
	//���������� ���⣬ �����������Ƚ�ƥ��Ҳ���Զ������������ ������������
	//ʱ�� ͨ���������� STM �ж��źš�
	Pwm_angle = 2.3*dt + 180;
	dt = (int)Pwm_angle;
	_ptm1al=dt&0x00ff;//PTMn CCRA ���ֽڼĴ��� bit 1~bit 0    
	_ptm1ah=dt>>8;    //PTMn CCRA ���ֽڼĴ��� bit 1~bit 0
}



void inline PWM_Change_0(int dt)//���뷶Χ0-180
{
	Pwm_angle = 2.3*dt + 180;
	dt = (int)Pwm_angle;
	_ptm0al=dt&0x00ff;//PTMn CCRA ���ֽڼĴ��� bit 1~bit 0    
	_ptm0ah=dt>>8;    //PTMn CCRA ���ֽڼĴ��� bit 1~bit 0
}

void inline PWM_Change_2(int dt)//���뷶Χ0-180
{
	Pwm_angle = 2.3*dt + 180;
	dt = (int)Pwm_angle;
	_ptm2al=dt&0x00ff;//PTMn CCRA ���ֽڼĴ��� bit 1~bit 0    
	_ptm2ah=dt>>8;    //PTMn CCRA ���ֽڼĴ��� bit 1~bit 0
}


void inline PWM_Period_Init()
{

	//�����Ͷ�ʱ��0	
//	_pfs13 = 1;
//	_pfs12 = 0;  	   //PF5����ΪPTP0���  �����
	
	_pcs05 = 1;
	_pcs04 = 0;  	   //PC2����ΪPTP0���  �һ���


	//�����Ͷ�ʱ��1	
//	_pes07=1;
//	_pes06=0;           //PE3����ΪPTP1���  ���±�
	
	_pcs11 = 1;
	_pcs10 = 0;        //PC4����ΪPTP1��� ���±�
   	
	
	//�����Ͷ�ʱ��2
//	_pds05 = 0;
//	_pds04 = 1;  	   //PD2����ΪPTP2���  ���ϱ�
	
	_pbs07 = 1;
	_pbs06 = 1;  	   //PB3����ΪPTP2���  ���ϱ�
			
	//	PTM1	PWM Output	
	_ptm1c0=0b00110100;	//  Fsys/64;	
	_ptm1c1=0b10101000;	//  PWM��� PΪ����, AΪռ�ձ� ����Ч    bit0: 0�� CCRP �C ���ڣ� CCRA �C ռ�ձ�   ���Ƚ���Pƥ��ʱ��0
	
	//  CCRP=Fsys/(64*���Ƶ��)	625--> PWM Ƶ��200Hz Ƶ��100Hz���Ͽ���������˸   ���5000  
	_ptm1rpl=5000&0xff;  //PTMn CCRP ���ֽڼĴ��� bit 7~bit 0   �������� 
	_ptm1rph=5000>>8;    //PTMn CCRP ���ֽڼĴ��� bit 7~bit 0

	_pt1on=1;
	
	



//	PTM0	PWM Output
	_ptm0c0=0b00110100;	//  Fsys/64;	
	_ptm0c1=0b10101000;	//  PWM��� PΪ����, AΪռ�ձ� ����Ч    bit0: 0�� CCRP �C ���ڣ� CCRA �C ռ�ձ�   ���Ƚ���Pƥ��ʱ��0
	
	//  CCRP=Fsys/(64*���Ƶ��)	625--> PWM Ƶ��200Hz Ƶ��100Hz���Ͽ���������˸   ���2500  
	_ptm0rpl=5000&0xff;  //PTMn CCRP ���ֽڼĴ��� bit 7~bit 0   �������� 
	_ptm0rph=5000>>8;    //PTMn CCRP ���ֽڼĴ��� bit 7~bit 0
	_pt0on=1;
	
		//	PTM2	PWM Output	
	_ptm2c0=0b00110100;	//  Fsys/64;	
	_ptm2c1=0b10101000;	//  PWM��� PΪ����, AΪռ�ձ� ����Ч    bit0: 0�� CCRP �C ���ڣ� CCRA �C ռ�ձ�   ���Ƚ���Pƥ��ʱ��0
	
	//  CCRP=Fsys/(64*���Ƶ��)	625--> PWM Ƶ��200Hz Ƶ��100Hz���Ͽ���������˸   ���2500  
	_ptm2rpl=5000&0xff;  //PTMn CCRP ���ֽڼĴ��� bit 7~bit 0   �������� 
	_ptm2rph=5000>>8;    //PTMn CCRP ���ֽڼĴ��� bit 7~bit 0

	_pt2on=1;
	
	
}


