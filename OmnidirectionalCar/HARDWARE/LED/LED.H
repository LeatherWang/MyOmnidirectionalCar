#ifndef __LED_H
#define __LED_H
#include "sys.h"
//LED �˿ڶ���
#define LED PAout(15) 
#define BUZZER PBout(13)
void LED_Init(void);  //��ʼ��
void Led_Flash(u16 time);
#endif