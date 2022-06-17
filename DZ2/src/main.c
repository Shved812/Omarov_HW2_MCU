

#include "SPI5.h"
#include "SDRAM.h"
#include "LTDC.h"
#include "Image.h"
#include "Graphics_tools.h"
#include "TIM.h"

#define 	ENABLE		1
#define 	DISABLE		0
//#define 	N_buf		76800

#define 	FramePos0_x_begin		25
#define 	FramePos0_y_begin		60
#define 	FramePos0_x_end			225
#define 	FramePos0_y_end			128
#define 	FramePos1_x_begin		25
#define 	FramePos1_y_begin		140
#define 	FramePos1_x_end			225
#define 	FramePos1_y_end			200
#define 	FramePos2_x_begin		25
#define 	FramePos2_y_begin		210
#define 	FramePos2_x_end			225
#define 	FramePos2_y_end			278
#define 	FramePos3_x_begin		25
#define 	FramePos3_y_begin		285
#define 	FramePos3_x_end			225
#define 	FramePos3_y_end			312

uint8_t Count_clicks = 0;
uint8_t Pos_point = 0;
uint8_t Current_status = 1;

void TIM6_DAC_IRQHandler(){
	TIM6->SR &= ~TIM_SR_UIF;
	Pos_point++;
	Count_clicks = 0;
	switch (Pos_point){
	case 0:
		Graphic_reDrawFrame(&Image_menu,FramePos3_x_begin,FramePos3_y_begin,FramePos3_x_end,FramePos3_y_end);
		Graphic_DrawFrame(RGB_COL_WHITE,FramePos0_x_begin,FramePos0_y_begin,FramePos0_x_end,FramePos0_y_end);
		break;
	case 1:
		Graphic_reDrawFrame(&Image_menu,FramePos0_x_begin,FramePos0_y_begin,FramePos0_x_end,FramePos0_y_end);
		Graphic_DrawFrame(RGB_COL_WHITE,FramePos1_x_begin,FramePos1_y_begin,FramePos1_x_end,FramePos1_y_end);
		break;
	case 2:
		Graphic_reDrawFrame(&Image_menu,FramePos1_x_begin,FramePos1_y_begin,FramePos1_x_end,FramePos1_y_end);
		Graphic_DrawFrame(RGB_COL_WHITE,FramePos2_x_begin,FramePos2_y_begin,FramePos2_x_end,FramePos2_y_end);
		break;
	case 3:
		Graphic_reDrawFrame(&Image_menu,FramePos2_x_begin,FramePos2_y_begin,FramePos2_x_end,FramePos2_y_end);
		Graphic_DrawFrame(RGB_COL_WHITE,FramePos3_x_begin,FramePos3_y_begin,FramePos3_x_end,FramePos3_y_end);
		break;
	default:
		Pos_point=0;
		Graphic_reDrawFrame(&Image_menu,FramePos3_x_begin,FramePos3_y_begin,FramePos3_x_end,FramePos3_y_end);
		Graphic_DrawFrame(RGB_COL_WHITE,FramePos0_x_begin,FramePos0_y_begin,FramePos0_x_end,FramePos0_y_end);
		break;
	}
	TIM6_cmd(DISABLE);
}

void EXTI0_IRQHandler(){
	if(Current_status != 0)
	{
		Graphic_SaveImage();
		Current_status = 0;
		Pos_point = 0;
		Count_clicks = 0;
		Graphic_DrawImage(&Image_menu,0,0);
		Graphic_DrawFrame(RGB_COL_WHITE,FramePos0_x_begin,FramePos0_y_begin,FramePos0_x_end,FramePos0_y_end);

	}
	else
	{
		if(Count_clicks == 0)
		{
			//Graphic_DrawImage(&Buf_Image,0,0);
			Count_clicks++;
			TIM6_cmd(ENABLE);
		}
		else{
			TIM6_cmd(DISABLE);
			Count_clicks=0;
			switch (Pos_point){
			case 0:
				Graphic_DrawSavedImage();
				Current_status = Pos_point+1;
				Pos_point = 0;
				break;
			case 1:
				Graphic_DrawSavedImage();
				Graphic_ConvertCurrentSquareImage2BW();
				Current_status = Pos_point+1;
				Pos_point = 0;
				break;
			case 2:
				Graphic_DrawSavedImage();
				Graphic_FlipSquareImage();;
				Current_status = Pos_point+1;
				Pos_point = 0;
				break;
			case 3:
				LCD_FillLayer ( RGB_COL_BLACK ) ;
				Graphic_DrawImage(&Image1,0,40);
				Current_status = Pos_point+1;
				Pos_point = 0;
				break;
			}
		}


	}
	EXTI->PR |= EXTI_PR_PR0;
}

void init_EXTI_PA0(){
	  //EXTI_Init()
	  RCC->APB2ENR |= RCC_APB2Periph_SYSCFG;
	  SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;
	  EXTI->IMR |= EXTI_IMR_MR0;	//mask of exti for enable
	  EXTI->RTSR |= EXTI_RTSR_TR0; 	//rising trigger
	  EXTI->FTSR &= ~EXTI_FTSR_TR0;	//falling trigger

	  NVIC_SetPriority(EXTI0_IRQn, 2);
	  NVIC_EnableIRQ(EXTI0_IRQn);

	  //EXTI->SWIER |= EXTI_SWIER_SWIER0; //software interrupt
}

void init_gpio_button(){
	RCC->AHB1LPENR |= RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER &= ~GPIO_MODER_MODER0;
}

void init_button(){
	init_gpio_button();
	init_EXTI_PA0();
}

int main ( void )
{
  uint32_t n;
  // Init from the LCD
  init_LCD();
  // Init the layers
  LCD_LayerInit_Fullscreen();
  // switch to background
  LCD_SetLayer_1 ( ) ;
  // Fill the background completely with a color
  LCD_FillLayer ( RGB_COL_WHITE ) ;
  // switch to foreground
  LCD_SetLayer_2 ( ) ;
  // Fill the foreground completely with a color
  LCD_FillLayer ( RGB_COL_BLACK ) ;

  Graphic_DrawImage(&Image1,0,40);
  Graphic_ConvertCurrentSquareImage2BW();

  init_TIM6();
  TIM6_cmd(DISABLE);
  init_button();

  while ( 1 )
  {

  }
}



uint32_t sEE_TIMEOUT_UserCallback(void)
{
  /* TODO, implement your code here */
  while (1)
  {
  }
}

//#define  LCD_MAXX           ((uint16_t)240)      // Pixel in X-Richtung
//#define  LCD_MAXY           ((uint16_t)320)
