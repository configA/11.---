#include "mpu_6050.h"
char buff_text[50];


float q0 = 1, q1 = 0, q2 = 0, q3 = 0;
float exInt = 0, eyInt = 0, ezInt = 0;
float Yaw=1;	//roll��Χ��Z����ת��Ҳ�з�����
float Roll=1;	//yawΧ��Y����ת����ƫ����
float Pitch=1; //pitchΧ��X����ת������������



void IIC_init()//IIC��ʼ��
{

	SDA_set=0;//���
	SCL_set=0;//���
	SCL_pin=1;
	SDA_pin=1;
	SDA_up_set=1;
}


/*******************************************************************************
* ������         : Delay2us()
* ��������		   : ��ʱ
* ����           : ��
* ���         	 : ��
*******************************************************************************/
//8��asm����4��39  ָ������Ϊ4��ʱ������ ��������Ϊ8��ʱ������
//ʱ������0.125us
void IIC_delay2us()
{		
	asm("nop");//һ����������1us
	asm("nop");
}

void IIC_delay5us()
{		
	asm("nop");  	asm("nop");//һ����������1us
	asm("nop");		asm("nop");
	asm("nop");
}


/*******************************************************************************
* ������         : I2cStart()
* ��������		   : ��ʼ�źţ���SCL_pinʱ���ź��ڸߵ�ƽ�ڼ�SDA_pin�źŲ���һ���½���
* ����           : ��
* ���         	 : ��
* ��ע           : ��ʼ֮��SDA_pin��SCL_pin��Ϊ0
*******************************************************************************/
void IIC_Start()	//SCL ���Ǹߵ�ƽʱ��SDA �ߴӸߵ�ƽ��͵�ƽ�л���ʾ��ʼ������
{
//	SDA_pin=1;
//	SCL_pin=1;
//	IIC_delay5us();//����ʱ����SDA_pin����ʱ��>4.7us
//	SDA_pin=0;
//	IIC_delay5us();	
//	SCL_pin=0;		
	
	SDA_pin=1;
	IIC_delay2us();
	SCL_pin=1;
	IIC_delay5us();//����ʱ����SDA_pin����ʱ��>4.7us
	IIC_delay2us();	
	SDA_pin=0;
	IIC_delay5us();//����ʱ����>4us
	IIC_delay2us();
	SCL_pin=0;		
	IIC_delay2us();	
	
}


/*******************************************************************************
* ������         : I2cStop()
* ��������		   : ��ֹ�źţ���SCL_pinʱ���źŸߵ�ƽ�ڼ�SDA_pin�źŲ���һ��������
* ����           : ��
* ���         	 : ��
* ��ע           : ����֮�󱣳�SDA_pin��SCL_pin��Ϊ1����ʾ���߿���
*******************************************************************************/

void IIC_Stop()
{
//	SDA_pin=0;
//	SCL_pin=1;
//	IIC_delay5us();//����ʱ�����4.7us
//	SDA_pin=1;
//	IIC_delay5us();
//	SCL_pin=0;
//	IIC_delay2us();

	SDA_pin=0;
	IIC_delay5us();
	SCL_pin=1;
	IIC_delay5us();//����ʱ�����4.7us
	SDA_pin=1;
	IIC_delay5us();
	IIC_delay2us();	
	SCL_pin=0;
	IIC_delay2us();
}

/*******************************************************************************
* ������         : I2cSendByte(unsigned char num)
* ��������		   : ͨ��I2C����һ���ֽڡ���SCL_pinʱ���źŸߵ�ƽ�ڼ䣬���ַ����ź�SDA_pin�����ȶ�
* ����           : num
* ���         	 : 0��1�����ͳɹ�����1������ʧ�ܷ���0
* ��ע           : ������һ���ֽ�SCL_pin=0,SDA_pin=1
*******************************************************************************/

