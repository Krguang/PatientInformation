#include "lcd.h"
#include "fatfs.h"
#include "ascii.h"

//LCD的画笔颜色和背景色	   
uint16_t FRONT_COLOR=Black;	//画笔颜色
uint16_t BACK_COLOR=White;  //背景色 


void Delay(__IO u32 nCount)
{	
	volatile int i;
	for(i=0;i<7200;i++)
    for(; nCount != 0; nCount--);
}  
 
void LCD_Rst(void)
{			
    Clr_Rst;
    Delay(10000);					   
    Set_Rst;		 	 
    Delay(10000);	
}
static void WriteComm(u16 CMD)
{			
	*(__IO u16 *) (Bank1_LCD_C) = CMD;
}
static void WriteData(u16 tem_data)
{			
	*(__IO u16 *) (Bank1_LCD_D) = tem_data;
}

/**********************************************
Lcd初始化函数
***********************************************/
void Lcd_Initialize(void)
{	
	//Delay(20);
	HAL_Delay(1);
	LCD_Rst();

// 	WriteComm(0xBF);
// 	a = *(__IO u16 *) (Bank1_LCD_D); 
// 	printf("ID=%04x\r\n",a);
// 	a = *(__IO u16 *) (Bank1_LCD_D); 
// 	printf("ID=%04x\r\n",a);
// a = *(__IO u16 *) (Bank1_LCD_D); 
// 	printf("ID=%04x\r\n",a);
// 	a = *(__IO u16 *) (Bank1_LCD_D); 
// 	printf("ID=%04x\r\n",a);
// a = *(__IO u16 *) (Bank1_LCD_D); 
// 	printf("ID=%04x\r\n",a);
// 	a = *(__IO u16 *) (Bank1_LCD_D); 
// 	printf("ID=%04x\r\n",a);	

	//************* Start Initial Sequence **********//
WriteComm(0xFF); // EXTC Command Set enable register 
WriteData(0xFF); 
WriteData(0x98); 
WriteData(0x06); 

WriteComm(0xBA); // SPI Interface Setting 
WriteData(0xE0); 

WriteComm(0xBC); // GIP 1 
WriteData(0x03); 
WriteData(0x0F); 
WriteData(0x63); 
WriteData(0x69); 
WriteData(0x01); 
WriteData(0x01); 
WriteData(0x1B); 
WriteData(0x11); 
WriteData(0x70); 
WriteData(0x73); 
WriteData(0xFF); 
WriteData(0xFF); 
WriteData(0x08); 
WriteData(0x09); 
WriteData(0x05); 
WriteData(0x00);
WriteData(0xEE); 
WriteData(0xE2); 
WriteData(0x01); 
WriteData(0x00);
WriteData(0xC1); 

WriteComm(0xBD); // GIP 2 
WriteData(0x01); 
WriteData(0x23); 
WriteData(0x45); 
WriteData(0x67); 
WriteData(0x01); 
WriteData(0x23); 
WriteData(0x45); 
WriteData(0x67); 

WriteComm(0xBE); // GIP 3 
WriteData(0x00); 
WriteData(0x22); 
WriteData(0x27); 
WriteData(0x6A); 
WriteData(0xBC); 
WriteData(0xD8); 
WriteData(0x92); 
WriteData(0x22); 
WriteData(0x22); 

WriteComm(0xC7); // Vcom 
WriteData(0x1E);
 
WriteComm(0xED); // EN_volt_reg 
WriteData(0x7F); 
WriteData(0x0F); 
WriteData(0x00); 

WriteComm(0xC0); // Power Control 1
WriteData(0xE3); 
WriteData(0x0B); 
WriteData(0x00);
 
WriteComm(0xFC);
WriteData(0x08); 

WriteComm(0xDF); // Engineering Setting 
WriteData(0x00); 
WriteData(0x00); 
WriteData(0x00); 
WriteData(0x00); 
WriteData(0x00); 
WriteData(0x02); 

WriteComm(0xF3); // DVDD Voltage Setting 
WriteData(0x74); 

WriteComm(0xB4); // Display Inversion Control 
WriteData(0x00); 
WriteData(0x00); 
WriteData(0x00); 

WriteComm(0xF7); // 480x854
WriteData(0x81); 

WriteComm(0xB1); // Frame Rate 
WriteData(0x00); 
WriteData(0x10); 
WriteData(0x14); 

WriteComm(0xF1); // Panel Timing Control 
WriteData(0x29); 
WriteData(0x8A); 
WriteData(0x07); 

WriteComm(0xF2); //Panel Timing Control 
WriteData(0x40); 
WriteData(0xD2); 
WriteData(0x50); 
WriteData(0x28); 

WriteComm(0xC1); // Power Control 2 
WriteData(0x17);
WriteData(0X85); 
WriteData(0x85); 
WriteData(0x20); 

WriteComm(0xE0); 
WriteData(0x00); //P1 
WriteData(0x0C); //P2 
WriteData(0x15); //P3 
WriteData(0x0D); //P4 
WriteData(0x0F); //P5 
WriteData(0x0C); //P6 
WriteData(0x07); //P7 
WriteData(0x05); //P8 
WriteData(0x07); //P9 
WriteData(0x0B); //P10 
WriteData(0x10); //P11 
WriteData(0x10); //P12 
WriteData(0x0D); //P13 
WriteData(0x17); //P14 
WriteData(0x0F); //P15 
WriteData(0x00); //P16 

WriteComm(0xE1); 
WriteData(0x00); //P1 
WriteData(0x0D); //P2 
WriteData(0x15); //P3 
WriteData(0x0E); //P4 
WriteData(0x10); //P5 
WriteData(0x0D); //P6 
WriteData(0x08); //P7 
WriteData(0x06); //P8 
WriteData(0x07); //P9 
WriteData(0x0C); //P10 
WriteData(0x11); //P11 
WriteData(0x11); //P12 
WriteData(0x0E); //P13 
WriteData(0x17); //P14 
WriteData(0x0F); //P15 
WriteData(0x00); //P16

WriteComm(0x35); //Tearing Effect ON 
WriteData(0x00); 

WriteComm(0x36); 
WriteData(0x60); 

WriteComm(0x3A); 
WriteData(0x55); 

WriteComm(0x11); //Exit Sleep 
//Delay(120); 
HAL_Delay(10);
WriteComm(0x29); // Display On 

Lcd_Light_ON;

}
/******************************************
函数名：Lcd写命令函数
功能：向Lcd指定位置写入应有命令或数据
入口参数：Index 要寻址的寄存器地址
          ConfigTemp 写入的数据或命令值
******************************************/
void LCD_WR_REG(u16 Index,u16 CongfigTemp)
{
	*(__IO u16 *) (Bank1_LCD_C) = Index;	
	*(__IO u16 *) (Bank1_LCD_D) = CongfigTemp;
}


