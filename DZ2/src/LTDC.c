/*
 * LTDC.c
 *
 *  Created on: 1 мая 2022 г.
 *      Author: hard_
 */
#include "LTDC.h"

static uint16_t CursorX, CursorY;
static uint32_t CursorPos;

void init_LCD(){

	init_LCD_IO();
	//P_LCD9341_InitIO();

	init_SPI5();
	//UB_SPI5_Init(SPI_MODE_0_MSB);

	LCD_InitChip();
	//P_LCD9341_InitChip();

	init_SDRAM();
	//UB_SDRAM_Init();

	LCD_InitLTCD();

	LCD_CurrentFrameBuffer=LCD_FRAME_BUFFER;

	CursorX=0;
	CursorY=0;
	CursorPos=0;

}



void init_LCD_IO(){
	//WRX GPIOD PD13
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	GPIOD->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR13_1;
	GPIOD->MODER |= GPIO_MODER_MODER13_0;
	//CS GPIOC PC2
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR2_1;
	GPIOC->MODER |= GPIO_MODER_MODER2_0;

	LCD_CS(1);
}

void LCD_InitChip()
{
    LCD_CMD(0xCA);
    LCD_DATA(0xC3);
    LCD_DATA(0x08);
    LCD_DATA(0x50);

    LCD_CMD(LCD_POWERB);	//LCD_POWERB	= 0xCF
    LCD_DATA(0x00);
    LCD_DATA(0xC1);
    LCD_DATA(0x30);

    LCD_CMD(LCD_POWER_SEQ);	//LCD_POWER_SEQ	= 0xED
    LCD_DATA(0x64);
    LCD_DATA(0x03);
    LCD_DATA(0x12);
    LCD_DATA(0x81);

    LCD_CMD(LCD_DTCA);		//LCD_DTCA		= 0xE8
    LCD_DATA(0x85);
    LCD_DATA(0x00);
    LCD_DATA(0x78);

    LCD_CMD(LCD_POWERA);	//LCD_POWERA	= 0xCB
    LCD_DATA(0x39);
    LCD_DATA(0x2C);
    LCD_DATA(0x00);
    LCD_DATA(0x34);
    LCD_DATA(0x02);

    LCD_CMD(LCD_PRC);		//LCD_PRC		= 0xF7
    LCD_DATA(0x20);

    LCD_CMD(LCD_DTCB);		//LCD_DTCB		= 0xEA
    LCD_DATA(0x00);
    LCD_DATA(0x00);

    LCD_CMD(LCD_FRC);		//LCD_FRC		= 0xB1
    LCD_DATA(0x00);
    LCD_DATA(0x1B);

    LCD_CMD(LCD_DFC);		//LCD_DFC		= 0xB6
    LCD_DATA(0x0A);
    LCD_DATA(0xA2);

    LCD_CMD(LCD_POWER1);	//LCD_POWER1	= 0xC0
    LCD_DATA(0x10);

    LCD_CMD(LCD_POWER2);	//LCD_POWER2	= 0xC1
    LCD_DATA(0x10);

    LCD_CMD(LCD_VCOM1);		//LCD_VCOM1		= 0xC5
    LCD_DATA(0x45);
    LCD_DATA(0x15);

    LCD_CMD(LCD_VCOM2);		//LCD_VCOM2		= 0xC7
    LCD_DATA(0x90);

    LCD_CMD(LCD_MAC);		//LCD_MAC		= 0x36
    LCD_DATA(0xC8);

    LCD_CMD(LCD_3GAMMA_EN);	//LCD_3GAMMA_EN	= 0xF2
    LCD_DATA(0x00);

    LCD_CMD(LCD_RGB_INTERFACE);	//LCD_RGB_INTERFACE	= 0xB0
    LCD_DATA(0xC2);

    LCD_CMD(LCD_DFC);		//LCD_DFC		= 0xB6
    LCD_DATA(0x0A);
    LCD_DATA(0xA7);
    LCD_DATA(0x27);
    LCD_DATA(0x04);
    //------------------------

    LCD_CMD(LCD_COLUMN_ADDR);	//LCD_COLUMN_ADDR	= 0x2A
    LCD_DATA(0x00);
    LCD_DATA(0x00);
    LCD_DATA(0x00);
    LCD_DATA(0xEF);
    //------------------------

    LCD_CMD(LCD_PAGE_ADDR);	//LCD_PAGE_ADDR	= 0x2B
    LCD_DATA(0x00);
    LCD_DATA(0x00);
    LCD_DATA(0x01);
    LCD_DATA(0x3F);

    LCD_CMD(LCD_INTERFACE);	//LCD_INTERFACE	= 0xF6
    LCD_DATA(0x01);
    LCD_DATA(0x00);
    LCD_DATA(0x06);
    //------------------------

    LCD_CMD(LCD_GRAM);		//LCD_GRAM		= 0x2C
    LCD_Delay(10);
    //------------------------

    LCD_CMD(LCD_GAMMA);		//LCD_GAMMA		= 0x26
    LCD_DATA(0x01);
    //------------------------

    LCD_CMD(LCD_PGAMMA);	//LCD_PGAMMA	= 0xE0
    LCD_DATA(0x0F);
    LCD_DATA(0x29);
    LCD_DATA(0x24);
    LCD_DATA(0x0C);
    LCD_DATA(0x0E);
    LCD_DATA(0x09);
    LCD_DATA(0x4E);
    LCD_DATA(0x78);
    LCD_DATA(0x3C);
    LCD_DATA(0x09);
    LCD_DATA(0x13);
    LCD_DATA(0x05);
    LCD_DATA(0x17);
    LCD_DATA(0x11);
    LCD_DATA(0x00);

    LCD_CMD(LCD_NGAMMA);	//LCD_NGAMMA	= 0xE1
    LCD_DATA(0x00);
    LCD_DATA(0x16);
    LCD_DATA(0x1B);
    LCD_DATA(0x04);
    LCD_DATA(0x11);
    LCD_DATA(0x07);
    LCD_DATA(0x31);
    LCD_DATA(0x33);
    LCD_DATA(0x42);
    LCD_DATA(0x05);
    LCD_DATA(0x0C);
    LCD_DATA(0x0A);
    LCD_DATA(0x28);
    LCD_DATA(0x2F);
    LCD_DATA(0x0F);
    //------------------------

    LCD_CMD(LCD_SLEEP_OUT);	//LCD_SLEEP_OUT	= 0x11
    LCD_Delay(10);
    LCD_CMD(LCD_DISPLAY_ON); //LCD_DISPLAY_ON	= 0x29
    //------------------------

    LCD_CMD(LCD_GRAM);		//LCD_GRAM		= 0x2C
}

