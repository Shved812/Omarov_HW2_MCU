/*
 * Image.h
 *
 *  Created on: 1 мая 2022 г.
 *      Author: hard_
 */
#ifndef IMAGE_H_
#define IMAGE_H_

#ifndef STM32F4_h
#define STM32F4_H
#include "stm32f4xx.h"
#include "stm32f429i_discovery.h"
#endif

typedef struct _Image_t
{
  /*const */uint16_t *table; // Tabelle mit den Daten
  uint16_t width;        // Breite des Bildes (in Pixel)
  uint16_t height;       // Hoehe des Bildes  (in Pixel)
}Image;

extern Image Image1;
extern Image Image_menu;
#endif /* IMAGE_H_ */