/**
  * 函数功能: 在LCD显示器上开辟一个窗口
  * 输入参数: usX ：在特定扫描方向下窗口的起点X坐标
  *           usY ：在特定扫描方向下窗口的起点Y坐标
  *           usWidth ：窗口的宽度
  *           usHeight ：窗口的高度
  * 返 回 值: 无
  * 说    明：无
  */
void LCD_OpenWindow(uint16_t usX, uint16_t usY, uint16_t usWidth, uint16_t usHeight)
{	
	WriteComm(0x2A ); 				       /* 设置X坐标 */
	WriteData(usX>>8);	             /* 设置起始点：先高8位 */
	WriteData(usX&0xff);	           /* 然后低8位 */
	WriteData((usX+usWidth-1)>>8);  /* 设置结束点：先高8位 */
	WriteData((usX+usWidth-1)&0xff);/* 然后低8位 */

	WriteComm(0x2B); 			           /* 设置Y坐标*/
	WriteData(usY>>8);              /* 设置起始点：先高8位 */
	WriteData(usY&0xff);            /* 然后低8位 */
	WriteData((usY+usHeight-1)>>8); /* 设置结束点：先高8位 */
	WriteData((usY+usHeight-1)&0xff);/* 然后低8位 */
}

/**********************************************
函数名：Lcd块选函数
功能：选定Lcd上指定的矩形区域

注意：xStart、yStart、Xend、Yend随着屏幕的旋转而改变，位置是矩形框的四个角

入口参数：xStart x方向的起始点
          ySrart y方向的起始点
          Xend   x方向的终止点
          Yend   y方向的终止点
返回值：无
***********************************************/
void BlockWrite(unsigned int Xstart,unsigned int Xend,unsigned int Ystart,unsigned int Yend) 
{
	//HX8352-C

	WriteComm(0x2a);   
	WriteData(Xstart>>8);
	WriteData(Xstart&0xff);
	WriteData(Xend>>8);
	WriteData(Xend&0xff);

	WriteComm(0x2b);   
	WriteData(Ystart>>8);
	WriteData(Ystart&0xff);
	WriteData(Yend>>8);
	WriteData(Yend&0xff);


	WriteComm(0x2c);
}
/**********************************************
函数名：矩形填充函数，可用于清屏
功能：选定Lcd上指定的矩形区域

注意：xStart和 yStart随着屏幕的旋转而改变，位置是矩形框的四个角

入口参数：xStart x方向的起始点
          ySrart y方向的终止点
          xLong 要选定矩形的x方向长度
          yLong  要选定矩形的y方向长度
					Color  填充的颜色
返回值：无
***********************************************/
void Lcd_ColorBox(u16 xStart,u16 yStart,u16 xLong,u16 yLong,u32 Color)
{
	u32 temp;

	BlockWrite(xStart,xStart+xLong-1,yStart,yStart+yLong-1);
	for (temp=0; temp<xLong*yLong; temp++)
	{
		*(__IO u16 *) (Bank1_LCD_D) = Color;
		
	}
}