void LCD_InitLTCD(){
	RCC->APB2ENR |= RCC_APB2ENR_LTDCEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA2DEN;

	LCD_AF_config();

	RCC_PLLSAIConf(192, 7, 4); //PLLSAI on 6MHz
	RCC->DCKCFGR |= 2<<16;
	//RCC_LTDCCLKDivConfig(0x20000); //RCC_PLLSAIDivR_Div8

	RCC->CR |= RCC_CR_PLLSAION;
	while ((RCC->CR & RCC_CR_PLLSAIRDY) == 0); //PLLSAI on and wait

	/*
	 //---------------------------------------
	  // Timer konfig
	  // HSync = 10       VSync = 2
	  // HBP   = 20       VBP   = 2
	  // HFP   = 10       VFP   = 4
	  //
	  // Portrait  : W=240, H=320
	  //---------------------------------------
	  LTDC_InitStruct.LTDC_HorizontalSync = 9;       // HSync-1
	  LTDC_InitStruct.LTDC_VerticalSync = 1;         // VSync-1
	  LTDC_InitStruct.LTDC_AccumulatedHBP = 29;      // HSync+HBP-1
	  LTDC_InitStruct.LTDC_AccumulatedVBP = 3;       // VSync+VBP-1
	  LTDC_InitStruct.LTDC_AccumulatedActiveW = 269; // HSync+HBP+W-1
	  LTDC_InitStruct.LTDC_AccumulatedActiveH = 323; // VSync+VBP+H-1
	  LTDC_InitStruct.LTDC_TotalWidth = 279;         // HSync+HBP+W+HFP-1
	  LTDC_InitStruct.LTDC_TotalHeigh = 327;         // VSync+VBP+H+VFP-1
	 */
	  LTDC->SSCR |= (DISPLAY_HSYNC - 1) << 16;
	  LTDC->SSCR |= (DISPLAY_VSYNC - 1);

	  LTDC->BPCR |= (DISPLAY_HSYNC+DISPLAY_HBP-1) << 16;
	  LTDC->BPCR |= (DISPLAY_VSYNC+DISPLAY_VBP-1);

	  LTDC->AWCR |= (DISPLAY_WIDTH + DISPLAY_HSYNC + DISPLAY_HBP - 1) << 16;
	  LTDC->AWCR |= (DISPLAY_HEIGHT + DISPLAY_VSYNC + DISPLAY_VBP - 1);

	  LTDC->TWCR |= (DISPLAY_WIDTH + DISPLAY_HSYNC + DISPLAY_HBP + DISPLAY_HFP -1)<< 16;
	  LTDC->TWCR |= (DISPLAY_HEIGHT + DISPLAY_VSYNC + DISPLAY_VBP + DISPLAY_VFP - 1);
}
/*
void RCC_LTDCCLKDivConfig(uint32_t RCC_PLLSAIDivR)
{
  uint32_t tmpreg = 0;

  tmpreg = RCC->DCKCFGR;

  // Clear PLLSAIDIVR[2:0] bits
  tmpreg &= ~RCC_DCKCFGR_PLLSAIDIVR;

  // Set PLLSAIDIVR values
  tmpreg |= RCC_PLLSAIDivR;

  // Store the new value
  RCC->DCKCFGR = tmpreg;
}
*/

