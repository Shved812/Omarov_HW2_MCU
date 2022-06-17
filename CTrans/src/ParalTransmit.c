/*
 * ParalTransmit.c
 *
 *  Created on: 18 ��� 2022 �.
 *      Author: hard_
 */
#include "ParalTransmit.h"
//EN - in	PG2		+
//RD - out	PG3		+
cBuffer buf;
/*
 * PE2		+		B7
 * PE3		+		B6
 * PE4		+		B5
 * PE5		+		B4
 * PE6		+		B3
 * PC13		+		B2
 * PC11		+		B1
 * PC12		+		B0
 */
void Parallel_Transmit(){
	uint8_t temp;
	if(Buffer_getfromEnd(&buf,&temp))
		Parallel_SendByte(temp);
}

void Parallel_SendByte(uint8_t Byte){
	GPIOC->BSRRH |= GPIO_BSRR_BS_11|GPIO_BSRR_BS_12|GPIO_BSRR_BS_13;
	GPIOE->BSRRH |= GPIO_BSRR_BS_2|GPIO_BSRR_BS_3|GPIO_BSRR_BS_4|GPIO_BSRR_BS_5|GPIO_BSRR_BS_5;

	GPIOC->BSRRL |= ((Byte&0x01) >> 0) * GPIO_BSRR_BS_12;
	GPIOC->BSRRL |= ((Byte&0x02) >> 1) * GPIO_BSRR_BS_11;
	GPIOE->BSRRL |= ((Byte&0x04) >> 2) * GPIO_BSRR_BS_2;
	GPIOE->BSRRL |= ((Byte&0x08) >> 3) * GPIO_BSRR_BS_3;
	GPIOE->BSRRL |= ((Byte&0x10) >> 4) * GPIO_BSRR_BS_4;
	GPIOE->BSRRL |= ((Byte&0x20) >> 5) * GPIO_BSRR_BS_5;
	GPIOE->BSRRL |= ((Byte&0x40) >> 6) * GPIO_BSRR_BS_6;
	GPIOC->BSRRL |= ((Byte&0x80) >> 7) * GPIO_BSRR_BS_13;

	Parallel_EN_cmd(ENABLE);
}

void Parallel_EN_cmd(uint8_t STATE){
	if(STATE == 0)
		GPIOG->BSRRH |= GPIO_BSRR_BS_2;
	else
		GPIOG->BSRRL |= GPIO_BSRR_BS_2;
}

void init_ParallelTransmit(){
	init_gpio_ParallelTransmit();
	init_EXTI_PG3();
	init_TIM2();
}

void init_gpio_ParallelTransmit(){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;

	GPIOC->MODER &= ~GPIO_MODER_MODER11;
	GPIOC->MODER &= ~GPIO_MODER_MODER12;
	GPIOC->MODER &= ~GPIO_MODER_MODER13;
	GPIOE->MODER &= ~GPIO_MODER_MODER2;
	GPIOE->MODER &= ~GPIO_MODER_MODER3;
	GPIOE->MODER &= ~GPIO_MODER_MODER4;
	GPIOE->MODER &= ~GPIO_MODER_MODER5;
	GPIOE->MODER &= ~GPIO_MODER_MODER6;
	GPIOG->MODER &= ~GPIO_MODER_MODER2;
	GPIOG->MODER &= ~GPIO_MODER_MODER3;

	GPIOC->MODER |= GPIO_MODER_MODER11_0;
	GPIOC->MODER |= GPIO_MODER_MODER12_0;
	GPIOC->MODER |= GPIO_MODER_MODER13_0;
	GPIOE->MODER |= GPIO_MODER_MODER2_0;
	GPIOE->MODER |= GPIO_MODER_MODER3_0;
	GPIOE->MODER |= GPIO_MODER_MODER4_0;
	GPIOE->MODER |= GPIO_MODER_MODER5_0;
	GPIOE->MODER |= GPIO_MODER_MODER6_0;
	GPIOG->MODER |= GPIO_MODER_MODER2_0;

	//GPIOG->PUPDR |= GPIO_PUPDR_PUPDR3_1;

	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR11_0;
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR12_0;
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR13_0;
	GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR2_0;
	GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR3_0;
	GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR4_0;
	GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR5_0;
	GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6_0;
	GPIOG->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR2_0;
	GPIOG->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR3_0;

	Parallel_EN_cmd(DISABLE);
}

void init_EXTI_PG3(){
	  //EXTI_Init()
	  RCC->APB2ENR |= RCC_APB2Periph_SYSCFG;
	  SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI3_PG;
	  EXTI->IMR |= EXTI_IMR_MR3;	//mask of exti for enable
	  EXTI->RTSR |= EXTI_RTSR_TR3; 	//rising trigger
	  EXTI->FTSR |= EXTI_FTSR_TR3;	//falling trigger

	  NVIC_SetPriority(EXTI3_IRQn, 2);
	  NVIC_EnableIRQ(EXTI3_IRQn);

	  //EXTI->SWIER |= EXTI_SWIER_SWIER2; //software interrupt
}