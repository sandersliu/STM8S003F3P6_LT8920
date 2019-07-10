#ifndef __KEY_H
#define __KEY_H
#include "stm8s.h"


#define   Read_GPIOD_PIN4   GPIO_ReadInputPin(GPIOD, GPIO_PIN_4)

void KEY_Init(void);
void Key_Scan(uint8_t req);
#endif