void RCC_PLLSAIConf(uint32_t PLLSAIN, uint32_t PLLSAIQ, uint32_t PLLSAIR)
{
  RCC->PLLSAICFGR = (PLLSAIN << 6) | (PLLSAIQ << 24) | (PLLSAIR << 28);
}

void LCD_AF_config(){
	//GPIOA init
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	GPIOA->MODER |= GPIO_MODER_MODER3_1;
	GPIOA->MODER |= GPIO_MODER_MODER4_1;
	GPIOA->MODER |= GPIO_MODER_MODER6_1;
	GPIOA->MODER |= GPIO_MODER_MODER11_1;
	GPIOA->MODER |= GPIO_MODER_MODER12_1;

	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR3_1;
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR4_1;
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6_1;
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR11_1;
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR12_1;

	GPIOA->AFR[0] |= GPIO_AF_LTDC<<(3*4);
	GPIOA->AFR[0] |= GPIO_AF_LTDC<<(4*4);
	GPIOA->AFR[0] |= GPIO_AF_LTDC<<(6*4);
	GPIOA->AFR[1] |= GPIO_AF_LTDC<<(3*4);
	GPIOA->AFR[1] |= GPIO_AF_LTDC<<(4*4);

	//GPIOB init
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

	GPIOB->MODER |= GPIO_MODER_MODER0_1;
	GPIOB->MODER |= GPIO_MODER_MODER1_1;
	GPIOB->MODER |= GPIO_MODER_MODER8_1;
	GPIOB->MODER |= GPIO_MODER_MODER9_1;
	GPIOB->MODER |= GPIO_MODER_MODER10_1;
	GPIOB->MODER |= GPIO_MODER_MODER11_1;

	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR0_1;
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR1_1;
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR8_1;
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR9_1;
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR10_1;
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR11_1;

	GPIOB->AFR[0] |= 0x09<<(0*4); //GPIO_AF_CAN1?
	GPIOB->AFR[0] |= 0x09<<(1*4); //Wha?
	GPIOB->AFR[1] |= GPIO_AF_LTDC<<(0*4);
	GPIOB->AFR[1] |= GPIO_AF_LTDC<<(1*4);
	GPIOB->AFR[1] |= GPIO_AF_LTDC<<(2*4);
	GPIOB->AFR[1] |= GPIO_AF_LTDC<<(3*4);

	//GPIOC init
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

	GPIOC->MODER |= GPIO_MODER_MODER6_1;
	GPIOC->MODER |= GPIO_MODER_MODER7_1;
	GPIOC->MODER |= GPIO_MODER_MODER10_1;

	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6_1;
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR7_1;
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR10_1;

	GPIOC->AFR[0] |= GPIO_AF_LTDC<<(6*4);
	GPIOC->AFR[0] |= GPIO_AF_LTDC<<(7*4);
	GPIOC->AFR[1] |= GPIO_AF_LTDC<<(2*4);

	//GPIOD init
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

	GPIOD->MODER |= GPIO_MODER_MODER3_1;
	GPIOD->MODER |= GPIO_MODER_MODER6_1;

	GPIOD->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR3_1;
	GPIOD->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6_1;

	GPIOD->AFR[0] |= GPIO_AF_LTDC<<(3*4);
	GPIOD->AFR[0] |= GPIO_AF_LTDC<<(6*4);

	//GPIOF init
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;

	GPIOF->MODER |= GPIO_MODER_MODER10_1;

	GPIOF->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR10_1;

	GPIOF->AFR[1] |= GPIO_AF_LTDC<<(2*4);

	//GPIOG init
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;

	GPIOG->MODER |= GPIO_MODER_MODER6_1;
	GPIOG->MODER |= GPIO_MODER_MODER7_1;
	GPIOG->MODER |= GPIO_MODER_MODER10_1;
	GPIOG->MODER |= GPIO_MODER_MODER11_1;
	GPIOG->MODER |= GPIO_MODER_MODER12_1;

	GPIOG->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6_1;
	GPIOG->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR7_1;
	GPIOG->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR10_1;
	GPIOG->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR11_1;
	GPIOG->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR12_1;

	GPIOG->AFR[0] |= GPIO_AF_LTDC<<(6*4);
	GPIOG->AFR[0] |= GPIO_AF_LTDC<<(7*4);
	GPIOG->AFR[1] |= 0x09<<(2*4);
	GPIOG->AFR[1] |= GPIO_AF_LTDC<<(3*4);
	GPIOG->AFR[1] |= 0x09<<(4*4);
}