/******************************************
函数名：Lcd图像填充100*100
功能：向Lcd指定位置填充图像
入口参数：Index 要寻址的寄存器地址
          ConfigTemp 写入的数据或命令值
******************************************/
void LCD_Fill_Pic(u16 x, u16 y,u16 pic_H, u16 pic_V, const unsigned char* pic)
{
  unsigned long i;
	unsigned int j;

// 	WriteComm(0x36); //Set_address_mode
// 	WriteData(0x0a); //横屏，从左下角开始，从左到右，从下到上
	BlockWrite(x,x+pic_H-1,y,y+pic_V-1);
	for (i = 0; i < pic_H*pic_V*2; i+=2)
	{
		j=pic[i];
		j=j<<8;
		j=j+pic[i+1];
		*(__IO u16 *) (Bank1_LCD_D) = j;
	}
// 	WriteComm(0x36); //Set_address_mode
// 	WriteData(0xaa);
}

//快速画点
//x,y:坐标
//color:颜色
void LCD_DrawFRONT_COLOR(uint16_t x,uint16_t y,uint16_t color)
{	   
	Lcd_ColorBox(x,y,1,1,color);
} 


/**
  * 函数功能: 从SD卡读取GBK码
  * 输入参数: pBuffer：数据保存地址
  *           gbk ：汉字字符低字节码
  *           font：字体选择
  *           可选值：USE_FONT_16 ：16号字体
  *                   USE_FONT_24 ：24号字体 
  * 返 回 值: uint8_t: 0:读取失败，1：读取成功
  * 说    明：使用该函数之前确保已运行了f_mount(&fs,"0:",1);程序。
  */
