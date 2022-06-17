/*
 * TIM.c
 *
 *  Created on: 3 θών. 2022 γ.
 *      Author: hard_
 */
/*
void TIM6_DAC_IRQHandler(){
	TIM6->SR &= ~TIM_SR_UIF;
}
*/
#include "TIM.h"

void TIM1_UP_TIM10_IRQHandler(){
	TIM1->SR &=~TIM_SR_UIF;
}



void TIM7_IRQHandler(){
	TIM7->SR &= ~TIM_SR_UIF;
}


void init_TIM1(){
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	//TIM1->CR1 |= TIM_CR1_OPM;
	//TIM1->CR1 |= TIM_CR1_CKD_1;
	TIM1->ARR=20000; //max CNT
	TIM1->PSC=9000-1; //weight CNT

	TIM1->DIER |= TIM_DIER_UIE; //enable interruption

	NVIC_SetPriority(TIM1_UP_TIM10_IRQn,7);
	NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);

	TIM1->CR1 |= TIM_CR1_CEN;

}

void init_TIM6(){
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	TIM6->ARR = 2500;
	TIM6->PSC = 9000-1;

	TIM6->DIER |= TIM_DIER_UIE;

	NVIC_SetPriority(TIM6_DAC_IRQn, 8);
	NVIC_EnableIRQ(TIM6_DAC_IRQn);

	TIM6->CR1 |= TIM_CR1_CEN;
}
void init_TIM7(){
	RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
	TIM7->ARR = 5000-1;
	TIM7->PSC = 500-1;

	TIM7->DIER |= TIM_DIER_UIE;

	NVIC_SetPriority(TIM7_IRQn, 8);
	NVIC_EnableIRQ(TIM7_IRQn);

	TIM7->CR1 |= TIM_CR1_CEN;
}

void TIM1_cmd(uint8_t STATE){
	TIM1->CR1 &= ~TIM_CR1_CEN;
	if(STATE != 0)
		TIM1->CR1 |= TIM_CR1_CEN;
}
void TIM6_cmd(uint8_t STATE){
	TIM6->CR1 &= ~TIM_CR1_CEN;
	if(STATE != 0)
		TIM6->CR1 |= TIM_CR1_CEN;
}
void TIM7_cmd(uint8_t STATE){
	TIM7->CR1 &= ~TIM_CR1_CEN;
	if(STATE != 0)
		TIM7->CR1 |= TIM_CR1_CEN;
}
void TIM1_ARR(uint16_t ARR){
	TIM1->ARR = ARR;
}
void TIM6_ARR(uint16_t ARR){
	TIM6->ARR = ARR;
}
void TIM7_ARR(uint16_t ARR){
	TIM7->ARR = ARR;
}
void TIM1_PSC(uint16_t PSC){
	TIM1->PSC = PSC;
}
void TIM6_PSC(uint16_t PSC){
	TIM6->PSC = PSC;
}
void TIM7_PSC(uint16_t PSC){
	TIM7->PSC = PSC;
}
