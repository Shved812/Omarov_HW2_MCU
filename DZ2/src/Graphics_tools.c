/*
 * Graphics_tools.c
 *
 *  Created on: 31 мая 2022 г.
 *      Author: hard_
 */
#include "Graphics_tools.h"

void Graphic_DrawImage(Image *img, int16_t xpos, int16_t ypos)
{
  uint16_t xn,yn;
  uint16_t *pixel;
  uint16_t Color;

  pixel=&img->table[0];
//horizontal sampling:
    for(yn = 0; yn < img->height; yn++) {
      LCD_SetCursor2Draw(xpos,yn+ypos);
      for(xn = 0; xn < img->width; xn++) {
        Color=pixel[yn*img->width+xn];
        LCD_DrawPixel(Color);
      }
    }
// vertical sampling
/*
    for(yn = 0; yn < img->height; yn++) {
      UB_LCD_SetCursor2Draw(img->height+xpos-yn-1,ypos);
      for(xn = 0; xn < img->width; xn++) {
        color=pixel[yn*img->width+xn];
        UB_LCD_DrawPixel(color);
      }
    }
  }
*/
};

void Graphic_DrawFrame(int16_t Color, int16_t x_begin, int16_t y_begin, int16_t x_end, int16_t y_end){
	uint16_t xn,yn;

	LCD_SetCursor2Draw(x_begin,y_begin);
	for(xn=x_begin;xn<x_end+1;xn++)
		LCD_DrawPixel(Color);

	LCD_SetCursor2Draw(x_begin,y_end);
	for(xn=x_begin;xn<x_end+1;xn++)
		LCD_DrawPixel(Color);

	for(yn=y_begin;yn<y_end+1;yn++){
		LCD_SetCursor2Draw(x_begin,yn);
		LCD_DrawPixel(Color);
	}

	for(yn=y_begin;yn<y_end+1;yn++){
		LCD_SetCursor2Draw(x_end,yn);
		LCD_DrawPixel(Color);
	}
};

void Graphic_reDrawFrame(Image* img, int16_t x_begin, int16_t y_begin, int16_t x_end, int16_t y_end){
	uint16_t xn,yn;
	uint16_t *pixel;
	uint16_t Color;
	pixel=&img->table[0];

	LCD_SetCursor2Draw(x_begin,y_begin);
	for(xn=x_begin;xn<x_end+1;xn++){
		Color=pixel[y_begin*img->width+xn];
		LCD_DrawPixel(Color);
	}
	LCD_SetCursor2Draw(x_begin,y_end);
	for(xn=x_begin;xn<x_end+1;xn++){
		Color=pixel[y_end*img->width+xn];
		LCD_DrawPixel(Color);
	}
	for(yn=y_begin;yn<y_end+1;yn++){
		LCD_SetCursor2Draw(x_begin,yn);
		Color=pixel[yn*img->width+x_begin];
		LCD_DrawPixel(Color);
	}

	for(yn=y_begin;yn<y_end+1;yn++){
		LCD_SetCursor2Draw(x_end,yn);
		Color=pixel[yn*img->width+x_end];
		LCD_DrawPixel(Color);
	}
}

uint16_t Graphic_ConvertColor2BM(uint16_t  Color){
	uint16_t R;
	uint16_t G;
	uint16_t B;
	R=((Color&0xF800)>>11);
	G=((Color&0x07E0)>>6);
	B=((Color&0x001F));
	uint16_t Color_BW = (R+G+B)/3;
	uint16_t Sum = (Color_BW<<11) + (Color_BW<<6) + (Color_BW);
	return Sum;
};