void LCD_CS(uint8_t SET){
	if(SET == 0)
		GPIOC->BSRRH |= GPIO_BSRR_BS_2;
	else
		GPIOC->BSRRL |= GPIO_BSRR_BS_2;
}

void LCD_WRX(uint8_t SET){
	if(SET == 0)
		GPIOD->BSRRH |= GPIO_BSRR_BS_13;
	else
		GPIOD->BSRRL |= GPIO_BSRR_BS_13;
}

void LCD_CMD(uint8_t byte)
{
  LCD_WRX(0);

  LCD_CS(0);

  SPI5_SendByte(byte); //A recive dosen't use mb occuring of eror
  SPI5_ReceiveByte(); //Fix

  LCD_Delay(10); //Habr say that it dose't matter

  LCD_CS(1);
}

void LCD_DATA(uint8_t byte)
{
  LCD_WRX(1);

  LCD_CS(0);

  SPI5_SendByte(byte);
  SPI5_ReceiveByte(); //Fix
  // kleine Pause
  LCD_Delay(10);

  LCD_CS(1);
}

void LCD_Delay(uint8_t t){
	for(int i=0;i<t;i++);
}

void LCD_LayerInit_Fullscreen(){
	  uint32_t whsppos = 0;
	  uint32_t wvsppos = 0;
	  uint32_t dcblue = 0;
	  uint32_t dcgreen = 0;
	  uint32_t dcred = 0;
	  uint32_t dcalpha = 0;
	  uint32_t cfbp = 0;

	  //----------LAYER1 INIT
	whsppos = (LCD_MAXX + 30 - 1) << 16;
	  LTDC_Layer1->WHPCR &= ~(LTDC_LxWHPCR_WHSTPOS | LTDC_LxWHPCR_WHSPPOS);
	  LTDC_Layer1->WHPCR = (30 | whsppos);

	  /* Configures the vertical start and stop position */
	wvsppos = (LCD_MAXY + 4 - 1) << 16;
	  LTDC_Layer1->WVPCR &= ~(LTDC_LxWVPCR_WVSTPOS | LTDC_LxWVPCR_WVSPPOS);
	  LTDC_Layer1->WVPCR  = (4 | wvsppos);

	  /* Specifies the pixel format */
	  LTDC_Layer1->PFCR &= ~(LTDC_LxPFCR_PF);
	  LTDC_Layer1->PFCR = (LTDC_Pixelformat_RGB565);

	  /* Configures the default color values */
	  //dcblue = (0 << 0);
	  dcgreen = (0 << 8);
	  dcred = (0 << 16);
	  dcalpha = (0 << 24);
	  LTDC_Layer1->DCCR &=  ~(LTDC_LxDCCR_DCBLUE | LTDC_LxDCCR_DCGREEN | LTDC_LxDCCR_DCRED | LTDC_LxDCCR_DCALPHA);
	  LTDC_Layer1->DCCR = (dcblue | dcgreen | dcred | dcalpha);

	  /* Specifies the constant alpha value */
	  LTDC_Layer1->CACR &= ~(LTDC_LxCACR_CONSTA);
	  LTDC_Layer1->CACR = (255);

	  /* Specifies the blending factors */
	  LTDC_Layer1->BFCR &= ~(LTDC_LxBFCR_BF2 | LTDC_LxBFCR_BF1);
	  LTDC_Layer1->BFCR = (LTDC_BlendingFactor1_CA | LTDC_BlendingFactor2_CA);

	  /* Configures the color frame buffer start address */
	  LTDC_Layer1->CFBAR &= ~(LTDC_LxCFBAR_CFBADD);
	  LTDC_Layer1->CFBAR = (LCD_FRAME_BUFFER);

	  /* Configures the color frame buffer pitch in byte */
	  cfbp = ((LCD_MAXX * 2) << 16);
	  LTDC_Layer1->CFBLR  &= ~(LTDC_LxCFBLR_CFBLL | LTDC_LxCFBLR_CFBP);
	  LTDC_Layer1->CFBLR  = (((LCD_MAXX * 2) + 3) | cfbp);

	  /* Configures the frame buffer line number */
	  LTDC_Layer1->CFBLNR  &= ~(LTDC_LxCFBLNR_CFBLNBR);
	  LTDC_Layer1->CFBLNR  = (LCD_MAXY);

	  //----------LAYER2 INIT

	whsppos = (LCD_MAXX + 30 - 1) << 16;
	  LTDC_Layer2->WHPCR &= ~(LTDC_LxWHPCR_WHSTPOS | LTDC_LxWHPCR_WHSPPOS);
	  LTDC_Layer2->WHPCR = (30 | whsppos);

	  /* Configures the vertical start and stop position */
	wvsppos = (LCD_MAXY + 4 - 1) << 16;
	  LTDC_Layer2->WVPCR &= ~(LTDC_LxWVPCR_WVSTPOS | LTDC_LxWVPCR_WVSPPOS);
	  LTDC_Layer2->WVPCR  = (4 | wvsppos);

	  /* Specifies the pixel format */
	  LTDC_Layer2->PFCR &= ~(LTDC_LxPFCR_PF);
	  LTDC_Layer2->PFCR = (LTDC_Pixelformat_RGB565);

	  /* Configures the default color values */
	  dcblue = (0 << 0);
	  dcgreen = (0 << 8);
	  dcred = (0 << 16);
	  dcalpha = (0 << 24);
	  LTDC_Layer2->DCCR &=  ~(LTDC_LxDCCR_DCBLUE | LTDC_LxDCCR_DCGREEN | LTDC_LxDCCR_DCRED | LTDC_LxDCCR_DCALPHA);
	  LTDC_Layer2->DCCR = (dcblue | dcgreen | dcred | dcalpha);

	  /* Specifies the constant alpha value */
	  LTDC_Layer2->CACR &= ~(LTDC_LxCACR_CONSTA);
	  LTDC_Layer2->CACR = (255);

	  /* Specifies the blending factors */
	  LTDC_Layer2->BFCR &= ~(LTDC_LxBFCR_BF2 | LTDC_LxBFCR_BF1);
	  LTDC_Layer2->BFCR = (LTDC_BlendingFactor1_PAxCA | LTDC_BlendingFactor2_PAxCA);

	  /* Configures the color frame buffer start address */
	  LTDC_Layer2->CFBAR &= ~(LTDC_LxCFBAR_CFBADD);
	  LTDC_Layer2->CFBAR = (LCD_FRAME_BUFFER + LCD_FRAME_OFFSET);

	  /* Configures the color frame buffer pitch in byte */
	  cfbp = ((LCD_MAXX * 2) << 16);
	  LTDC_Layer2->CFBLR  &= ~(LTDC_LxCFBLR_CFBLL | LTDC_LxCFBLR_CFBP);
	  LTDC_Layer2->CFBLR  = (((LCD_MAXX * 2) + 3) | cfbp);

	  /* Configures the frame buffer line number */
	  LTDC_Layer2->CFBLNR  &= ~(LTDC_LxCFBLNR_CFBLNBR);
	  LTDC_Layer2->CFBLNR  = (LCD_MAXY);

	  LTDC->SRCR = LTDC_SRCR_IMR; //ReloadConfig

	  LTDC_Layer1CMD(1);
	  LTDC_Layer2CMD(1);

	  LTDC->SRCR = LTDC_SRCR_IMR; //ReloadConfig

	  LTDC_DitherCMD(1);

	  LTDC_CMD(1);

}

