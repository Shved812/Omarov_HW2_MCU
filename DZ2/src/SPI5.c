/*
 * SPI5.c
 *
 *  Created on: 30 апр. 2022 г.
 *      Author: hard_
 */
#include "SPI5.h"

void init_GPIO_as_AF(){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;

	  GPIOF->MODER |= GPIO_MODER_MODER9_1; // MOSI an PF9
	  GPIOF->MODER |= GPIO_MODER_MODER8_1; // MISO an PF8
	  GPIOF->MODER |= GPIO_MODER_MODER7_1; // SCK an PF7

	  GPIOF->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR9_1;
	  GPIOF->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR8_1;
	  GPIOF->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR7_1;

	  GPIOF->AFR[1] |= GPIO_AF_SPI5<<(1*4);
	  GPIOF->AFR[1] |= GPIO_AF_SPI5;
	  GPIOF->AFR[0] |= GPIO_AF_SPI5<<(7*4);
}

//spi_mode_0_msb
void init_SPI5(){
	RCC->APB2ENR |= RCC_APB2ENR_SPI5EN;
	init_GPIO_as_AF();

    RCC->APB2RSTR |= RCC_APB2RSTR_SPI5RST;
    RCC->APB2RSTR &= ~RCC_APB2RSTR_SPI5RST;

	//SPI5->CR1 &= ~SPI_CR1_BIDIMODE; //BiDirectional mode
	SPI5->CR1 |= SPI_CR1_MSTR; //master
	SPI5->CR1 |= SPI_CR1_SSI;
	//SPI5->CR1 &= ~SPI_CR1_DFF;//Data lenght 8b
	//SPI5->CR1 &= ~SPI_CR1_CPOL; //Clock POLarity
	//SPI5->CR1 &= ~SPI_CR1_CPHA; // Clock PHAse
	SPI5->CR1 |= SPI_CR1_SSM; //slave chosen SSI
	SPI5->CR1 |= SPI_CR1_BR_0 | SPI_CR1_BR_1; //boudrate fpclk/16
	//SPI5->CR1 &= ~SPI_CR1_LSBFIRST; //MSB folow first
	SPI5->CRCPR |= 7;
	//SPI5->I2SCFGR &= ~SPI_I2SCFGR_I2SMOD; //disable i2s mode (enable spi mode)
	SPI5->CR1 |= SPI_CR1_SPE; // enable spi
}

void SPI5_SendData(uint16_t Data){
	SPI5->DR = Data;
}

void SPI5_SendByte(uint8_t Data){
	while((SPI5->SR & SPI_SR_TXE)==0);
	SPI5_SendData(Data);
	uint8_t ret_val = SPI5_ReceiveData();
	return ret_val;
}

uint16_t SPI5_ReceiveData(){
	return SPI5->DR;
}

uint8_t SPI5_ReceiveByte(){
	while((SPI5->SR & SPI_SR_RXNE)==0);
	return SPI5_ReceiveData();
}

