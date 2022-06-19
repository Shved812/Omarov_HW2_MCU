/*
 * CTrans.h
 *
 *  Created on: 17 θών. 2022 γ.
 *      Author: hard_
 */
#ifndef CTRANS_H_
#define CTRANS_H_

#ifndef STM32F4_H
#define STM32F4_H
#include "stm32f4xx.h"
#include "stm32f429i_discovery.h"
#endif

#include "CBUF.h"
#include "Led.h"
#include "ParalTransmit.h"
#include "TIM.h"
#include "USART.h"

#define Size_of_cBUF	1024
#define St_validation_byte 0xAB

extern uint8_t Byte;
extern cBuffer Buf_in;
extern cBuffer Buf_out;
extern uint8_t data_in[Size_of_cBUF];
extern uint8_t data_out[Size_of_cBUF];


void init_CTrans();

void EXTI3_IRQHandler();

void TIM2_IRQHandler();

void TIM3_IRQHandler();

void USART1_IRQHandler();

void init_USART_RR();

void USART_RR_cmd(uint8_t STATE);


#endif /* CTRANS_H_ */