void LTDC_Layer1CMD(uint8_t SET)
{
  if (SET != 0)
  {
    LTDC_Layer1->CR |= LTDC_LxCR_LEN;
  }
  else
  {
    LTDC_Layer1->CR &= ~LTDC_LxCR_LEN;
  }
}

void LTDC_Layer2CMD(uint8_t SET)
{
  if (SET != 0)
  {
    LTDC_Layer2->CR |= LTDC_LxCR_LEN;
  }
  else
  {
    LTDC_Layer2->CR &= ~LTDC_LxCR_LEN;
  }
}

void LTDC_DitherCMD(uint8_t SET)
{
  if (SET != 0)
  {
    LTDC->GCR |= LTDC_GCR_DTEN;
  }
  else
  {
    LTDC->GCR &= ~(uint32_t)LTDC_GCR_DTEN;
  }
}

void LTDC_CMD(uint8_t SET)
{
  if (SET != 0)
  {
    LTDC->GCR |= LTDC_GCR_LTDCEN;
  }
  else
  {
    LTDC->GCR &= ~(uint32_t)LTDC_GCR_LTDCEN;
  }
}

void LCD_SetLayer_1()
{
  LCD_CurrentFrameBuffer = LCD_FRAME_BUFFER;
  LCD_CurrentLayer = 0;
}

