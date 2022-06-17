/*
 * CBUF.c
 *
 *  Created on: 17 мая 2022 г.
 *      Author: hard_
 */
#include "CBUF.h"



void Buffer_init(cBuffer* buf, uint8_t* data, uint16_t size){
	buf->Data = data;
	buf->Size = size;
	buf->Data_len = 0;
	buf->Begin = 0;
	buf->End = buf->Begin;
}

uint8_t Buffer_add2end(cBuffer* buf, uint8_t byte){
	if(buf->Data_len == buf->Size)
		return 0;
	buf->Data[buf->End]=byte;
	buf->End+=1;
	buf->Data_len+=1;
	if(buf->End > buf->Size-1)
		buf->End=0;
	return 1;
}

uint8_t Buffer_getfromEnd(cBuffer* buf, uint8_t* byte){
	if(buf->Data_len==0)
		return 0;
	*byte=buf->Data[buf->Begin];
	buf->Begin+=1;
	buf->Data_len-=1;
	if(buf->Begin==buf->Size)
		buf->Begin=0;
	return 1;
}

void Catch_error(cBuffer* buf){
	for(uint8_t i=0;Buffer_add2end(buf,i);i++);
	uint8_t i=0;
	while(Buffer_getfromEnd(buf,&i)){
		i;
	}
}

void Buffer_fill(cBuffer* buf){
	for(uint8_t i=0;Buffer_add2end(buf,i);i++);
}
void Buffer_fill_ind(cBuffer* buf,uint16_t index){
	for(uint8_t i=0;Buffer_add2end(buf,i);i++)
		Buffer_add2end(buf,i);
}
void Buffer_fill_byte(cBuffer* buf,uint8_t byte){
	for(uint8_t i=0;Buffer_add2end(buf,byte);i++);
}
