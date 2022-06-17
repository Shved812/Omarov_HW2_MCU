/*
 * LTDC.h
 *
 *  Created on: 1 мая 2022 г.
 *      Author: hard_
 */
//PD13
//PC2
//PA3
//PA4
//PA6
//PA11
//PA12
//PB0
//PB1
//PB8
//PB9
//PB10
//PB11
//PC6
//PC7
//PC10
//PD3
//PD6
//PF10
//PG6
//PG7
//PG10
//PG11
//PG12

#ifndef LTDC_H_
#define LTDC_H_

#ifndef STM32F4_h
#define STM32F4_H
#include "stm32f4xx.h"
#include "stm32f429i_discovery.h"
#endif

#include "SPI5.h"
#include "SDRAM.h"

typedef struct Picture_t
{
  const uint8_t *table; // Tabelle mit den Daten
  uint32_t size;        // Anzahl der Bytes
}Picture;

extern Picture Jpg;

#define  RGB_COL_BLACK          0x0000
#define  RGB_COL_BLUE           0x001F
#define  RGB_COL_GREEN          0x07E0
#define  RGB_COL_RED            0xF800
#define  RGB_COL_WHITE          0xFFFF

#define  RGB_COL_CYAN           0x07FF
#define  RGB_COL_MAGENTA        0xF81F
#define  RGB_COL_YELLOW         0xFFE0

#define  RGB_COL_GREY           0xF7DE

#define LCD_SLEEP_OUT            0x11   // Sleep out register
#define LCD_GAMMA                0x26   // Gamma register
#define LCD_DISPLAY_OFF          0x28   // Display off register
#define LCD_DISPLAY_ON           0x29   // Display on register
#define LCD_COLUMN_ADDR          0x2A   // Column address register
#define LCD_PAGE_ADDR            0x2B   // Page address register
#define LCD_GRAM                 0x2C   // GRAM register
#define LCD_MAC                  0x36   // Memory Access Control register
#define LCD_PIXEL_FORMAT         0x3A   // Pixel Format register
#define LCD_WDB                  0x51   // Write Brightness Display register
#define LCD_WCD                  0x53   // Write Control Display register
#define LCD_RGB_INTERFACE        0xB0   // RGB Interface Signal Control
#define LCD_FRC                  0xB1   // Frame Rate Control register
#define LCD_BPC                  0xB5   // Blanking Porch Control register
#define LCD_DFC                  0xB6   // Display Function Control register
#define LCD_POWER1               0xC0   // Power Control 1 register
#define LCD_POWER2               0xC1   // Power Control 2 register
#define LCD_VCOM1                0xC5   // VCOM Control 1 register
#define LCD_VCOM2                0xC7   // VCOM Control 2 register
#define LCD_POWERA               0xCB   // Power control A register
#define LCD_POWERB               0xCF   // Power control B register
#define LCD_PGAMMA               0xE0   // Positive Gamma Correction register
#define LCD_NGAMMA               0xE1   // Negative Gamma Correction register
#define LCD_DTCA                 0xE8   // Driver timing control A
#define LCD_DTCB                 0xEA   // Driver timing control B
#define LCD_POWER_SEQ            0xED   // Power on sequence register
#define LCD_3GAMMA_EN            0xF2   // 3 Gamma enable register
#define LCD_INTERFACE            0xF6   // Interface control register
#define LCD_PRC                  0xF7   // Pump ratio control register

#define  DISPLAY_HSYNC            ((uint16_t)10)
#define  DISPLAY_HBP              ((uint16_t)20)
#define  DISPLAY_HFP              ((uint16_t)10)
#define  DISPLAY_VSYNC            ((uint16_t)2)
#define  DISPLAY_VBP              ((uint16_t)2)
#define  DISPLAY_VFP              ((uint16_t)4)
#define  DISPLAY_WIDTH            ((uint16_t)240)
#define  DISPLAY_HEIGHT			  ((uint16_t)320)

#define  LCD_MAXX           ((uint16_t)240)      // Pixel in X-Richtung
#define  LCD_MAXY           ((uint16_t)320)      // Pixel in Y-Richtung
#define  LCD_PIXEL  		LCD_MAXX*LCD_MAXY

#define LTDC_Pixelformat_RGB565                    ((uint32_t)0x00000002)

uint32_t LCD_CurrentFrameBuffer;
uint32_t LCD_CurrentLayer;
#define  LCD_FRAME_BUFFER     ((uint32_t)0xD0000000)//SDRAM_START_ADR
#define  LCD_FRAME_OFFSET   ((uint32_t)(LCD_PIXEL*2))



void init_LCD();

void init_LCD_IO();

void LCD_InitChip();

void LCD_InitLTCD();

void RCC_PLLSAIConf(uint32_t, uint32_t, uint32_t);

void LCD_AF_config();

void LCD_CS(uint8_t);

void LCD_WRX(uint8_t);
void LCD_CMD(uint8_t);

void LCD_DATA(uint8_t);

void LCD_Delay(uint8_t);

void LCD_LayerInit_Fullscreen();

void LTDC_Layer1CMD(uint8_t);

void LTDC_Layer2CMD(uint8_t);

void LTDC_DitherCMD(uint8_t);

void LTDC_CMD(uint8_t);

void LCD_SetLayer_1();

void LCD_SetLayer_2();

void LCD_FillLayer(uint16_t);

void LCD_DrawPixel(uint16_t);

void LCD_SetCursor2Draw(uint16_t, uint16_t);

void LCD_SetCursorPos(uint32_t pos);
#endif /* LTDC_H_ */
