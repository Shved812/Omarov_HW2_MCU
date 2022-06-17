/*
 * Led.c
 *
 *  Created on: 26 апр. 2022 г.
 *      Author: hard_
 */

#include "Led.h"


void init_gpio(){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
	GPIOG->MODER |= GPIO_MODER_MODER13_0 | GPIO_MODER_MODER14_0;
}
void Led3_on(){
	GPIOG->BSRRL = GPIO_BSRR_BS_13;
}
void Led4_on(){
	GPIOG->BSRRL = GPIO_BSRR_BS_14;
}
void Led3_off(){
	GPIOG->BSRRH = GPIO_BSRR_BS_13;
}
void Led4_off(){
	GPIOG->BSRRH = GPIO_BSRR_BS_14;
}
void Blink_Led3(){
	GPIOG->ODR ^= GPIO_ODR_ODR_13;
}
void Blink_Led4() {
	GPIOG->ODR ^= GPIO_ODR_ODR_14;
}

