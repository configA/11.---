#include "Cls_init.h"
#define q30  1073741824.0f    //2的30次方 计算欧拉角时需要

//-----主要函数声明
//void MUP_6060_READ();
void Control_Angle();//蓝牙控制角度
//-----串口变量
char Bluetooth=0;//蓝牙变量读取接收到的第一个串口数据
char buff_text[50]={'\0'};//串口打印字符串数组
char linshi[50]={'\0'};
//-----定时器变量
unsigned int time2_count=0;//定时器变量
unsigned int mpu6050_delay=0;//6050减速函数
unsigned int mechanical_delay=0;//机械臂减速
//-----MPU-6050变量
//float mup6050_angle[3];// 0:俯仰角 1:横滚角 2:偏航角 
unsigned char dmpdatas[42]={'\0'};	//DMP数据
unsigned char zd=0,i=0;
long quat[4]={0};
float q0=1.0,q1=0.0,q2=0.0,q3=0.0;
float pitch=0,roll=0,yaw=0; //欧拉角
int pos0=90,pos1=90,pos2=90;//角度
int pos0_old=90,pos1_old=90,pos2_old=90;//上一次的角度
/*************主函数*************/
void main()
{		
	Cls_init();
	pos0 = 171; pos1 = 146; pos2 = 144;
	_pt0on=1;
	PWM_Change_0(pos0);
	delay_ms(1000);
	_pt0on=0;//关闭基座
	PWM_Change_1(pos1);
	delay_ms(1000);
	PWM_Change_2(pos2);	
	
	while(1)
	{
		//MUP_6060_READ();//SDA PF2 SCL PF3
		Control_Angle();
		//基地 L(顺时针)  R(逆时针) 
		//下臂 D(下)      U(上)
		//上臂 B(下)      T(上) 
		//头直线运动  S   曲线运动 C    G头部碰书
	}
}



/*************定时器2中断10ms(16M)进一次 *************/
DEFINE_ISR(time2,0x38)
{
	_emi=0;                    //关闭总中断
	time2_count++;
	if(time2_count==100)
	{
		time2_count=0;
		LED_Port1=~LED_Port1;           //LED1状态取反
	}
	if(++mpu6050_delay == 3) mpu6050_delay = 0;
	if(++ mechanical_delay== 3) mechanical_delay = 0;
	_stm2af=0;            //清除定时器中断标志位
	_emi=1;                    //开启总中断
}


/*************串口中断*************/
DEFINE_ISR(UART,0x3C)
{
	char buff[50]={'\0'};
 	if(_ur0f == 1)            //当串口一有数据来时，也就是说有跌倒的预兆
	{	
		get_buff(buff,'\n');//获取一串字符串（该字符串要有换行符号）'\n'=0x0A
		send_buff(buff);//回显
		Bluetooth = buff[0];
	}
	
 	if(_ur1f == 1)            //当串口一有数据来时，也就是说有跌倒的预兆
	{	
		get_buff1(buff,'\n');//获取一串字符串（该字符串要有换行符号）'\n'=0x0A
		send_buff1(buff);//回显
		Bluetooth = buff[0];
		//send_buff1(buff);//把接收到的字符串再发送出去
		
	}	
	_ur0f = 0;	
	_ur1f = 0;				
}




