#ifndef __LED_H
#define __LED_H

#include "stm32f1xx_hal.h"
#include "main.h"

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t


#define Bank1_LCD_D    ((u32)0x60020000)    //Disp Data ADDR
#define Bank1_LCD_C    ((u32)0x60000000)	   //Disp Reg ADDR

#define Set_Rst GPIOD->BSRR = ((uint16_t)0x2000);
#define Clr_Rst GPIOD->BRR  = ((uint16_t)0x2000);

#define Lcd_Light_ON   GPIOA->BSRR = ((uint16_t)0x0002) ;
#define Lcd_Light_OFF  GPIOA->BRR  = ((uint16_t)0x0002) ;



//Lcd初始化及其低级控制函数
void InitBackGround(void);
void Lcd_Initialize(void);
void LCD_WR_REG(u16 Index,u16 CongfigTemp);
void Lcd_ColorBox(u16 x,u16 y,u16 xLong,u16 yLong,u32 Color);

void LCD_Fill_Pic(u16 x, u16 y,u16 pic_H, u16 pic_V, const unsigned char* pic);
void BlockWrite(unsigned int Xstart,unsigned int Xend,unsigned int Ystart,unsigned int Yend);

void LCD_DispString_CH(uint16_t usX,uint16_t usY,const uint8_t *pstr,uint16_t usColor_Background, uint16_t usColor_Foreground,uint8_t font);
void LCD_DispString_EN_CH(uint16_t usX,uint16_t usY,const uint8_t *pstr,uint16_t usColor_Background, uint16_t usColor_Foreground,uint8_t font);

/*定义常见颜色*/
// #define red 0x001f
// #define blue 0xf800
// #define green 0x07e0
// #define black 0x0000
// #define white 0xffff
// #define yellow 0x07ff
// #define orange 0x05bf
// #define Chocolate4 0x4451
// #define Grey 0xefbd//灰色

//24位色定义
//#define White          0xFFFFFF
//#define Black          0x000000
//#define Blue           0x0000FF
//#define Blue2          0x00A0FF
//#define Red            0xFF0000
//#define Magenta        0xFF00FF
//#define Green          0x00FF00
//#define Cyan           0x00FFFF
//#define Yellow         0xFFFF00

////16位色定义
#define White          0xFFFF
#define Black          0x0000
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xE000
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0

#define BABY_BLUE		0xE7FF
#define BRIGHT_GREEN	0x67E0
#define DEEP_SKY_BLUE	0x5FF
#define MARINE_BLUE		0x22F
#endif