void Graphic_ConvertImage2BW(Image *img, int16_t xpos, int16_t ypos)
{
	  uint16_t xn,yn;
	  const uint16_t *pixel;
	  uint16_t color;

	  pixel=&img->table[0];

	    for(yn = 0; yn < img->height; yn++) {
	      LCD_SetCursor2Draw(xpos,yn+ypos);
	      for(xn = 0; xn < img->width; xn++) {
	        color = pixel[yn*img->width+xn];
	        color = Graphic_ConvertColor2BM(color);
	        LCD_DrawPixel(color);
	      }
	    }

};
void Graphic_ConvertCurrentImage2BW(){
	  for(uint32_t i=0x00;i<LCD_FRAME_OFFSET;i+=2)
		  *(uint16_t*)(LCD_CurrentFrameBuffer + i) = Graphic_ConvertColor2BM(*(uint16_t*)(LCD_CurrentFrameBuffer + i));
}
void Graphic_ConvertCurrentSquareImage2BW()
{

	uint16_t a,b,c,d;
	for(uint32_t j=0;j<LCD_MAXY;j+=2)
		for(uint32_t i=0;i<LCD_MAXX;i+=2)
		{
			a = Graphic_ConvertColor2BM(*(uint16_t*)(LCD_CurrentFrameBuffer + 2*((i)+(j)*LCD_MAXX)));
			b = Graphic_ConvertColor2BM(*(uint16_t*)(LCD_CurrentFrameBuffer + 2*((i)+(j+1)*LCD_MAXX)));
			c = Graphic_ConvertColor2BM(*(uint16_t*)(LCD_CurrentFrameBuffer + 2*((i+1)+(j)*LCD_MAXX)));
			d = Graphic_ConvertColor2BM(*(uint16_t*)(LCD_CurrentFrameBuffer + 2*((i+1)+(j+1)*LCD_MAXX)));

			*(uint16_t*)(LCD_CurrentFrameBuffer + 2*((i)+(j)*LCD_MAXX))		= a;
			*(uint16_t*)(LCD_CurrentFrameBuffer + 2*((i)+(j+1)*LCD_MAXX))	= b;
			*(uint16_t*)(LCD_CurrentFrameBuffer + 2*((i+1)+(j)*LCD_MAXX))	= c;
			*(uint16_t*)(LCD_CurrentFrameBuffer + 2*((i+1)+(j+1)*LCD_MAXX))	= d;
		}

};

void Graphic_DrawSavedImage(){
	uint32_t index = 0;
	for (index = 0x00; index < LCD_FRAME_OFFSET; index+=2)
		*(uint16_t*)(LCD_CurrentFrameBuffer+index)=*(uint16_t*)(LCD_FRAME_BUFFER+2*LCD_FRAME_OFFSET+index);
}

void Graphic_SaveImage(){
	uint32_t index = 0;
	for (index = 0x00; index < LCD_FRAME_OFFSET; index+=2)
		*(uint16_t*)(LCD_FRAME_BUFFER+2*LCD_FRAME_OFFSET+index)=*(uint16_t*)(LCD_CurrentFrameBuffer+index);
}

void Graphic_FlipImage(){
	uint16_t a,b,c,d;
	for(uint32_t j=40;j<LCD_MAXY/2;j++)
		for(uint32_t i=0;i<LCD_MAXX/2;i++)
		{

			a = *(uint16_t*)(LCD_CurrentFrameBuffer + 2*(i+j*LCD_MAXX));
			b = *(uint16_t*)(LCD_CurrentFrameBuffer + 2*((i+40)*LCD_MAXX-(j-40)+LCD_MAXX-1));
			c = *(uint16_t*)(LCD_CurrentFrameBuffer + 2*(-(j-40-40)*LCD_MAXX-i+LCD_MAXX*LCD_MAXX-1));
			d = *(uint16_t*)(LCD_CurrentFrameBuffer + 2*(-(i-40)*LCD_MAXX+(j-40)+LCD_MAXX*(LCD_MAXX-1)));

			*(uint16_t*)(LCD_CurrentFrameBuffer + 2*(i+j*240)) 								  = d;
			*(uint16_t*)(LCD_CurrentFrameBuffer + 2*((i+40)*240-(j-40)+240-1)) 			  = a;
			*(uint16_t*)(LCD_CurrentFrameBuffer + 2*(-(j-40-40)*240-i+240*240-1))	  = b;
			*(uint16_t*)(LCD_CurrentFrameBuffer + 2*(-(i-40)*240+(j-40)+240*(240-1)))  = c;

		}
}

