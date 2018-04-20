#include "lcd.h"
#include "fatfs.h"
#include "ascii.h"

//LCD�Ļ�����ɫ�ͱ���ɫ	   
uint16_t FRONT_COLOR=Black;	//������ɫ
uint16_t BACK_COLOR=White;  //����ɫ 


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
Lcd��ʼ������
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
��������Lcdд�����
���ܣ���Lcdָ��λ��д��Ӧ�����������
��ڲ�����Index ҪѰַ�ļĴ�����ַ
          ConfigTemp д������ݻ�����ֵ
******************************************/
void LCD_WR_REG(u16 Index,u16 CongfigTemp)
{
	*(__IO u16 *) (Bank1_LCD_C) = Index;	
	*(__IO u16 *) (Bank1_LCD_D) = CongfigTemp;
}


/**
  * ��������: ��LCD��ʾ���Ͽ���һ������
  * �������: usX �����ض�ɨ�跽���´��ڵ����X����
  *           usY �����ض�ɨ�跽���´��ڵ����Y����
  *           usWidth �����ڵĿ��
  *           usHeight �����ڵĸ߶�
  * �� �� ֵ: ��
  * ˵    ������
  */
void LCD_OpenWindow(uint16_t usX, uint16_t usY, uint16_t usWidth, uint16_t usHeight)
{	
	WriteComm(0x2A ); 				       /* ����X���� */
	WriteData(usX>>8);	             /* ������ʼ�㣺�ȸ�8λ */
	WriteData(usX&0xff);	           /* Ȼ���8λ */
	WriteData((usX+usWidth-1)>>8);  /* ���ý����㣺�ȸ�8λ */
	WriteData((usX+usWidth-1)&0xff);/* Ȼ���8λ */

	WriteComm(0x2B); 			           /* ����Y����*/
	WriteData(usY>>8);              /* ������ʼ�㣺�ȸ�8λ */
	WriteData(usY&0xff);            /* Ȼ���8λ */
	WriteData((usY+usHeight-1)>>8); /* ���ý����㣺�ȸ�8λ */
	WriteData((usY+usHeight-1)&0xff);/* Ȼ���8λ */
}

/**********************************************
��������Lcd��ѡ����
���ܣ�ѡ��Lcd��ָ���ľ�������

ע�⣺xStart��yStart��Xend��Yend������Ļ����ת���ı䣬λ���Ǿ��ο���ĸ���

��ڲ�����xStart x�������ʼ��
          ySrart y�������ʼ��
          Xend   x�������ֹ��
          Yend   y�������ֹ��
����ֵ����
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
��������������亯��������������
���ܣ�ѡ��Lcd��ָ���ľ�������

ע�⣺xStart�� yStart������Ļ����ת���ı䣬λ���Ǿ��ο���ĸ���

��ڲ�����xStart x�������ʼ��
          ySrart y�������ֹ��
          xLong Ҫѡ�����ε�x���򳤶�
          yLong  Ҫѡ�����ε�y���򳤶�
					Color  ������ɫ
����ֵ����
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
��������Lcdͼ�����100*100
���ܣ���Lcdָ��λ�����ͼ��
��ڲ�����Index ҪѰַ�ļĴ�����ַ
          ConfigTemp д������ݻ�����ֵ
******************************************/
void LCD_Fill_Pic(u16 x, u16 y,u16 pic_H, u16 pic_V, const unsigned char* pic)
{
  unsigned long i;
	unsigned int j;

// 	WriteComm(0x36); //Set_address_mode
// 	WriteData(0x0a); //�����������½ǿ�ʼ�������ң����µ���
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

//���ٻ���
//x,y:����
//color:��ɫ
void LCD_DrawFRONT_COLOR(uint16_t x,uint16_t y,uint16_t color)
{	   
	Lcd_ColorBox(x,y,1,1,color);
} 


/**
  * ��������: ��SD����ȡGBK��
  * �������: pBuffer�����ݱ����ַ
  *           gbk �������ַ����ֽ���
  *           font������ѡ��
  *           ��ѡֵ��USE_FONT_16 ��16������
  *                   USE_FONT_24 ��24������ 
  * �� �� ֵ: uint8_t: 0:��ȡʧ�ܣ�1����ȡ�ɹ�
  * ˵    ����ʹ�øú���֮ǰȷ����������f_mount(&fs,"0:",1);����
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
    // 16*16��С�ĺ��� ����ģ ռ��16*16/8���ֽ�
    pos=((high8bit-0xa1)*94+low8bit-0xa1)*16*16/8;
    f_res=f_open(&file,"16.FON",FA_OPEN_EXISTING|FA_READ);
  }
  else if(font == 24)
  {
    // 24*24��С�ĺ��� ����ģ ռ��24*24/8���ֽ�
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
    f_lseek (&file, pos);		//ָ��ƫ��
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
  * ��������: �� LCD ��ʾ������ʾһ��Ӣ���ַ�
  * �������: usX�����ض�ɨ�跽�����ַ�����ʼX����
  *           usY �����ض�ɨ�跽���¸õ����ʼY����
  *           cChar ��Ҫ��ʾ��Ӣ���ַ�
  *           usColor_Background ��ѡ��Ӣ���ַ��ı���ɫ
  *           usColor_Foreground ��ѡ��Ӣ���ַ���ǰ��ɫ
  *           font������ѡ��
  *             ������USE_FONT_16 ��16������
  *                   USE_FONT_24 ��24������ 
  * �� �� ֵ: ��
  * ˵    �����ú���������ascii.h���ݶ�Ӧʹ��
  */
void LCD_DispChar_EN( uint16_t x, uint16_t y, char num, uint16_t usColor_Background, uint16_t usColor_Foreground,uint8_t size)
{
	   u16 temp,t1,t;
	u16 y0=y;
	u16 csize=(size/8+((size%8)?1:0))*(size/2);		//�õ�����һ���ַ���Ӧ������ռ���ֽ���	
 	num=num-' ';//�õ�ƫ�ƺ��ֵ��ASCII�ֿ��Ǵӿո�ʼȡģ������-' '���Ƕ�Ӧ�ַ����ֿ⣩
	for(t=0;t<csize;t++)
	{   
		if(size==16)temp=asc2_1608[num][t];	//����1608����
		else if(size==24)temp=asc2_2412[num][t];	//����2412����
		else if(size == 32) temp = asc2_3216[num][t];//����3216����
		else if(size == 64) temp = asc2_6432[num][t];
		else return;								//û�е��ֿ�
		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)LCD_DrawFRONT_COLOR(x,y,usColor_Foreground);
			else if(1)LCD_DrawFRONT_COLOR(x,y,usColor_Background);
			temp<<=1;
			y++;
			if(y>=480)return;		//��������
			if((y-y0)==size)
			{
				y=y0;
				x++;
				if(x>=854)return;	//��������
				break;
			}
		}  	 
	}  
}


