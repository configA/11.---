//MyType.h头文件
#include <HT66F2390.h>
typedef	unsigned char	u8;
typedef	char			s8;
typedef	unsigned short	u16;
typedef	short			s16;
typedef	unsigned long	u32;
typedef	long			s32;

typedef unsigned int   uint;


#define LED_Port1  _ph1			    //宏定义引脚	
#define LED_PortC _phc1                  //宏定义引脚属性的方向

#define LED_Port2  _ph0			    //宏定义引脚	
#define LED_PortC2 _phc0                 //宏定义引脚属性的方向		
void LED_init();	