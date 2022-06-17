

/* Includes */
#include "stm32f4xx.h"
#include "stm32f429i_discovery.h"
#include "CBUF.h"
#include "Led.h"
#include "ParalTransmit.h"
#include "TIM.h"
#include "USART.h"

#define Size_of_cBUF	1024
#define St_validation_byte 0xAB

//PG4 - USART_RR

uint8_t Byte=0;

void EXTI3_IRQHandler(){
	EXTI->PR |= EXTI_PR_PR3;
	if((GPIOG->IDR & GPIO_IDR_IDR_3) == 0)
		Parallel_EN_cmd(DISABLE);
}

void TIM2_IRQHandler(){
	TIM2->SR &=~TIM_SR_UIF;
	if((GPIOG->IDR & GPIO_IDR_IDR_3) && ((GPIOG->ODR & GPIO_ODR_ODR_2) == 0))
	{
		//for(int i=0;i<1000;i++);
		//Parallel_SendByte(temp);
		Parallel_Transmit();
	}
	uint8_t temp = 0xAB;
}

void TIM3_IRQHandler(){
	TIM3->SR &=~TIM_SR_UIF;
	if(Buffer_add2end(&buf,Byte))
	{
		TIMx_cmd(TIM3, DISABLE);
		GPIOG->BSRRL |= GPIO_BSRR_BS_4;
	}
}

void USART1_IRQHandler() {
	//haven't flag
	if ((USART1->SR & USART_SR_RXNE) == USART_SR_RXNE)
	{
		Byte = USART1->DR;
		if(Buffer_add2end(&buf,Byte))
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

void init_USART_RR(){
	  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
	  GPIOG->MODER |= GPIO_MODER_MODER4_0;
	  init_TIM3();
}

void USART_RR_cmd(uint8_t STATE){ //Ready to read
	if(STATE!=0)
		GPIOG->BSRRL |= GPIO_BSRR_BS_4;
	else
		GPIOG->BSRRH |= GPIO_BSRR_BS_4;
}

int main(void)
{
  int i = 0;

  uint8_t data[Size_of_cBUF];

  init_gpio();
  Buffer_init(&buf,data,Size_of_cBUF);

  //Buffer_fill(&buf);
  //Buffer_fill_ind(&buf,2);
  Buffer_add2end(&buf,0xAB);
  Buffer_add2end(&buf,0xCD);
  //Buffer_fill_byte(&buf,St_validation_byte);


  init_USART1();
  init_USART_RR();

  init_ParallelTransmit();
  USART_RR_cmd(ENABLE);

//  init_EXTI_PG3();
//  Parallel_EN_cmd(ENABLE);
  while (1)
  {
	  i++;
	  for(int k=0; k<10000000; k++);
	  Blink_Led4();
  }
}

uint32_t sEE_TIMEOUT_UserCallback(void)
{
  while (1)
  {
  }
}