static uint8_t GetGBKCode_SD(unsigned char* pBuffer,const uint8_t *pstr,uint8_t font)
{
  uint32_t pos;
  uint8_t high8bit,low8bit;
  FRESULT f_res;
  UINT f_num;
  
  high8bit=*pstr;
  low8bit=*(pstr+1);
  if(font==16)
  {
    // 16*16大小的汉字 其字模 占用16*16/8个字节
    pos=((high8bit-0xa1)*94+low8bit-0xa1)*16*16/8;
    f_res=f_open(&file,"16.FON",FA_OPEN_EXISTING|FA_READ);
  }
  else if(font == 24)
  {
    // 24*24大小的汉字 其字模 占用24*24/8个字节
    pos=((high8bit-0xa1)*94+low8bit-0xa1)*24*24/8; 
    f_res=f_open(&file,"24.FON",FA_OPEN_EXISTING|FA_READ);
		
  }else if(font == 32){
		pos=((high8bit-0xa1)*94+low8bit-0xa1)*32*32/8; 
    f_res=f_open(&file,"32.FON",FA_OPEN_EXISTING|FA_READ);
	} else {
		pos=((high8bit-0xa1)*94+low8bit-0xa1)*64*64/8; 
    f_res=f_open(&file,"64.FON",FA_OPEN_EXISTING|FA_READ);
		
	}
	
  if(f_res == FR_OK ) 
  {
    f_lseek (&file, pos);		//指针偏移
    if(font==16)
    {
      f_res=f_read(&file,pBuffer,32,&f_num); 
    }
    else if(font ==24)
    {
      f_res=f_read(&file,pBuffer,72,&f_num);
    }
		else if (font ==32){
			f_res=f_read(&file,pBuffer,128,&f_num);
		}
		else{
			f_res=f_read(&file,pBuffer,512,&f_num);
		}
		
    f_close(&file);      
    return 1;  
  }    
  else
    return 0;    
}

/**
  * 函数功能: 在 LCD 显示器上显示一个英文字符
  * 输入参数: usX：在特定扫描方向下字符的起始X坐标
  *           usY ：在特定扫描方向下该点的起始Y坐标
  *           cChar ：要显示的英文字符
  *           usColor_Background ：选择英文字符的背景色
  *           usColor_Foreground ：选择英文字符的前景色
  *           font：字体选择
  *             参数：USE_FONT_16 ：16号字体
  *                   USE_FONT_24 ：24号字体 
  * 返 回 值: 无
  * 说    明：该函数必须与ascii.h内容对应使用
  */
void LCD_DispChar_EN( uint16_t x, uint16_t y, char num, uint16_t usColor_Background, uint16_t usColor_Foreground,uint8_t size)
{
	   u16 temp,t1,t;
	u16 y0=y;
	u16 csize=(size/8+((size%8)?1:0))*(size/2);		//得到字体一个字符对应点阵集所占的字节数	
 	num=num-' ';//得到偏移后的值（ASCII字库是从空格开始取模，所以-' '就是对应字符的字库）
	for(t=0;t<csize;t++)
	{   
		if(size==16)temp=asc2_1608[num][t];	//调用1608字体
		else if(size==24)temp=asc2_2412[num][t];	//调用2412字体
		else if(size == 32) temp = asc2_3216[num][t];//调用3216字体
		else if(size == 64) temp = asc2_6432[num][t];
		else return;								//没有的字库
		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)LCD_DrawFRONT_COLOR(x,y,usColor_Foreground);
			else if(1)LCD_DrawFRONT_COLOR(x,y,usColor_Background);
			temp<<=1;
			y++;
			if(y>=480)return;		//超区域了
			if((y-y0)==size)
			{
				y=y0;
				x++;
				if(x>=854)return;	//超区域了
				break;
			}
		}  	 
	}  
}


/**
  * 函数功能: 在 LCD 显示器上显示一个中文
  * 输入参数: usX：在特定扫描方向下字符的起始X坐标
  *           usY ：在特定扫描方向下该点的起始Y坐标
  *           pstr: 汉字字符低字节码
  *           usColor_Background ：选择英文字符的背景色
  *           usColor_Foreground ：选择英文字符的前景色
  *           font：字体选择
  *           可选值：USE_FONT_16 ：16号字体
  *                   USE_FONT_24 ：24号字体 
  * 返 回 值: 无
  * 说    明：无
  */
