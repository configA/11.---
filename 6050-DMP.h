#include "HT66F2390.h"
#include <math.h>
#include "key.h"
#include "uart0.h"
#include "MyType.h"	
#include "Int2String.h"
#include "time.h"

#define SDA_pin		_pf2//设置输入输出
#define	SDA_set		_pfc2
#define SDA_up_set	_pfpu2//上拉
#define	SCL_pin		_pf3
#define	SCL_set		_pfc



#define	SMPLRT_DIV		0x19	//陀螺仪采样率，典型值：0x07(125Hz)
#define	CONFIG			 0x1A	//低通滤波频率，典型值：0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define	ACCEL_CONFIG	0x1C	//加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C 	//MPU6050加速度数据寄存器地址
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
#define	TEMP_OUT_H		0x41	//温度传感器地址
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43	//MPU6050陀螺仪数据寄存器地址
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
#define	PWR_MGMT_1		0x6B	//电源管理，典型值：0x00(正常启用)
#define	WHO_AM_I		 0x75	//初始化后，可通过读取它的“WHO AM I”寄存器内容来检测硬件是否正常，该寄存器存储了ID号0x68
#define	SlaveAddress	0xD0	//IIC写入时的地址字节数据，+1为读取    0x68左移一位后为 D0  A0引脚接地




void IIC_init();
void IIC_delay2us();
void IIC_delay5us();
void i2_qs();
void i2_tz();
void i2_fs(unsigned char Data);
unsigned char i2_js(unsigned char aack);	//接收8位数据
unsigned char i2cwrite(unsigned char addr,unsigned char Data);	//写入8位有效数据
unsigned char i2cread(unsigned char addr,unsigned char *Data);
unsigned char i2creads(unsigned char addr,unsigned char length,unsigned char *Data);
unsigned char writeBit(unsigned char addr,unsigned char bitNum,unsigned char Data);
unsigned char writeBits(unsigned char addr,unsigned char bitStart,unsigned char length,unsigned char Data);
unsigned char readBit(unsigned char addr,unsigned char bitNum,unsigned char *Data);
unsigned char readBits(unsigned char addr,unsigned char bitStart,unsigned char length,unsigned char *Data);
unsigned char loadfirmware(void);
int GetData(unsigned char REG_Address);//读取寄存器的初始数值
unsigned char loadcfgupd(void);	//DMP设置
/*最后更新DMP*/
unsigned char xdmpUpdates(unsigned char datacounts);
/*读取 FIFO 计数*/
unsigned int getFIFOCount();

/*FIFO数据读取
参数 *Data	存储数据的地址
返回值 (1=读取成功,0读取失败)
*/
unsigned char readdmp(unsigned char *Data);
//加载并配置 DMP 数字运动处理引擎
unsigned char dmpInitialize(void);

/*初始化MPU6050*/
void initMPU6050(void);

/*验证MPU6050连接*/
unsigned char getDeviceID(void);

//传送数据给匿名四轴上位机软件(V2.6版本)
//fun:功能字. 0XA0~0XAF
//data:数据缓存区,最多28字节!!
//len:data区有效数据个数
void usart1_niming_report(u8 fun,u8*data,u8 len);

//发送加速度传感器数据和陀螺仪数据
//aacx,aacy,aacz:x,y,z三个方向上面的加速度值
//gyrox,gyroy,gyroz:x,y,z三个方向上面的陀螺仪值
void mpu6050_send_data(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz);

//通过串口1上报结算后的姿态数据给电脑
//aacx,aacy,aacz:x,y,z三个方向上面的加速度值
//gyrox,gyroy,gyroz:x,y,z三个方向上面的陀螺仪值
//roll:横滚角.单位0.01度。 -18000 -> 18000 对应 -180.00  ->  180.00度
//pitch:俯仰角.单位 0.01度。-9000 - 9000 对应 -90.00 -> 90.00 度
//yaw:航向角.单位为0.1度 0 -> 3600  对应 0 -> 360.0度
void usart1_report_imu(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz,short roll,short pitch,short yaw);