unsigned char IIC_SendBuye(unsigned char dat)
{
	unsigned char a=0,b=0;//���255��һ����������Ϊ1us�������ʱ255us��		
	for(a=0;a<8;a++)//Ҫ����8λ�������λ��ʼ
	{
		SDA_pin=dat>>7;	 //��ʼ�ź�֮��SCL_pin=0�����Կ���ֱ�Ӹı�SDA_pin�ź�
		dat=dat<<1;
		IIC_delay2us();
		SCL_pin=1;
		IIC_delay5us();//����ʱ��>4.7us
		SCL_pin=0;
		IIC_delay5us();//ʱ�����4us		
	}
	SDA_pin=1;
	IIC_delay5us();
	SDA_set=1;
	SCL_pin=1;
//	send_buff("2");
	while(SDA_pin)//�ȴ�Ӧ��Ҳ���ǵȴ����豸��SDA_pin����
	{
		b++;
		if(b>200)	 //�������2000usû��Ӧ����ʧ�ܣ�����Ϊ��Ӧ�𣬱�ʾ���ս���
		{
			SCL_pin=0;
			IIC_delay2us();
			return 0;
		}
	}
//	send_buff("1");
	SCL_pin=0;
	IIC_delay2us();
	SDA_set=0;
 	return 1;		
}

/*******************************************************************************
* ������         : I2cReadByte()
* ��������		   : ʹ��I2c��ȡһ���ֽ�
* ����           : ��
* ���         	 : dat
* ��ע           : ������һ���ֽ�SCL_pin=0,SDA_pin=1.
*******************************************************************************/

unsigned char IIC_RecvByte()
{
	unsigned char a=0,dat=0;
	SDA_pin=1;			//��ʼ�ͷ���һ���ֽ�֮��SCL_pin����0
	IIC_delay2us();
	SDA_set=1;
	for(a=0;a<8;a++)//����8���ֽ�
	{
		SCL_pin=1;
		IIC_delay2us();
		dat<<=1;
		dat|=SDA_pin;
		IIC_delay5us();
		SCL_pin=0;
		IIC_delay5us();
	}
	SDA_set=0;
	return dat;		
}


void IIC_NAck(){
//		SDA_pin = 0;                    //д��Ӧ���ź�
//		SCL_pin = 1;              
//		IIC_delay5us();	               
//		SCL_pin = 0;                    
//		IIC_delay5us();
		SDA_pin = 0;                    //д��Ӧ���ź�
		SCL_pin = 1;              
		IIC_delay5us();                
		SCL_pin = 0;                    
		IIC_delay5us();     	               
}
void IIC_Ack(){
//		SDA_pin = 1;                    //дӦ���ź�
//	    SCL_pin = 1;                   
//		IIC_delay5us();	           
//		SCL_pin = 0;                    
//		IIC_delay5us();	
		SDA_pin = 1;                    //дӦ���ź�
	    SCL_pin = 1;                   
		IIC_delay5us();              
		SCL_pin = 0;                    
		IIC_delay5us();  
}



//**************************************
//��6050д��һ���ֽ�����
//**************************************
void Single_WriteI2C(unsigned char REG_Address,unsigned char REG_data)
{
    IIC_Start();                  //��ʼ�ź�
    IIC_SendBuye(SlaveAddress);   //�����豸��ַ+д�ź�
    IIC_SendBuye(REG_Address);    //�ڲ��Ĵ�����ַ��
    IIC_SendBuye(REG_data);       //�ڲ��Ĵ������ݣ�
    IIC_Stop();                   //����ֹͣ�ź�
}


//**************************************
//��I2C�豸��ȡһ���ֽ�����
//**************************************
unsigned char Single_ReadI2C(unsigned char REG_Address)
{
	unsigned char REG_data;
	IIC_Start();                   //��ʼ�ź�
	IIC_SendBuye(SlaveAddress);    //�����豸��ַ+д�ź�
	IIC_SendBuye(REG_Address);     //���ʹ洢��Ԫ��ַ����0��ʼ
	IIC_Start();                   //��ʼ�ź�
	IIC_SendBuye(SlaveAddress+1);  //�����豸��ַ+���ź�
	REG_data=IIC_RecvByte();       //�����Ĵ�������
	
	SDA_pin = 1;                    //дӦ���ź�
	SCL_pin = 1;                    //����ʱ����
	IIC_delay5us();                 //��ʱ
	SCL_pin = 0;                    //����ʱ����
	IIC_delay5us();                 //��ʱ
	
	IIC_Stop();                    //ֹͣ�ź�
	return REG_data;
}


