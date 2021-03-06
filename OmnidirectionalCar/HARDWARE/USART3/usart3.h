#ifndef __USRAT3_H
#define __USRAT3_H 
#include "sys.h"	  	

extern u8 Usart3_Receive;
void uart3_init(u32 pclk2,u32 bound);
int USART3_IRQHandler(void);
u8 click_RC (void);
u8 Left_RC (int time);
u8 Right_RC (int time);

void ANO_DT_Data_Receive_Anl(u8 *data_buf,u8 num);
void ANO_UART3_Put_Buf(unsigned char *DataToSend , u8 data_num);
#endif

