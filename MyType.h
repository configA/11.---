//MyType.hͷ�ļ�
#include <HT66F2390.h>
typedef	unsigned char	u8;
typedef	char			s8;
typedef	unsigned short	u16;
typedef	short			s16;
typedef	unsigned long	u32;
typedef	long			s32;

typedef unsigned int   uint;


#define LED_Port1  _ph1			    //�궨������	
#define LED_PortC _phc1                  //�궨���������Եķ���

#define LED_Port2  _ph0			    //�궨������	
#define LED_PortC2 _phc0                 //�궨���������Եķ���		
void LED_init();	