/**
  * ��������: �� LCD ��ʾ������ʾһ������
  * �������: usX�����ض�ɨ�跽�����ַ�����ʼX����
  *           usY �����ض�ɨ�跽���¸õ����ʼY����
  *           pstr: �����ַ����ֽ���
  *           usColor_Background ��ѡ��Ӣ���ַ��ı���ɫ
  *           usColor_Foreground ��ѡ��Ӣ���ַ���ǰ��ɫ
  *           font������ѡ��
  *           ��ѡֵ��USE_FONT_16 ��16������
  *                   USE_FONT_24 ��24������ 
  * �� �� ֵ: ��
  * ˵    ������
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
			if(usX>=854)return;		//��������
			if((usX-x0)==font)
			{
				usX=x0;
				usY++;
				if(usY>=480)return;	//��������
				break;
			}
		}
	}    

}


/**
  * ��������: �� LCD ��ʾ������ʾһ������
  * �������: usX�����ض�ɨ�跽�����ַ�����ʼX����
  *           usY �����ض�ɨ�跽���¸õ����ʼY����
  *           pstr: �����ַ����ֽ���
  *           usColor_Background ��ѡ��Ӣ���ַ��ı���ɫ
  *           usColor_Foreground ��ѡ��Ӣ���ַ���ǰ��ɫ
  *           font������ѡ��
  *           ��ѡֵ��USE_FONT_16 ��16������
  *                   USE_FONT_24 ��24������ 
  * �� �� ֵ: ��
  * ˵    ������
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
  * ��������: �� LCD ��ʾ������ʾһ����Ӣ��
  * �������: usX�����ض�ɨ�跽�����ַ�����ʼX����
  *           usY �����ض�ɨ�跽���¸õ����ʼY����
  *           pstr: �����ַ����ֽ���
  *           usColor_Background ��ѡ��Ӣ���ַ��ı���ɫ
  *           usColor_Foreground ��ѡ��Ӣ���ַ���ǰ��ɫ
  *           font������ѡ��
  *           ��ѡֵ��USE_FONT_16 ��16������
  *                   USE_FONT_24 ��24������ 
  * �� �� ֵ: ��
  * ˵    ������
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
