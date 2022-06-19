///*
// * CTrans.c
// *
// *  Created on: 17 θών. 2022 γ.
// *      Author: hard_
// */
#include "CTrans.h"
//
uint8_t Byte = 0;
cBuffer Buf_in;
cBuffer Buf_out;
uint8_t data_in[Size_of_cBUF];
uint8_t data_out[Size_of_cBUF];
//
void init_CTrans(){
	  Buffer_init(&Buf_in,data_in,Size_of_cBUF);
	  Buffer_init(&Buf_out,data_out,Size_of_cBUF);

//	    Buffer_add2end(&Buf_out,'B');
//	    Buffer_add2end(&Buf_out,'A');
//	    Buffer_add2end(&Buf_out,'B');
//	    Buffer_add2end(&Buf_out,'A');
//	    Buffer_add2end(&Buf_out,'I');
//	    Buffer_add2end(&Buf_out,'S');
//	    Buffer_add2end(&Buf_out,'Y');
//	    Buffer_add2end(&Buf_out,'O');
//	    Buffer_add2end(&Buf_out,'U');
	  Buffer_add2end(&Buf_out, 0xFF);

	  init_USART1();
	  init_USART_RR();

	  init_ParallelTransmit();
	  USART_RR_cmd(ENABLE);
}

void EXTI3_IRQHandler(){
	EXTI->PR |= EXTI_PR_PR3;
//	if((GPIOG->IDR & GPIO_IDR_IDR_3) == 0)
		Parallel_EN_cmd(DISABLE);
}

void TIM2_IRQHandler(){
	TIM2->SR &=~TIM_SR_UIF;
//	uint8_t temp;
//	if(Buffer_getfromEnd(&Buf_in,&temp))
//		Buffer_add2end(&Buf_out,temp);
	if((GPIOG->IDR & GPIO_IDR_IDR_3) && ((GPIOG->ODR & GPIO_ODR_ODR_2) == 0))
	{
		Parallel_Transmit(&Buf_out);
	}
}

void TIM3_IRQHandler(){
	TIM3->SR &=~TIM_SR_UIF;
	if(Buffer_add2end(&Buf_in,Byte))
	{
		TIMx_cmd(TIM3, DISABLE);
		USART_RR_cmd(ENABLE);
	}
}

void USART1_IRQHandler() {
	//haven't flag
	if ((USART1->SR & USART_SR_RXNE) == USART_SR_RXNE)
	{
		Byte = USART1->DR;
		if(Buffer_add2end(&Buf_in,Byte))
		{
			USART_RR_cmd(ENABLE);
		}
		else
		{
			USART_RR_cmd(DISABLE);
			TIMx_cmd(TIM3, ENABLE);
		}
	}
}

void init_USART_RR(){	//Ready to read
	  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	  GPIOB->MODER |= GPIO_MODER_MODER4_0;
	  init_TIM3();
}

void USART_RR_cmd(uint8_t STATE){	//Ready to read
	if(STATE!=0)
		GPIOB->BSRRL |= GPIO_BSRR_BS_4;
	else
		GPIOB->BSRRH |= GPIO_BSRR_BS_4;
}
