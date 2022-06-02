#include "mpu_6050.h"
char buff_text[50];


float q0 = 1, q1 = 0, q2 = 0, q3 = 0;
float exInt = 0, eyInt = 0, ezInt = 0;
float Yaw=1;	//roll是围绕Z轴旋转，也叫翻滚角
float Roll=1;	//yaw围绕Y轴旋转，叫偏航角
float Pitch=1; //pitch围绕X轴旋转，叫做俯仰角



void IIC_init()//IIC初始化
{

	SDA_set=0;//输出
	SCL_set=0;//输出
	SCL_pin=1;
	SDA_pin=1;
	SDA_up_set=1;
}


/*******************************************************************************
* 函数名         : Delay2us()
* 函数功能		   : 延时
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/
//8个asm出错，4有39  指令周期为4个时钟周期 机器周期为8个时钟周期
//时钟周期0.125us
void IIC_delay2us()
{		
	asm("nop");//一个机器周期1us
	asm("nop");
}

void IIC_delay5us()
{		
	asm("nop");  	asm("nop");//一个机器周期1us
	asm("nop");		asm("nop");
	asm("nop");
}


/*******************************************************************************
* 函数名         : I2cStart()
* 函数功能		   : 起始信号：在SCL_pin时钟信号在高电平期间SDA_pin信号产生一个下降沿
* 输入           : 无
* 输出         	 : 无
* 备注           : 起始之后SDA_pin和SCL_pin都为0
*******************************************************************************/
void IIC_Start()	//SCL 线是高电平时，SDA 线从高电平向低电平切换表示起始条件。
{
//	SDA_pin=1;
//	SCL_pin=1;
//	IIC_delay5us();//建立时间是SDA_pin保持时间>4.7us
//	SDA_pin=0;
//	IIC_delay5us();	
//	SCL_pin=0;		
	
	SDA_pin=1;
	IIC_delay2us();
	SCL_pin=1;
	IIC_delay5us();//建立时间是SDA_pin保持时间>4.7us
	IIC_delay2us();	
	SDA_pin=0;
	IIC_delay5us();//保持时间是>4us
	IIC_delay2us();
	SCL_pin=0;		
	IIC_delay2us();	
	
}


/*******************************************************************************
* 函数名         : I2cStop()
* 函数功能		   : 终止信号：在SCL_pin时钟信号高电平期间SDA_pin信号产生一个上升沿
* 输入           : 无
* 输出         	 : 无
* 备注           : 结束之后保持SDA_pin和SCL_pin都为1；表示总线空闲
*******************************************************************************/

void IIC_Stop()
{
//	SDA_pin=0;
//	SCL_pin=1;
//	IIC_delay5us();//建立时间大于4.7us
//	SDA_pin=1;
//	IIC_delay5us();
//	SCL_pin=0;
//	IIC_delay2us();

	SDA_pin=0;
	IIC_delay5us();
	SCL_pin=1;
	IIC_delay5us();//建立时间大于4.7us
	SDA_pin=1;
	IIC_delay5us();
	IIC_delay2us();	
	SCL_pin=0;
	IIC_delay2us();
}

/*******************************************************************************
* 函数名         : I2cSendByte(unsigned char num)
* 函数功能		   : 通过I2C发送一个字节。在SCL_pin时钟信号高电平期间，保持发送信号SDA_pin保持稳定
* 输入           : num
* 输出         	 : 0或1。发送成功返回1，发送失败返回0
* 备注           : 发送完一个字节SCL_pin=0,SDA_pin=1
*******************************************************************************/

