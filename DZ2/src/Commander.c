/*
 * Commander.c
 *
 *  Created on: 17 θών. 2022 γ.
 *      Author: hard_
 */

#include "Commander.h"

uint32_t Index_pixel_in = 0;
uint32_t Index_pixel_out = 0;
uint8_t Left_p = 1;
uint8_t Right_p = 1;
uint16_t Result_p = 1;

void TIM4_IRQHandler(){
	TIM4->SR &=~TIM_SR_UIF;
	if(Buffer_get_Data_len(&Buf_in)>1)
	{
		Buffer_getfromEnd(&Buf_in,&Left_p);
		Buffer_getfromEnd(&Buf_in,&Right_p);
		Convert_8to16(Left_p, Right_p, &Result_p);
		Index_pixel_in = Graphic_Load2screen(Result_p, Index_pixel_in);
	}
	if(Buffer_get_freespace(&Buf_out)>1)
	{
		Index_pixel_out = Graphic_Get4screen(&Result_p, Index_pixel_out);
		Convert_16to8(&Left_p, &Right_p, Result_p);
		Buffer_add2end(&Buf_out, Left_p);
		Buffer_add2end(&Buf_out, Right_p);
	}
}

void Convert_8to16(uint8_t left, uint8_t right, uint16_t* result){
	*result = (((uint16_t) left)<<8) & 0xFF00;
	*result |= ((uint16_t) right) & 0x00FF;
}

void Convert_16to8(uint8_t* left, uint8_t* right, uint16_t result){
	*left = (uint8_t)((result & 0xFF00)>>8);
	*right = (uint8_t)((result & 0x00FF));
}

void init_Commander(){
	init_TIM4();
}

void Commander_cmd(uint8_t STATE){
	TIMx_cmd(TIM4, STATE);
}