//******************************************************************************************************
//��ʼ��MPU6050
//******************************************************************************************************
void InitMPU6050()
{
	unsigned char text1;
	Single_WriteI2C(PWR_MGMT_1, 0x80);	//��λ6050
	delay_ms(100);
	Single_WriteI2C(PWR_MGMT_1, 0x00);	//�������״̬
	Single_WriteI2C(PWR_MGMT_1, 0x00);	//�������״̬
	Single_WriteI2C(PWR_MGMT_1, 0x00);	//�������״̬
	text1=Single_ReadI2C(PWR_MGMT_1);//��ʼ���󣬿�ͨ����ȡ���ġ�WHO AM I���Ĵ������������Ӳ���Ƿ��������üĴ����洢��ID��0x68
	if(text1==0x00)
		send_buff("6050��λ�ɹ�");
	else
		send_buff("6050��λʧ��");
	Single_WriteI2C(SMPLRT_DIV, 0x07);
	Single_WriteI2C(CONFIG, 0x06);
	Single_WriteI2C(GYRO_CONFIG, 0x18);
	Single_WriteI2C(ACCEL_CONFIG, 0x01);
}

//******************************************************************************************************
//�ϳ�����
//******************************************************************************************************
int GetData(unsigned char REG_Address)
{
	unsigned char H,L;
	H=Single_ReadI2C(REG_Address);
	L=Single_ReadI2C(REG_Address+1);
	return ((H<<8)+L);   //�ϳ�����
}

//���������������͵�����
void Display10BitData(int value)
{
	Int2String(value,buff_text);
	send_buff(buff_text);
}

//�������������͵�����
void Display20BitData(float value)
{
	Float2String(value,buff_text);
	send_buff(buff_text);
}
    
//ͨ��ԭʼ���ݼ���
void IMUupdate()
{
	float norm;
	float vx, vy, vz;
	float ex, ey, ez;
	float ax,ay,az;
	float gx,gy,gz;
	
	ax = GetData(ACCEL_XOUT_H);
	ay = GetData(ACCEL_YOUT_H);
	az = GetData(ACCEL_ZOUT_H);
	
	gx = GetData(GYRO_XOUT_H);
	gy = GetData(GYRO_YOUT_H);
	gz = GetData(GYRO_ZOUT_H);
	
	norm = sqrt(ax*ax + ay*ay + az*az);
	ax = ax / norm;
	ay = ay / norm;
	az = az / norm;
	
	vx = 2*(q1*q3 - q0*q2);
	vy = 2*(q0*q1 - q2*q3);
	vz = q0*q0 - q1*q1 - q2*q2 + q3*q3;
	
	ex = (ay*vz - az*vy);
	ey = (az*vx - ax*vz);
	ez = (ax*vy - ay*vx);
	
	exInt = exInt + ex*Ki;
	eyInt = eyInt + ey*Ki;
	ezInt = ezInt + ez*Ki;
	
	
	gx = gx + Kp*ex + exInt;
	gy = gy + Kp*ey + eyInt;
	gz = gz + Kp*ez + ezInt;
	
	
	q0 = q0 + (-q1*gx - q2*gy - q3*gz)*halfT;
	q1 = q1 + (q0*gx + q2*gz - q3*gy)*halfT;
	q2 = q2 + (q0*gy - q1*gz + q3*gx)*halfT;
	q3 = q3 + (q0*gz + q1*gy - q2*gx)*halfT;  
	
	norm = sqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
	//Display10BitData(norm);
	
	q0 = q0 / norm;
	q1 = q1 / norm;
	q2 = q2 / norm;
	q3 = q3 / norm;
	Yaw = atan2(2*(q1*q2 + q0*q3),q0*q0+q1*q1-q2*q2-q3*q3)* 57.3;
	Pitch = asin(-2*q1*q3+2*q0*q2)*57.3;
	Roll = atan2(2 * q2 * q3 + 2*q0*q1,-2*q1*q1-2*q2*q2+1)*57.3;

}