unsigned char IIC_SendBuye(unsigned char dat)
{
	unsigned char a=0,b=0;//最大255，一个机器周期为1us，最大延时255us。		
	for(a=0;a<8;a++)//要发送8位，从最高位开始
	{
		SDA_pin=dat>>7;	 //起始信号之后SCL_pin=0，所以可以直接改变SDA_pin信号
		dat=dat<<1;
		IIC_delay2us();
		SCL_pin=1;
		IIC_delay5us();//建立时间>4.7us
		SCL_pin=0;
		IIC_delay5us();//时间大于4us		
	}
	SDA_pin=1;
	IIC_delay5us();
	SDA_set=1;
	SCL_pin=1;
//	send_buff("2");
	while(SDA_pin)//等待应答，也就是等待从设备把SDA_pin拉低
	{
		b++;
		if(b>200)	 //如果超过2000us没有应答发送失败，或者为非应答，表示接收结束
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
* 函数名         : I2cReadByte()
* 函数功能		   : 使用I2c读取一个字节
* 输入           : 无
* 输出         	 : dat
* 备注           : 接收完一个字节SCL_pin=0,SDA_pin=1.
*******************************************************************************/

unsigned char IIC_RecvByte()
{
	unsigned char a=0,dat=0;
	SDA_pin=1;			//起始和发送一个字节之后SCL_pin都是0
	IIC_delay2us();
	SDA_set=1;
	for(a=0;a<8;a++)//接收8个字节
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
//		SDA_pin = 0;                    //写不应答信号
//		SCL_pin = 1;              
//		IIC_delay5us();	               
//		SCL_pin = 0;                    
//		IIC_delay5us();
		SDA_pin = 0;                    //写不应答信号
		SCL_pin = 1;              
		IIC_delay5us();                
		SCL_pin = 0;                    
		IIC_delay5us();     	               
}
void IIC_Ack(){
//		SDA_pin = 1;                    //写应答信号
//	    SCL_pin = 1;                   
//		IIC_delay5us();	           
//		SCL_pin = 0;                    
//		IIC_delay5us();	
		SDA_pin = 1;                    //写应答信号
	    SCL_pin = 1;                   
		IIC_delay5us();              
		SCL_pin = 0;                    
		IIC_delay5us();  
}



//**************************************
//向6050写入一个字节数据
//**************************************
void Single_WriteI2C(unsigned char REG_Address,unsigned char REG_data)
{
    IIC_Start();                  //起始信号
    IIC_SendBuye(SlaveAddress);   //发送设备地址+写信号
    IIC_SendBuye(REG_Address);    //内部寄存器地址，
    IIC_SendBuye(REG_data);       //内部寄存器数据，
    IIC_Stop();                   //发送停止信号
}


//**************************************
//从I2C设备读取一个字节数据
//**************************************
unsigned char Single_ReadI2C(unsigned char REG_Address)
{
	unsigned char REG_data;
	IIC_Start();                   //起始信号
	IIC_SendBuye(SlaveAddress);    //发送设备地址+写信号
	IIC_SendBuye(REG_Address);     //发送存储单元地址，从0开始
	IIC_Start();                   //起始信号
	IIC_SendBuye(SlaveAddress+1);  //发送设备地址+读信号
	REG_data=IIC_RecvByte();       //读出寄存器数据
	
	SDA_pin = 1;                    //写应答信号
	SCL_pin = 1;                    //拉高时钟线
	IIC_delay5us();                 //延时
	SCL_pin = 0;                    //拉低时钟线
	IIC_delay5us();                 //延时
	
	IIC_Stop();                    //停止信号
	return REG_data;
}


//******************************************************************************************************
//初始化MPU6050
//******************************************************************************************************
void InitMPU6050()
{
	unsigned char text1;
	Single_WriteI2C(PWR_MGMT_1, 0x80);	//复位6050
	delay_ms(100);
	Single_WriteI2C(PWR_MGMT_1, 0x00);	//解除休眠状态
	Single_WriteI2C(PWR_MGMT_1, 0x00);	//解除休眠状态
	Single_WriteI2C(PWR_MGMT_1, 0x00);	//解除休眠状态
	text1=Single_ReadI2C(PWR_MGMT_1);//初始化后，可通过读取它的“WHO AM I”寄存器内容来检测硬件是否正常，该寄存器存储了ID号0x68
	if(text1==0x00)
		send_buff("6050复位成功");
	else
		send_buff("6050复位失败");
	Single_WriteI2C(SMPLRT_DIV, 0x07);
	Single_WriteI2C(CONFIG, 0x06);
	Single_WriteI2C(GYRO_CONFIG, 0x18);
	Single_WriteI2C(ACCEL_CONFIG, 0x01);
}

//******************************************************************************************************
//合成数据
//******************************************************************************************************
int GetData(unsigned char REG_Address)
{
	unsigned char H,L;
	H=Single_ReadI2C(REG_Address);
	L=Single_ReadI2C(REG_Address+1);
	return ((H<<8)+L);   //合成数据
}

//将整形数据数据送到串口
void Display10BitData(int value)
{
	Int2String(value,buff_text);
	send_buff(buff_text);
}

//将浮点数数据送到串口
void Display20BitData(float value)
{
	Float2String(value,buff_text);
	send_buff(buff_text);
}
    
//通过原始数据计算
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