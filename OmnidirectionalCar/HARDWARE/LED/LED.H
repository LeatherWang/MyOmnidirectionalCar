#ifndef __LED_H
#define __LED_H
#include "sys.h"
//LED 端口定义
#define LED PAout(15) 
#define BUZZER PBout(13)
void LED_Init(void);  //初始化
void Led_Flash(u16 time);
#endif
