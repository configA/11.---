#include "Int2String.h"


char* Int2String(int num,char *str)//10进制 
{
	int i = 0;//指示填充str 
	int j = 0;
	if(num<0)//如果num为负数，将num变正 
	{
		num = -num;
		str[i++] = '-';
	} 
	//转换 
	do
	{
		str[i++] = num%10+48;//取num最低位 字符0~9的ASCII码是48~57；简单来说数字0+48=48，ASCII码对应字符'0' 
		num /= 10;//去掉最低位	
	}while(num);//num不为0继续循环
	
	
	//确定开始调整的位置 
	
	if(str[0]=='-')//如果有负号，负号不用调整 
	{
		j = 1;//从第二位开始调整 
		++i;//由于有负号，所以交换的对称轴也要后移1位 
	}
	//对称交换 
	for(;j<i/2;j++)
	{
		//对称交换两端的值 其实就是省下中间变量交换a+b的值：a=a+b;b=a-b;a=a-b; 
		str[j] = str[j] + str[i-1-j];
		str[i-1-j] = str[j] - str[i-1-j];
		str[j] = str[j] - str[i-1-j];
	} 
	str[i++] = ' ';
//	str[i++] = '\r';//先 /r 在 /n 换行
//	str[i++] = '\n';
	str[i] = '\0';
	return str;//返回转换后的值 
}

int String2Int(char *str)//字符串转数字 
{
	char flag = '+';//指示结果是否带符号 
	long res = 0;
	
	if(*str=='-')//字符串带负号 
	{
		++str;//指向下一个字符 
		flag = '-';//将标志设为负号 
	} 
	//逐个字符转换，并累加到结果res 
	while(*str>='0' && *str<='9')//如果是数字才进行转换，数字0~9的ASCII码：48~57 
	{
		res = 10*res+  *str++ - '0';//字符'0'的ASCII码为48,48-48=0刚好转化为数字0 
	} 
 
    if(flag == '-')//处理是负数的情况
	{
		res = -res;
	}
 	
	return (int)res;
}



char* Float2String(float oat,char *str)//浮点数转字符串2位小数
{
	int i = 0;//指示填充str 
	int j = 0;
	int num=0;
	int temp=0;
	num=oat;
	
	if(oat<0)//如果num为负数，将num变正 
	{
		num = -num;
		str[i++] = '-';
	} 
	//转换 
	do
	{
		str[i++] = num%10+48;//取num最低位 字符0~9的ASCII码是48~57；简单来说数字0+48=48，ASCII码对应字符'0' 
		num /= 10;//去掉最低位	
	}while(num);//num不为0继续循环
	
	
	
	//确定开始调整的位置 
	
	if(str[0]=='-')//如果有负号，负号不用调整 
	{
		j = 1;//从第二位开始调整 
		++i;//由于有负号，所以交换的对称轴也要后移1位 
	}
	//对称交换 
	for(;j<i/2;j++)
	{
		//对称交换两端的值 其实就是省下中间变量交换a+b的值：a=a+b;b=a-b;a=a-b; 
		str[j] = str[j] + str[i-1-j];
		str[i-1-j] = str[j] - str[i-1-j];
		str[j] = str[j] - str[i-1-j];
	} 
	if(str[0]=='-')
	{
		i = i-1;
		str[i++] = '.';
		temp = (oat*10)*-1;//取小数点后一位		
		str[i++] = temp%10+48;
		temp = (oat*100)*-1;//取小数点后俩位
		str[i++] = temp%10+48;
	}
	else
	{
		str[i++] = '.';
		temp = oat*10;//取小数点后一位
		str[i++] = temp%10+48;
		temp = oat*100;//取小数点后俩位
		str[i++] = temp%10+48;
	}	

	str[i++] = ' ';
	str[i] = '\0';
	return str;//返回转换后的值 
}

