/*
 * USART.h
 *
 *  Created on: 4 мая 2022 г.
 *      Author: hard_
 */

#ifndef STM32F4_H
#define STM32F4_h

#include "stm32f4xx.h"
#include "stm32f429i_discovery.h"

#endif

#ifndef USART_H_
#define USART_H_



void USART1_IRQHandler();

void init_gpio_as_AF_for_USART1();

void init_gpio_as_AF_for_USART6();

void init_USART6();

void init_USART1();


uint8_t put_char_usart1(uint8_t);


void get_char_usart1(uint16_t*);

uint8_t put_char_usart6(uint8_t);


void get_char_usart6(uint16_t*);


#endif /* USART_H_ */
