/*
 * SDRAM.h
 *
 *  Created on: 1 мая 2022 г.
 *      Author: hard_
 */
//PB5
//PB6
//PC0
//PD0
//PD1
//PD8
//PD9
//PD10
//PD14
//PD15
//PE0
//PE1
//PE7
//PE8
//PE9
//PE10
//PE11
//PE12
//PE13
//PE14
//PE15
//PF0
//PF1
//PF2
//PF3
//PF4
//PF5
//PF11
//PF12
//PF13
//PF14
//PF15
//PG0
//PG1
//PG4
//PG5
//PG8
//PG15

#ifndef SDRAM_H_
#define SDRAM_H_

#ifndef STM32F4_h
#define STM32F4_H
#include "stm32f4xx.h"
#include "stm32f429i_discovery.h"
#endif

#define SDRAM_MAX_ADR         0x800000  // max=8MByte
#define SDRAM_START_ADR      ((uint32_t)0xD0000000)


void init_SDRAM();

void SDRAM_InitIO();

//FMC_Bank2_SDRAM
void SDRAM_InitFMC();

void SDRAM_InitSeq();

void SDRAM_Write16b(uint32_t, uint16_t);

uint16_t SDRAM_Read16b(uint32_t);


#endif /* SDRAM_H_ */
