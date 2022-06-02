#include "HT66F2390.h"
#include <math.h>
#include "key.h"
#include "uart0.h"
#include "MyType.h"	
#include "Int2String.h"
#include "time.h"

#define SDA_pin		_pf2//�����������
#define	SDA_set		_pfc2
#define SDA_up_set	_pfpu2//����
#define	SCL_pin		_pf3
#define	SCL_set		_pfc



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
#define	PWR_MGMT_1		0x6B	//��Դ��������ֵ��0x00(��������)
#define	WHO_AM_I		 0x75	//��ʼ���󣬿�ͨ����ȡ���ġ�WHO AM I���Ĵ������������Ӳ���Ƿ��������üĴ����洢��ID��0x68
#define	SlaveAddress	0xD0	//IICд��ʱ�ĵ�ַ�ֽ����ݣ�+1Ϊ��ȡ    0x68����һλ��Ϊ D0  A0���Žӵ�




void IIC_init();
void IIC_delay2us();
void IIC_delay5us();
void i2_qs();
void i2_tz();
void i2_fs(unsigned char Data);
unsigned char i2_js(unsigned char aack);	//����8λ����
unsigned char i2cwrite(unsigned char addr,unsigned char Data);	//д��8λ��Ч����
unsigned char i2cread(unsigned char addr,unsigned char *Data);
unsigned char i2creads(unsigned char addr,unsigned char length,unsigned char *Data);
unsigned char writeBit(unsigned char addr,unsigned char bitNum,unsigned char Data);
unsigned char writeBits(unsigned char addr,unsigned char bitStart,unsigned char length,unsigned char Data);
unsigned char readBit(unsigned char addr,unsigned char bitNum,unsigned char *Data);
unsigned char readBits(unsigned char addr,unsigned char bitStart,unsigned char length,unsigned char *Data);
unsigned char loadfirmware(void);
int GetData(unsigned char REG_Address);//��ȡ�Ĵ����ĳ�ʼ��ֵ
unsigned char loadcfgupd(void);	//DMP����
/*������DMP*/
unsigned char xdmpUpdates(unsigned char datacounts);
/*��ȡ FIFO ����*/
unsigned int getFIFOCount();

/*FIFO���ݶ�ȡ
���� *Data	�洢���ݵĵ�ַ
����ֵ (1=��ȡ�ɹ�,0��ȡʧ��)
*/
unsigned char readdmp(unsigned char *Data);
//���ز����� DMP �����˶���������
unsigned char dmpInitialize(void);

/*��ʼ��MPU6050*/
void initMPU6050(void);

/*��֤MPU6050����*/
unsigned char getDeviceID(void);

//�������ݸ�����������λ�����(V2.6�汾)
//fun:������. 0XA0~0XAF
//data:���ݻ�����,���28�ֽ�!!
//len:data����Ч���ݸ���
void usart1_niming_report(u8 fun,u8*data,u8 len);

//���ͼ��ٶȴ��������ݺ�����������
//aacx,aacy,aacz:x,y,z������������ļ��ٶ�ֵ
//gyrox,gyroy,gyroz:x,y,z�������������������ֵ
void mpu6050_send_data(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz);

//ͨ������1�ϱ���������̬���ݸ�����
//aacx,aacy,aacz:x,y,z������������ļ��ٶ�ֵ
//gyrox,gyroy,gyroz:x,y,z�������������������ֵ
//roll:�����.��λ0.01�ȡ� -18000 -> 18000 ��Ӧ -180.00  ->  180.00��
//pitch:������.��λ 0.01�ȡ�-9000 - 9000 ��Ӧ -90.00 -> 90.00 ��
//yaw:�����.��λΪ0.1�� 0 -> 3600  ��Ӧ 0 -> 360.0��
void usart1_report_imu(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz,short roll,short pitch,short yaw);


