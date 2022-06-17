/*
 * Graphics_tools.h
 *
 *  Created on: 31 мая 2022 г.
 *      Author: hard_
 */
#ifndef GRAPHICS_TOOLS_H_
#define GRAPHICS_TOOLS_H_

#ifndef STM32F4_h
#define STM32F4_H
#include "stm32f4xx.h"
#include "stm32f429i_discovery.h"
#endif

#include "Image.h"
#include "LTDC.h"

void Graphic_DrawImage(Image *img, int16_t xpos, int16_t ypos);

void Graphic_DrawFrame(int16_t color, int16_t x_begin, int16_t y_begin, int16_t x_end, int16_t y_end);

void Graphic_reDrawFrame(Image* img, int16_t x_begin, int16_t y_begin, int16_t x_end, int16_t y_end);

uint16_t Graphic_ConvertColor2BM(uint16_t  Color);

void Graphic_ConvertImage2BW(Image *img, int16_t xpos, int16_t ypos);

void Graphic_ConvertCurrentSquareImage2BW();

void Graphic_ConvertCurrentImage2BW();

void Graphic_SaveImage();

void Graphic_DrawSavedImage();

void Graphic_FlipImage();

void Graphic_FlipSavedImage();

void Graphic_FlipSquareImage();

#endif /* GRAPHICS_TOOLS_H_ */