void Graphic_FlipSavedImage(){
	uint16_t a,b,c,d;
	for(uint32_t j=40;j<LCD_MAXY/2;j++)
		for(uint32_t i=0;i<LCD_MAXX/2;i++)
		{

			a = *(uint16_t*)(LCD_FRAME_BUFFER+2*LCD_FRAME_OFFSET + 2*(i+j*LCD_MAXX));
			b = *(uint16_t*)(LCD_FRAME_BUFFER+2*LCD_FRAME_OFFSET + 2*((i+40)*LCD_MAXX-(j-40)+LCD_MAXX-1));
			c = *(uint16_t*)(LCD_FRAME_BUFFER+2*LCD_FRAME_OFFSET + 2*(-(j-40-40)*LCD_MAXX-i+LCD_MAXX*LCD_MAXX-1));
			d = *(uint16_t*)(LCD_FRAME_BUFFER+2*LCD_FRAME_OFFSET + 2*(-(i-40)*LCD_MAXX+(j-40)+LCD_MAXX*(LCD_MAXX-1)));

			*(uint16_t*)(LCD_FRAME_BUFFER+2*LCD_FRAME_OFFSET + 2*(i+j*LCD_MAXX)) 								  = d;
			*(uint16_t*)(LCD_FRAME_BUFFER+2*LCD_FRAME_OFFSET + 2*((i+40)*LCD_MAXX-(j-40)+LCD_MAXX-1)) 			  = a;
			*(uint16_t*)(LCD_FRAME_BUFFER+2*LCD_FRAME_OFFSET + 2*(-(j-40-40)*LCD_MAXX-i+LCD_MAXX*LCD_MAXX-1))	  = b;
			*(uint16_t*)(LCD_FRAME_BUFFER+2*LCD_FRAME_OFFSET + 2*(-(i-40)*LCD_MAXX+(j-40)+LCD_MAXX*(LCD_MAXX-1))) = c;

		}
}

