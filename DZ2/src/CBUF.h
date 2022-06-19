/*
 * CBUF.h
 *
 *  Created on: 17 мая 2022 г.
 *      Author: hard_
 */
#ifndef CBUF_H_
#define CBUF_H_

#ifndef STM32F4_H
#define STM32F4_H
#include "stm32f4xx.h"
#include "stm32f429i_discovery.h"
#endif

typedef struct
{
	uint8_t* Data;		//point of Data array
	uint16_t Size;		//Size of Buf
	uint16_t Begin;		//index begin of data
	uint16_t End;		//index end of data
	uint16_t Data_len;	//Current size of buffer data
}cBuffer;

void Buffer_init(cBuffer*, uint8_t*, uint16_t);

uint8_t Buffer_add2end(cBuffer* , uint8_t );

uint8_t Buffer_getfromEnd(cBuffer* , uint8_t* );

void Catch_error(cBuffer* );

void Buffer_fill(cBuffer* buf);
void Buffer_fill_ind(cBuffer* buf,uint16_t index);
void Buffer_fill_byte(cBuffer* buf,uint8_t byte);

uint16_t Buffer_get_Data_len(cBuffer* buf);
uint16_t Buffer_get_freespace(cBuffer* buf);

void Buffer_clean(cBuffer* buf);
#endif /* CBUF_H_ */