void LCD_SetLayer_2()
{
  LCD_CurrentFrameBuffer = LCD_FRAME_BUFFER + LCD_FRAME_OFFSET;
  LCD_CurrentLayer = 1;
}

void LCD_FillLayer(uint16_t color)
{
  uint32_t index = 0;

  for (index = 0x00; index < LCD_FRAME_OFFSET; index+=2) {
    *(uint16_t*)(LCD_CurrentFrameBuffer + index) = color;
  }
}

void LCD_DrawPixel(uint16_t color){
	{
	  *(volatile uint16_t*)(CursorPos)=color;	//del volatile
	    CursorX++;
	    if(CursorX>=LCD_MAXX) {
	      CursorX=0;
	      CursorY++;
	      if(CursorY>=LCD_MAXY) CursorY=0;
	    }

	  CursorPos=LCD_CurrentFrameBuffer+(2*((CursorY*LCD_MAXX)+CursorX));
	}
}

void LCD_SetCursor2Draw(uint16_t xpos, uint16_t ypos)
{
  CursorX=xpos;
  CursorY=ypos;

  CursorPos=LCD_CurrentFrameBuffer+(2*((CursorY*LCD_MAXX)+CursorX));
}

void LCD_SetCursorPos(uint32_t pos)
{
  CursorPos=LCD_CurrentFrameBuffer+pos;
}