void LCD_DispCHAR_CH(uint16_t usX,uint16_t usY,const uint8_t *pstr,uint16_t usColor_Background, uint16_t usColor_Foreground,uint8_t font)
{
	uint16_t ucTemp, ucPage, ucColumn;
  uint8_t gbk_buffer[512];
  uint16_t x0 = usX;
	LCD_OpenWindow(usX,usY,font,font);
	WriteComm(0x2C);
	
	GetGBKCode_SD(gbk_buffer,pstr,font);
	
	for(ucPage=0;ucPage<font*font/8;ucPage++)
	{
		ucTemp=gbk_buffer[ucPage];		
		for(ucColumn=0;ucColumn<8;ucColumn++)
		{
			if(ucTemp&0x01){
				//WriteData(usColor_Foreground);	
				LCD_DrawFRONT_COLOR(usX,usY,usColor_Foreground);				
			}
			else{
				LCD_DrawFRONT_COLOR(usX,usY,usColor_Background);
			}					
			ucTemp >>= 1;				
			usX++;
			if(usX>=854)return;		//超区域了
			if((usX-x0)==font)
			{
				usX=x0;
				usY++;
				if(usY>=480)return;	//超区域了
				break;
			}
		}
	}    

}


/**
  * 函数功能: 在 LCD 显示器上显示一串中文
  * 输入参数: usX：在特定扫描方向下字符的起始X坐标
  *           usY ：在特定扫描方向下该点的起始Y坐标
  *           pstr: 汉字字符低字节码
  *           usColor_Background ：选择英文字符的背景色
  *           usColor_Foreground ：选择英文字符的前景色
  *           font：字体选择
  *           可选值：USE_FONT_16 ：16号字体
  *                   USE_FONT_24 ：24号字体 
  * 返 回 值: 无
  * 说    明：无
  */
void LCD_DispString_CH(uint16_t usX,uint16_t usY,const uint8_t *pstr,uint16_t usColor_Background, uint16_t usColor_Foreground,uint8_t font)
{

  while(*pstr != '\0')
	{
		if((usX+font)>854)
		{
			usX = 0;
			usY += font;
		}      
		if((usY+font) > 480)
		{
			usX=0;
			usY=0;
		}      
		LCD_DispCHAR_CH(usX,usY,pstr,usColor_Background,usColor_Foreground,font);
		pstr+=2;      
		usX+=font;
	}  
}

/**
  * 函数功能: 在 LCD 显示器上显示一串中英文
  * 输入参数: usX：在特定扫描方向下字符的起始X坐标
  *           usY ：在特定扫描方向下该点的起始Y坐标
  *           pstr: 汉字字符低字节码
  *           usColor_Background ：选择英文字符的背景色
  *           usColor_Foreground ：选择英文字符的前景色
  *           font：字体选择
  *           可选值：USE_FONT_16 ：16号字体
  *                   USE_FONT_24 ：24号字体 
  * 返 回 值: 无
  * 说    明：无
  */
void LCD_DispString_EN_CH(uint16_t usX,uint16_t usY,const uint8_t *pstr,uint16_t usColor_Background, uint16_t usColor_Foreground,uint8_t font)
{

  while(*pstr != '\0')
	{
    if(*pstr<=0x7f)
    {
			
			if((usX+(font/2))>854)
			{
				usX = 0;
				usY += font;
			}      
			if((usY+font)>480)
			{
				usX=0;
				usY=0;
			}      
			LCD_DispChar_EN(usX,usY,*pstr,usColor_Background,usColor_Foreground,font);
			pstr++;      
			usX+=(font/2);
    }else{
			if((usX+font)>854)
        {
          usX = 0;
          usY += font;
        }      
        if((usY+font)>480)
        {
          usX=0;
          usY=0;
        }      
        LCD_DispCHAR_CH(usX,usY,pstr,usColor_Background,usColor_Foreground,font);
        pstr+=2;      
        usX+=font;
		}
	}  
}