void Graphic_FlipSquareImage(){
	uint16_t a[4],b[4],c[4],d[4];
	for(uint32_t j=40;j<LCD_MAXY/2;j+=2)
		for(uint32_t i=0;i<LCD_MAXX/2;i+=2)
		{

			a[0] = *(uint16_t*)(LCD_CurrentFrameBuffer + 2*((i)+(j)*LCD_MAXX));
			a[1] = *(uint16_t*)(LCD_CurrentFrameBuffer + 2*((i)+(j+1)*LCD_MAXX));
			a[2] = *(uint16_t*)(LCD_CurrentFrameBuffer + 2*((i+1)+(j)*LCD_MAXX));
			a[3] = *(uint16_t*)(LCD_CurrentFrameBuffer + 2*((i+1)+(j+1)*LCD_MAXX));

			b[0] = *(uint16_t*)(LCD_CurrentFrameBuffer + 2*((i+40)*LCD_MAXX-(j-40)+LCD_MAXX-1));
			b[1] = *(uint16_t*)(LCD_CurrentFrameBuffer + 2*((i+40)*LCD_MAXX-(j-40+1)+LCD_MAXX-1));
			b[2] = *(uint16_t*)(LCD_CurrentFrameBuffer + 2*((i+40+1)*LCD_MAXX-(j-40)+LCD_MAXX-1));
			b[3] = *(uint16_t*)(LCD_CurrentFrameBuffer + 2*((i+40+1)*LCD_MAXX-(j-40+1)+LCD_MAXX-1));

			c[0] = *(uint16_t*)(LCD_CurrentFrameBuffer + 2*(-(j-40-40)*LCD_MAXX-(i)+LCD_MAXX*LCD_MAXX-1));
			c[1] = *(uint16_t*)(LCD_CurrentFrameBuffer + 2*(-(j-40-40+1)*LCD_MAXX-(i)+LCD_MAXX*LCD_MAXX-1));
			c[2] = *(uint16_t*)(LCD_CurrentFrameBuffer + 2*(-(j-40-40)*LCD_MAXX-(i+1)+LCD_MAXX*LCD_MAXX-1));
			c[3] = *(uint16_t*)(LCD_CurrentFrameBuffer + 2*(-(j-40-40+1)*LCD_MAXX-(i+1)+LCD_MAXX*LCD_MAXX-1));

			d[0] = *(uint16_t*)(LCD_CurrentFrameBuffer + 2*(-(i-40)*LCD_MAXX+(j-40)+LCD_MAXX*(LCD_MAXX-1)));
			d[1] = *(uint16_t*)(LCD_CurrentFrameBuffer + 2*(-(i-40)*LCD_MAXX+(j-40+1)+LCD_MAXX*(LCD_MAXX-1)));
			d[2] = *(uint16_t*)(LCD_CurrentFrameBuffer + 2*(-(i-40+1)*LCD_MAXX+(j-40)+LCD_MAXX*(LCD_MAXX-1)));
			d[3] = *(uint16_t*)(LCD_CurrentFrameBuffer + 2*(-(i-40+1)*LCD_MAXX+(j-40+1)+LCD_MAXX*(LCD_MAXX-1)));

			*(uint16_t*)(LCD_CurrentFrameBuffer + 2*((i)+(j)*LCD_MAXX))     = d[0];
			*(uint16_t*)(LCD_CurrentFrameBuffer + 2*((i)+(j+1)*LCD_MAXX))   = d[1];
			*(uint16_t*)(LCD_CurrentFrameBuffer + 2*((i+1)+(j)*LCD_MAXX))   = d[2];
			*(uint16_t*)(LCD_CurrentFrameBuffer + 2*((i+1)+(j+1)*LCD_MAXX)) = d[3];

			*(uint16_t*)(LCD_CurrentFrameBuffer + 2*((i+40)*LCD_MAXX-(j-40)+LCD_MAXX-1))     = a[0];
			*(uint16_t*)(LCD_CurrentFrameBuffer + 2*((i+40)*LCD_MAXX-(j-40+1)+LCD_MAXX-1))   = a[1];
			*(uint16_t*)(LCD_CurrentFrameBuffer + 2*((i+40+1)*LCD_MAXX-(j-40)+LCD_MAXX-1))   = a[2];
			*(uint16_t*)(LCD_CurrentFrameBuffer + 2*((i+40+1)*LCD_MAXX-(j-40+1)+LCD_MAXX-1)) = a[3];

			*(uint16_t*)(LCD_CurrentFrameBuffer + 2*(-(j-40-40)*LCD_MAXX-(i)+LCD_MAXX*LCD_MAXX-1))     = b[0];
			*(uint16_t*)(LCD_CurrentFrameBuffer + 2*(-(j-40-40+1)*LCD_MAXX-(i)+LCD_MAXX*LCD_MAXX-1))   = b[1];
			*(uint16_t*)(LCD_CurrentFrameBuffer + 2*(-(j-40-40)*LCD_MAXX-(i+1)+LCD_MAXX*LCD_MAXX-1))   = b[2];
			*(uint16_t*)(LCD_CurrentFrameBuffer + 2*(-(j-40-40+1)*LCD_MAXX-(i+1)+LCD_MAXX*LCD_MAXX-1)) = b[3];

			*(uint16_t*)(LCD_CurrentFrameBuffer + 2*(-(i-40)*LCD_MAXX+(j-40)+LCD_MAXX*(LCD_MAXX-1)))     = c[0];
			*(uint16_t*)(LCD_CurrentFrameBuffer + 2*(-(i-40)*LCD_MAXX+(j-40+1)+LCD_MAXX*(LCD_MAXX-1)))   = c[1];
			*(uint16_t*)(LCD_CurrentFrameBuffer + 2*(-(i-40+1)*LCD_MAXX+(j-40)+LCD_MAXX*(LCD_MAXX-1)))   = c[2];
			*(uint16_t*)(LCD_CurrentFrameBuffer + 2*(-(i-40+1)*LCD_MAXX+(j-40+1)+LCD_MAXX*(LCD_MAXX-1))) = c[3];

		}
}
