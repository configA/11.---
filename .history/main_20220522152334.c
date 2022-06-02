#include "Cls_init.h"
#define q30  1073741824.0f    //2��30�η� ����ŷ����ʱ��Ҫ

//-----��Ҫ��������
//void MUP_6060_READ();
void Control_Angle();//�������ƽǶ�
//-----���ڱ���
char Bluetooth=0;//����������ȡ���յ��ĵ�һ����������
char buff_text[50]={'\0'};//���ڴ�ӡ�ַ�������
char linshi[50]={'\0'};
//-----��ʱ������
unsigned int time2_count=0;//��ʱ������
unsigned int mpu6050_delay=0;//6050���ٺ���
unsigned int mechanical_delay=0;//��е�ۼ���
//-----MPU-6050����
//float mup6050_angle[3];// 0:������ 1:����� 2:ƫ���� 
unsigned char dmpdatas[42]={'\0'};	//DMP����
unsigned char zd=0,i=0;
long quat[4]={0};
float q0=1.0,q1=0.0,q2=0.0,q3=0.0;
float pitch=0,roll=0,yaw=0; //ŷ����
int pos0=90,pos1=90,pos2=90;//�Ƕ�
int pos0_old=90,pos1_old=90,pos2_old=90;//��һ�εĽǶ�
/*************������*************/
void main()
{		
	Cls_init();
	pos0 = 171; pos1 = 146; pos2 = 144;
	_pt0on=1;
	PWM_Change_0(pos0);
	delay_ms(1000);
	_pt0on=0;//�رջ���
	PWM_Change_1(pos1);
	delay_ms(1000);
	PWM_Change_2(pos2);	
	
	while(1)
	{
		//MUP_6060_READ();//SDA PF2 SCL PF3
		Control_Angle();
		//���� L(˳ʱ��)  R(��ʱ��) 
		//�±� D(��)      U(��)
		//�ϱ� B(��)      T(��) 
		//ͷֱ���˶�  S   �����˶� C    Gͷ������
	}
}



/*************��ʱ��2�ж�10ms(16M)��һ�� *************/
DEFINE_ISR(time2,0x38)
{
	_emi=0;                    //�ر����ж�
	time2_count++;
	if(time2_count==100)
	{
		time2_count=0;
		LED_Port1=~LED_Port1;           //LED1״̬ȡ��
	}
	if(++mpu6050_delay == 3) mpu6050_delay = 0;
	if(++ mechanical_delay== 3) mechanical_delay = 0;
	_stm2af=0;            //�����ʱ���жϱ�־λ
	_emi=1;                    //�������ж�
}


/*************�����ж�*************/
DEFINE_ISR(UART,0x3C)
{
	char buff[50]={'\0'};
 	if(_ur0f == 1)            //������һ��������ʱ��Ҳ����˵�е�����Ԥ��
	{	
		get_buff(buff,'\n');//��ȡһ���ַ��������ַ���Ҫ�л��з��ţ�'\n'=0x0A
		send_buff(buff);//����
		Bluetooth = buff[0];
	}
	
 	if(_ur1f == 1)            //������һ��������ʱ��Ҳ����˵�е�����Ԥ��
	{	
		get_buff1(buff,'\n');//��ȡһ���ַ��������ַ���Ҫ�л��з��ţ�'\n'=0x0A
		send_buff1(buff);//����
		Bluetooth = buff[0];
		//send_buff1(buff);//�ѽ��յ����ַ����ٷ��ͳ�ȥ
		
	}	
	_ur0f = 0;	
	_ur1f = 0;				
}




/*************6050���ݶ�ȡ*************/
void MUP_6060_READ()
{
	if(mpu6050_delay) return; //200ms����һ��
	else mpu6050_delay = 1;
	PWM_Change_0(0);
	PWM_Change_1(0);
		i=getFIFOCount();//��ȡFIFO����
	 	i2cread(0x3A,&zd);	//��ȡ�ж�״̬
	 	if((zd & 0x10)||i==1024)	//�ж�FIFO�Ƿ����
	 	{
	    	writeBit(0x6A,2,1);	//��λ FIFO
		}
		else if (zd & 0x02)
		{
	    	while(i<42) i=getFIFOCount();//��ȡFIFO����
			readdmp(dmpdatas);	//��ȡFIFO����(��Ԫ��+����������)
			
			//������Ԫ��
			quat[0] = ((long)dmpdatas[0] << 24) | ((long)dmpdatas[1] << 16) |
	            ((long)dmpdatas[2] << 8) | dmpdatas[3];
			quat[1] = ((long)dmpdatas[4] << 24) | ((long)dmpdatas[5] << 16) |
	            ((long)dmpdatas[6] << 8) | dmpdatas[7];
	    	quat[2] = ((long)dmpdatas[8] << 24) | ((long)dmpdatas[9] << 16) |
	            ((long)dmpdatas[10] << 8) | dmpdatas[11];
	    	quat[3] = ((long)dmpdatas[12] << 24) | ((long)dmpdatas[13] << 16) |
	            ((long)dmpdatas[14] << 8) | dmpdatas[15];
			//������Ԫ��
			q0 = quat[0] / q30;	//q30��ʽת��Ϊ������
			q1 = quat[1] / q30;
			q2 = quat[2] / q30;
			q3 = quat[3] / q30; 
	
			//57.3�ǻ���ת�Ƕ� 180/pi
			pitch = asin(-2 * q1 * q3 + 2 * q0* q2)* 57.3;	// pitch
			roll  = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1)* 57.3;	// roll 
			yaw   = atan2(2*(q1*q2 + q0*q3),q0*q0+q1*q1-q2*q2-q3*q3) * 57.3;	//yaw


//			������ʾ			
//			send_buff("������=");
//			send_buff(Int2String((int)pitch,buff_text));
//			
//			send_buff("�����=");
//			send_buff(Int2String((int)roll,buff_text));
//			
//			send_buff("ƫ����=");
//			send_buff(Int2String((int)yaw,buff_text));
//			send_buff("\r\n");	

//			��������ʾ			
			send_buff("������=");
			send_buff(Float2String(pitch,buff_text));
			
			send_buff("�����=");
			send_buff(Float2String(roll,buff_text));
			
			send_buff("ƫ����=");
			send_buff(Float2String(yaw,buff_text));
			send_buff("\r\n");	
		}					
}


