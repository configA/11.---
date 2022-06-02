#include "HT66F2390.h"
#include "Int2String.h"
#include "uart0.h"
#include "key.h"
#include <math.h>

#define SDA_pin		_pf2//�����������
#define	SDA_set		_pfc2
#define SDA_up_set	_pfpu2//����
#define	SCL_pin		_pf3
#define	SCL_set		_pfc3


#define	SMPLRT_DIV		0x19	//�����ǲ����ʣ�����ֵ��0x07(125Hz)
#define	CONFIG			 0x1A	//��ͨ�˲�Ƶ�ʣ�����ֵ��0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//�������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
#define	ACCEL_CONFIG	0x1C	//���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x01(���Լ죬2G��5Hz)
#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C 	//MPU6050���ٶ����ݼĴ�����ַ
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
#define	TEMP_OUT_H		0x41	//�¶ȴ�������ַ
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43	//MPU6050���������ݼĴ�����ַ
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
#define	PWR_MGMT_1		0x6B	//��Դ����������ֵ��0x00(��������)
#define	WHO_AM_I		 0x75	//��ʼ���󣬿�ͨ����ȡ���ġ�WHO AM I���Ĵ������������Ӳ���Ƿ��������üĴ����洢��ID��0x68
#define	SlaveAddress	0xD0	//IICд��ʱ�ĵ�ַ�ֽ����ݣ�+1Ϊ��ȡ    0x68����һλ��Ϊ D0  A0���Žӵ�



typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;

#define Kp 100.0f
#define Ki 0.002f
#define halfT 0.001f

//6050����
extern float Yaw;	//roll��Χ��Z����ת��Ҳ�з�����
extern float Roll;	//yawΧ��Y����ת����ƫ����
extern float Pitch; //pitchΧ��X����ת������������



void IIC_init();
void IIC_delay2us();
void IIC_delay5us();
void IIC_Start();
void IIC_Stop();
void IIC_NAck();
void IIC_Ack();
unsigned char IIC_SendBuye(unsigned char dat);
unsigned char IIC_RecvByte();
unsigned char Single_ReadI2C(unsigned char REG_Address);
void Single_WriteI2C(unsigned char REG_Address,unsigned char REG_data);
int GetData(unsigned char REG_Address);
void Display10BitData(int value);
void Display20BitData(float value);
void InitMPU6050();
void IMUupdate();//ŷ����ת��

