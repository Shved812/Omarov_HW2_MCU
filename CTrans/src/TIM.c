/*
 * TIM.c
 *
 *  Created on: 3 θών. 2022 γ.
 *      Author: hard_
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

void init_TIM2(){
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	//TIM1->CR1 |= TIM_CR1_OPM;
	//TIM1->CR1 |= TIM_CR1_CKD_1;
	TIM2->ARR=200; //max CNT
	TIM2->PSC=90-1; //weight CNT

	TIM2->DIER |= TIM_DIER_UIE; //enable interruption

	NVIC_SetPriority(TIM2_IRQn,4);
	NVIC_EnableIRQ(TIM2_IRQn);

	TIM2->CR1 |= TIM_CR1_CEN;

}

void init_TIM3(){
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	//TIM1->CR1 |= TIM_CR1_OPM;
	//TIM1->CR1 |= TIM_CR1_CKD_1;
	TIM2->ARR=2000; //max CNT
	TIM2->PSC=900-1; //weight CNT

	TIM2->DIER |= TIM_DIER_UIE; //enable interruption

	NVIC_SetPriority(TIM3_IRQn,3);
	NVIC_EnableIRQ(TIM3_IRQn);

	TIMx_cmd(TIM3, ENABLE);
	TIMx_cmd(TIM3, DISABLE);
	//TIM2->CR1 |= TIM_CR1_CEN;
	//TIM2->CR1
}

void init_TIM6(){
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	TIM6->ARR = 90000;
	TIM6->PSC = 2000-1;

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
void TIM2_cmd(uint8_t STATE){
	TIM2->CR1 &= ~TIM_CR1_CEN;
	if(STATE != 0)
		TIM2->CR1 |= TIM_CR1_CEN;
}
void TIM3_cmd(uint8_t STATE){
	TIM3->CR1 &= ~TIM_CR1_CEN;
	if(STATE != 0)
		TIM3->CR1 |= TIM_CR1_CEN;
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
void TIM2_ARR(uint16_t ARR){
	TIM2->ARR = ARR;
}
void TIM3_ARR(uint16_t ARR){
	TIM3->ARR = ARR;
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
void TIM2_PSC(uint16_t PSC){
	TIM2->PSC = PSC;
}
void TIM3_PSC(uint16_t PSC){
	TIM3->PSC = PSC;
}
void TIM6_PSC(uint16_t PSC){
	TIM6->PSC = PSC;
}
void TIM7_PSC(uint16_t PSC){
	TIM7->PSC = PSC;
}

//void init_TIMx(TIM_TypeDef* TIMx);
void TIMx_cmd(TIM_TypeDef* TIMx,uint8_t STATE){
	TIMx->CR1 &= ~TIM_CR1_CEN;
	if(STATE != 0)
		TIMx->CR1 |= TIM_CR1_CEN;
};

void TIMx_ARR(TIM_TypeDef* TIMx, uint16_t ARR){
	TIMx->ARR = ARR;
};

void TIMx_PSC(TIM_TypeDef* TIMx, uint16_t PSC){
	TIMx->PSC = PSC;
};

//void init_TIMx(TIM_TypeDef* TIMx){
//	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
//	//TIMx->CR1 |= TIM_CR1_OPM;
//	//TIMx->CR1 |= TIM_CR1_CKD_1;
//	TIMx->ARR=20000; //max CNT
//	TIMx->PSC=9000-1; //weight CNT
//
//	TIMx->DIER |= TIM_DIER_UIE; //enable interruption
//
//	//NVIC_SetPriority(TIM _IRQn,4);
//	//NVIC_EnableIRQ(TIM _IRQn);
//
//	TIMx->CR1 |= TIM_CR1_CEN;
//
//}