//90-187(0-90) 187-284(90-180)
//��ʱ��0Ϊ����  ��ʱ��1Ϊ�±�  ��ʱ��2Ϊ�ϱ�
void Control_Angle()
{
	if(mechanical_delay) return; //200ms����һ��
	else mechanical_delay = 1;
	//---------------------------------���ؿ���	----------------------------------//
	if(Bluetooth == 'R')
	{
		Bluetooth = 0;
		if(pos0 >= 10)
		{
			_pt0on=1;//�򿪻���
			pos0--;
			PWM_Change_0(pos0);
			delay_ms(10);
			_pt0on=0;//�رջ���
		}	
	}
	if(Bluetooth == 'L')
	{
		Bluetooth = 0;
		if(pos0 <= 170)
		{
			_pt0on=1;//�򿪻���
			pos0++;
			PWM_Change_0(pos0);
			delay_ms(10);
			_pt0on=0;//�رջ���
		}	
	}
	//---------------------------------�±ڿ���	----------------------------------//
		if(Bluetooth == 'D')//����
	{
		if(pos1 >= 10)
		{
			Bluetooth = 0;
			pos1--;
			PWM_Change_1(pos1);
			delay_ms(10);
		}	
	}
	if(Bluetooth == 'U')//����
	{
		Bluetooth = 0;
		if(pos1 <= 170)
		{
			pos1++;
			PWM_Change_1(pos1);
			delay_ms(10);
		}	
	}
	//---------------------------------�ϱۿ���	----------------------------------//
	if(Bluetooth == 'B')//����
	{
		Bluetooth = 0;
		if(pos2 >= 10)
		{
			pos2--;
			PWM_Change_2(pos2);
			delay_ms(10);
		}	
	}
	if(Bluetooth == 'T')//����
	{
		Bluetooth = 0;
		if(pos2 <= 170)
		{
			pos2++;
			PWM_Change_2(pos2);
			delay_ms(10);
		}	
	}
	if(Bluetooth == 'M')//��λ
	{
		Bluetooth = 0;
		pos0=90;
		pos1=90;
		pos2=90;
		_pt0on=1;
		PWM_Change_0(pos0);
		delay_ms(500);
		_pt0on=0;
		PWM_Change_1(pos1);
		delay_ms(500);
		PWM_Change_2(pos2);
		delay_ms(500);
			
	}

	f(Bluetooth == 'G')//��λ
	{
		Bluetooth = 0;
		pos0=171;
		pos1=146;
		pos2=144;
		_pt0on=1;
		PWM_Change_0(pos0);
		delay_ms(500);
		_pt0on=0;
		PWM_Change_1(pos1);
		delay_ms(500);
		PWM_Change_2(pos2);
		delay_ms(500);
			
	}
	if(Bluetooth == 'S')//ֱ���˶�
	{
		Bluetooth = 0;
		if((pos1 >= 50) && (pos2 <= 170))
		{
			pos1--;
			pos2++;
			PWM_Change_1(pos1);
			PWM_Change_2(pos2);
			delay_ms(10);
		}
	}

	if(Bluetooth == 'C')//�����˶�
	{
		Bluetooth = 0;
		if((pos1 >= 50) && (pos2 >= 50))
		{
			pos1--;
			pos2--;
			PWM_Change_1(pos1);
			PWM_Change_2(pos2);
			delay_ms(10);
		}
	}

	if((pos0_old != pos0) || (pos1_old != pos1) || (pos2_old != pos2))
	{
		send_buff(Int2String(pos0,linshi));
		send_buff("   ");
		send_buff(Int2String(pos1,linshi));
		send_buff("   ");
		send_buff(Int2String(pos2,linshi));
		send_buff("\r\n");	
	}
	pos0_old = pos0; pos1_old = pos1; pos2_old = pos2;
		
}

