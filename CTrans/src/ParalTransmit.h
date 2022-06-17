/*
 * ParalTransmit.h
 *
 *  Created on: 18 мая 2022 г.
 *      Author: hard_
 */


#ifndef PARALTRANSMIT_H_
#define PARALTRANSMIT_H_

#ifndef  STM32F4_H
#define STM32F4_H
#include "stm32f4xx.h"
#include "stm32f429i_discovery.h"
#endif

#include "TIM.h"
#include "CBUF.h"

/*
 *
 *
 *
 *
 * PC13		+		B7
 * PE6		+		B6
 * PE5		+		B5
 * PE4		+		B4
 * PE3		+		B3
 * PE2		+		B2
 * PC11		+		B1
 * PC12		+		B0
 */

//CS
//WR
//RD

//EN - Out	PG2		+
//RD - In	PG3		+

extern cBuffer buf;

void Parallel_Transmit();

void Parallel_EN_cmd(uint8_t STATE);

void Parallel_SendByte(uint8_t Byte);

void EXTI3_IRQHandler();

void init_ParallelTransmit();

void init_gpio_ParallelTransmit();

void init_TIMx();


void init_EXTI_PG3();


#endif /* PARALTRANSMIT_H_ */
