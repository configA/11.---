#include "Int2String.h"


char* Int2String(int num,char *str)//10���� 
{
	int i = 0;//ָʾ���str 
	int j = 0;
	if(num<0)//���numΪ��������num���� 
	{
		num = -num;
		str[i++] = '-';
	} 
	//ת�� 
	do
	{
		str[i++] = num%10+48;//ȡnum���λ �ַ�0~9��ASCII����48~57������˵����0+48=48��ASCII���Ӧ�ַ�'0' 
		num /= 10;//ȥ�����λ	
	}while(num);//num��Ϊ0����ѭ��
	
	
	//ȷ����ʼ������λ�� 
	
	if(str[0]=='-')//����и��ţ����Ų��õ��� 
	{
		j = 1;//�ӵڶ�λ��ʼ���� 
		++i;//�����и��ţ����Խ����ĶԳ���ҲҪ����1λ 
	}
	//�Գƽ��� 
	for(;j<i/2;j++)
	{
		//�Գƽ������˵�ֵ ��ʵ����ʡ���м��������a+b��ֵ��a=a+b;b=a-b;a=a-b; 
		str[j] = str[j] + str[i-1-j];
		str[i-1-j] = str[j] - str[i-1-j];
		str[j] = str[j] - str[i-1-j];
	} 
	str[i++] = ' ';
//	str[i++] = '\r';//�� /r �� /n ����
//	str[i++] = '\n';
	str[i] = '\0';
	return str;//����ת�����ֵ 
}

int String2Int(char *str)//�ַ���ת���� 
{
	char flag = '+';//ָʾ����Ƿ������ 
	long res = 0;
	
	if(*str=='-')//�ַ��������� 
	{
		++str;//ָ����һ���ַ� 
		flag = '-';//����־��Ϊ���� 
	} 
	//����ַ�ת�������ۼӵ����res 
	while(*str>='0' && *str<='9')//��������ֲŽ���ת��������0~9��ASCII�룺48~57 
	{
		res = 10*res+  *str++ - '0';//�ַ�'0'��ASCII��Ϊ48,48-48=0�պ�ת��Ϊ����0 
	} 
 
    if(flag == '-')//�����Ǹ��������
	{
		res = -res;
	}
 	
	return (int)res;
}



char* Float2String(float oat,char *str)//������ת�ַ���2λС��
{
	int i = 0;//ָʾ���str 
	int j = 0;
	int num=0;
	int temp=0;
	num=oat;
	
	if(oat<0)//���numΪ��������num���� 
	{
		num = -num;
		str[i++] = '-';
	} 
	//ת�� 
	do
	{
		str[i++] = num%10+48;//ȡnum���λ �ַ�0~9��ASCII����48~57������˵����0+48=48��ASCII���Ӧ�ַ�'0' 
		num /= 10;//ȥ�����λ	
	}while(num);//num��Ϊ0����ѭ��
	
	
	
	//ȷ����ʼ������λ�� 
	
	if(str[0]=='-')//����и��ţ����Ų��õ��� 
	{
		j = 1;//�ӵڶ�λ��ʼ���� 
		++i;//�����и��ţ����Խ����ĶԳ���ҲҪ����1λ 
	}
	//�Գƽ��� 
	for(;j<i/2;j++)
	{
		//�Գƽ������˵�ֵ ��ʵ����ʡ���м��������a+b��ֵ��a=a+b;b=a-b;a=a-b; 
		str[j] = str[j] + str[i-1-j];
		str[i-1-j] = str[j] - str[i-1-j];
		str[j] = str[j] - str[i-1-j];
	} 
	if(str[0]=='-')
	{
		i = i-1;
		str[i++] = '.';
		temp = (oat*10)*-1;//ȡС�����һλ		
		str[i++] = temp%10+48;
		temp = (oat*100)*-1;//ȡС�������λ
		str[i++] = temp%10+48;
	}
	else
	{
		str[i++] = '.';
		temp = oat*10;//ȡС�����һλ
		str[i++] = temp%10+48;
		temp = oat*100;//ȡС�������λ
		str[i++] = temp%10+48;
	}	

	str[i++] = ' ';
	str[i] = '\0';
	return str;//����ת�����ֵ 
}

