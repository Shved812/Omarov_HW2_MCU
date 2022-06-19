/*
 * Commander.h
 *
 *  Created on: 17 θών. 2022 γ.
 *      Author: hard_
 */

#ifndef COMMANDER_H_
#define COMMANDER_H_

#ifndef STM32F4_h
#define STM32F4_H
#include "stm32f4xx.h"
#include "stm32f429i_discovery.h"
#endif

#include "Graphics_tools.h"
#include "CBUF.h"
#include "TIM.h"
#include "Led.h"
#include "CTrans.h"

extern uint32_t Index_pixel_in;
extern uint32_t Index_pixel_out;
extern uint8_t Left_p;
extern uint8_t Right_p;
extern uint16_t Result_p;

void TIM4_IRQHandler();

void Convert_8to16(uint8_t left, uint8_t right, uint16_t* result);

void Convert_16to8(uint8_t* left, uint8_t* right, uint16_t result);

void init_Commander();

#endif /* COMMANDER_H_ */
