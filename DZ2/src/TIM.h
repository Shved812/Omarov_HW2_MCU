/*
 * TIM.h
 *
 *  Created on: 3 ���. 2022 �.
 *      Author: hard_
 */

#ifndef TIM_H_
#define TIM_H_

#ifndef STM32F4_h
#define STM32F4_H
#include "stm32f4xx.h"
#include "stm32f429i_discovery.h"
#endif

void TIM1_UP_TIM10_IRQHandler();
void TIM6_DAC_IRQHandler();
void TIM7_IRQHandler();
void init_TIM1();
void init_TIM6();
void init_TIM7();
void TIM1_cmd(uint8_t STATE);
void TIM6_cmd(uint8_t STATE);
void TIM7_cmd(uint8_t STATE);
void TIM1_ARR(uint16_t Arr);
void TIM6_ARR(uint16_t Arr);
void TIM7_ARR(uint16_t Arr);
void TIM1_PSC(uint16_t Psc);
void TIM6_PSC(uint16_t Psc);
void TIM7_PSC(uint16_t Psc);
#endif /* TIM_H_ */
