/*
 * SPI5.h
 *
 *  Created on: 30 апр. 2022 г.
 *      Author: hard_
 */
//PF7
//PF8
//PF9

#ifndef SPI5_H_
#define SPI5_H_

#ifndef STM32F4_h
#define STM32F4_H
#include "stm32f4xx.h"
#include "stm32f429i_discovery.h"
#endif

void init_GPIO_as_AF();

//spi_mode_0_msb
void init_SPI5();

void SPI5_SendData(uint16_t Data);

void SPI5_SendByte(uint8_t Data);

uint16_t SPI5_ReceiveData();

uint8_t SPI5_ReceiveByte();


#endif /* SPI5_H_ */