/*************6050数据读取*************/
void MUP_6060_READ()
{
	if(mpu6050_delay) return; //200ms进入一次
	else mpu6050_delay = 1;
	PWM_Change_0(0);
	PWM_Change_1(0);
		i=getFIFOCount();//读取FIFO计数
	 	i2cread(0x3A,&zd);	//读取中断状态
	 	if((zd & 0x10)||i==1024)	//判断FIFO是否溢出
	 	{
	    	writeBit(0x6A,2,1);	//复位 FIFO
		}
		else if (zd & 0x02)
		{
	    	while(i<42) i=getFIFOCount();//读取FIFO计数
			readdmp(dmpdatas);	//读取FIFO数据(四元数+其他的数据)
			
			//处理四元数
			quat[0] = ((long)dmpdatas[0] << 24) | ((long)dmpdatas[1] << 16) |
	            ((long)dmpdatas[2] << 8) | dmpdatas[3];
			quat[1] = ((long)dmpdatas[4] << 24) | ((long)dmpdatas[5] << 16) |
	            ((long)dmpdatas[6] << 8) | dmpdatas[7];
	    	quat[2] = ((long)dmpdatas[8] << 24) | ((long)dmpdatas[9] << 16) |
	            ((long)dmpdatas[10] << 8) | dmpdatas[11];
	    	quat[3] = ((long)dmpdatas[12] << 24) | ((long)dmpdatas[13] << 16) |
	            ((long)dmpdatas[14] << 8) | dmpdatas[15];
			//处理四元数
			q0 = quat[0] / q30;	//q30格式转换为浮点数
			q1 = quat[1] / q30;
			q2 = quat[2] / q30;
			q3 = quat[3] / q30; 
	
			//57.3是弧度转角度 180/pi
			pitch = asin(-2 * q1 * q3 + 2 * q0* q2)* 57.3;	// pitch
			roll  = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1)* 57.3;	// roll 
			yaw   = atan2(2*(q1*q2 + q0*q3),q0*q0+q1*q1-q2*q2-q3*q3) * 57.3;	//yaw


//			整数显示			
//			send_buff("俯仰角=");
//			send_buff(Int2String((int)pitch,buff_text));
//			
//			send_buff("横滚角=");
//			send_buff(Int2String((int)roll,buff_text));
//			
//			send_buff("偏航角=");
//			send_buff(Int2String((int)yaw,buff_text));
//			send_buff("\r\n");	

//			浮点数显示			
			send_buff("俯仰角=");
			send_buff(Float2String(pitch,buff_text));
			
			send_buff("横滚角=");
			send_buff(Float2String(roll,buff_text));
			
			send_buff("偏航角=");
			send_buff(Float2String(yaw,buff_text));
			send_buff("\r\n");	
		}					
}


//90-187(0-90) 187-284(90-180)
//定时器0为基座  定时器1为下臂  定时器2为上臂
void Control_Angle()
{
	if(mechanical_delay) return; //200ms进入一次
	else mechanical_delay = 1;
	//---------------------------------基地控制	----------------------------------//
	if(Bluetooth == 'R')
	{
		Bluetooth = 0;
		if(pos0 >= 10)
		{
			_pt0on=1;//打开基座
			pos0--;
			PWM_Change_0(pos0);
			delay_ms(10);
			_pt0on=0;//关闭基座
		}	
	}
	if(Bluetooth == 'L')
	{
		Bluetooth = 0;
		if(pos0 <= 170)
		{
			_pt0on=1;//打开基座
			pos0++;
			PWM_Change_0(pos0);
			delay_ms(10);
			_pt0on=0;//关闭基座
		}	
	}
	//---------------------------------下壁控制	----------------------------------//
		if(Bluetooth == 'D')//向下
	{
		if(pos1 >= 10)
		{
			Bluetooth = 0;
			pos1--;
			PWM_Change_1(pos1);
			delay_ms(10);
		}	
	}
	if(Bluetooth == 'U')//向上
	{
		Bluetooth = 0;
		if(pos1 <= 170)
		{
			pos1++;
			PWM_Change_1(pos1);
			delay_ms(10);
		}	
	}
	//---------------------------------上臂控制	----------------------------------//
	if(Bluetooth == 'B')//向下
	{
		Bluetooth = 0;
		if(pos2 >= 10)
		{
			pos2--;
			PWM_Change_2(pos2);
			delay_ms(10);
		}	
	}
	if(Bluetooth == 'T')//向上
	{
		Bluetooth = 0;
		if(pos2 <= 170)
		{
			pos2++;
			PWM_Change_2(pos2);
			delay_ms(10);
		}	
	}
	if(Bluetooth == 'M')//归位
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

	f(Bluetooth == 'G')//归位
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
	if(Bluetooth == 'S')//直线运动
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

	if(Bluetooth == 'C')//曲线运动
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

