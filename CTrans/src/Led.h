/*
 * Led.h
 *
 *  Created on: 26 апр. 2022 г.
 *      Author: hard_
 */
#ifndef  STM_H
#define STM_H

#include "stm32f4xx.h"
#include "stm32f429i_discovery.h"

#endif

#ifndef LED_H_
#define LED_H_

void TIM6_DAC_IRQHandler(void);
void init_gpio();
void Led3_on();
void Led4_on();
void Led3_off();
void Led4_off();
void Blink_Led3();
void Blink_Led4();
void init_TIM6();

#endif /* LED_H_ */
