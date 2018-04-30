#include "parseData.h"
#include "string.h"
#include <stdlib.h>
#include "usart.h"
#include "lcd.h"

_PatientData _patient_data_temp;
_PatientData _patient_data;


static void dataProcessing() {

	if (strcmp(_patient_data.Number, _patient_data_temp.Number) != 0)
	{
		int len = strlen(_patient_data_temp.Number);
		memcpy(_patient_data.Number, _patient_data_temp.Number, NUMBER_LENGTH);
		Lcd_ColorBox(0, 0, 320, 120, Red);//刷一遍底色，把上一次显示的字刷掉
		switch (len)
		{
		case 1:LCD_DispString_EN_CH(128, 0, _patient_data.Number, Red, White, 128);
			break;
		case 2:LCD_DispString_EN_CH(96, 0, _patient_data.Number, Red, White, 128);
			break;
		case 3:LCD_DispString_EN_CH(64, 0, _patient_data.Number, Red, White, 128);
			break;
		case 4:LCD_DispString_EN_CH(32, 0, _patient_data.Number, Red, White, 128);
			break;
		default:
			break;
		}
		
		Lcd_ColorBox(0, 120, 426, 8, BABY_BLUE);//字体太大超出了底边，加上这个矩形盖住
	}

	if (strcmp(_patient_data.Name, _patient_data_temp.Name) != 0)
	{
		int len = strlen(_patient_data_temp.Name);
		memcpy(_patient_data.Name, _patient_data_temp.Name, NAME_LENGTH);
		Lcd_ColorBox(320, 0, 534 , 70, DEEP_SKY_BLUE);//刷一遍底色，把上一次显示的字刷掉
		switch (len)
		{
		case 2:LCD_DispString_EN_CH(546, 0, _patient_data.Name, DEEP_SKY_BLUE, White, 64);
			break;
		case 4:LCD_DispString_EN_CH(514, 0, _patient_data.Name, DEEP_SKY_BLUE, White, 64);
			break;
		case 6:LCD_DispString_EN_CH(482, 0, _patient_data.Name, DEEP_SKY_BLUE, White, 64);
			break;
		case 8:LCD_DispString_EN_CH(450, 0, _patient_data.Name, DEEP_SKY_BLUE, White, 64);
			break;
		default:
			break;
		}
	}

	if (strcmp(_patient_data.Gender, _patient_data_temp.Gender) != 0)
	{
		int len = strlen(_patient_data_temp.Gender);
		memcpy(_patient_data.Gender, _patient_data_temp.Gender, GENDER_LENGTH);
		Lcd_ColorBox(320, 70, 107, 50, MARINE_BLUE);//刷一遍底色，把上一次显示的字刷掉
		if (len == 2)
		{
			LCD_DispString_EN_CH(357, 79, _patient_data.Gender, MARINE_BLUE, White, 32);
		}
	}

	if (strcmp(_patient_data.Age, _patient_data_temp.Age) != 0)
	{
		int len = strlen(_patient_data_temp.Age);
		memcpy(_patient_data.Age, _patient_data_temp.Age, NAME_LENGTH);
		Lcd_ColorBox(427, 70, 142, 50, DEEP_SKY_BLUE);//刷一遍底色，把上一次显示的字刷掉
		switch (len)
		{
		case 1:LCD_DispString_EN_CH(498, 79, _patient_data.Age, DEEP_SKY_BLUE, White, 32);
			break;
		case 2:LCD_DispString_EN_CH(482, 79, _patient_data.Age, DEEP_SKY_BLUE, White, 32);
			break;
		case 3:LCD_DispString_EN_CH(466, 79, _patient_data.Age, DEEP_SKY_BLUE, White, 32);
			break;
		default:
			break;
		}
	}

	if (strcmp(_patient_data.NurseLevel, _patient_data_temp.NurseLevel) != 0)
	{
		int len = strlen(_patient_data_temp.NurseLevel);
		memcpy(_patient_data.NurseLevel, _patient_data_temp.NurseLevel, NURSE_LEVEL_LENGTH);
		Lcd_ColorBox(569, 70, 285, 50, BRIGHT_GREEN);//刷一遍底色，把上一次显示的字刷掉
		LCD_DispString_EN_CH(647, 79, _patient_data.NurseLevel, BRIGHT_GREEN, White, 32);
	}

	/********下面是表格部分*******/

	if (strcmp(_patient_data.HospNum, _patient_data_temp.HospNum) != 0)//住院号
	{
		int len = strlen(_patient_data_temp.HospNum);
		memcpy(_patient_data.HospNum, _patient_data_temp.HospNum, HOSP_NUM_LENGTH);
		Lcd_ColorBox(138, 134, 288, 32, BABY_BLUE);//刷一遍底色，把上一次显示的字刷掉
		LCD_DispString_EN_CH(138, 134, _patient_data.HospNum, BABY_BLUE, Black, 32);
	}

	if (strcmp(_patient_data.HospTime, _patient_data_temp.HospTime) != 0)//住院时间
	{
		int len = strlen(_patient_data_temp.HospTime);
		memcpy(_patient_data.HospTime, _patient_data_temp.HospTime, HOSP_TIME_LENGTH);
		Lcd_ColorBox(170, 194, 256, 32, BABY_BLUE);//刷一遍底色，把上一次显示的字刷掉
		LCD_DispString_EN_CH(170, 194, _patient_data.HospTime, BABY_BLUE, Black, 32);
	}

	if (strcmp(_patient_data.ChargeDoctor, _patient_data_temp.ChargeDoctor) != 0)//责任医生
	{
		int len = strlen(_patient_data_temp.ChargeDoctor);
		memcpy(_patient_data.ChargeDoctor, _patient_data_temp.ChargeDoctor, CHARGE_DOCTOR_LENGTH);
		Lcd_ColorBox(170, 254, 256, 32, BABY_BLUE);//刷一遍底色，把上一次显示的字刷掉
		LCD_DispString_EN_CH(170, 254, _patient_data.ChargeDoctor, BABY_BLUE, Black, 32);
	}

	if (strcmp(_patient_data.ChargeNurse, _patient_data_temp.ChargeNurse) != 0)//责任护士
	{
		int len = strlen(_patient_data_temp.ChargeNurse);
		memcpy(_patient_data.ChargeNurse, _patient_data_temp.ChargeNurse, CHARGE_NURSE_LENGTH);
		Lcd_ColorBox(170, 314, 256, 32, BABY_BLUE);//刷一遍底色，把上一次显示的字刷掉
		LCD_DispString_EN_CH(170, 314, _patient_data.ChargeNurse, BABY_BLUE, Black, 32);
	}

	if (strcmp(_patient_data.Diagnosis, _patient_data_temp.Diagnosis) != 0)
	{
		int len = strlen(_patient_data_temp.Diagnosis);
		memcpy(_patient_data.Diagnosis, _patient_data_temp.Diagnosis, DIAGNOSIS_LENGTH);
		Lcd_ColorBox(106, 374, 320, 32, BABY_BLUE);//刷一遍底色，把上一次显示的字刷掉
		LCD_DispString_EN_CH(106, 374, _patient_data.Diagnosis, BABY_BLUE, Black, 32);
	}

	if (strcmp(_patient_data.Others, _patient_data_temp.Others) != 0)
	{
		int len = strlen(_patient_data_temp.Others);
		memcpy(_patient_data.Others, _patient_data_temp.Others, OTHERS_LENGTH);
		Lcd_ColorBox(106, 434, 320, 32, BABY_BLUE);//刷一遍底色，把上一次显示的字刷掉
		LCD_DispString_EN_CH(106, 434, _patient_data.Others, BABY_BLUE, Red, 32);
	}

	if (strcmp(_patient_data.Medicare, _patient_data_temp.Medicare) != 0)
	{
		int len = strlen(_patient_data_temp.Medicare);
		memcpy(_patient_data.Medicare, _patient_data_temp.Medicare, MEDICARE_LENGTH);
		Lcd_ColorBox(543, 134, 320, 32, BABY_BLUE);//刷一遍底色，把上一次显示的字刷掉
		LCD_DispString_EN_CH(543, 134, _patient_data.Medicare, BABY_BLUE, Black, 32);
	}

	if (strcmp(_patient_data.Diet, _patient_data_temp.Diet) != 0)
	{
		int len = strlen(_patient_data_temp.Diet);
		memcpy(_patient_data.Diet, _patient_data_temp.Diet, DIET_LENGTH);
		Lcd_ColorBox(543, 194, 320, 32, BABY_BLUE);//刷一遍底色，把上一次显示的字刷掉
		LCD_DispString_EN_CH(543, 194, _patient_data.Diet, BABY_BLUE, Black, 32);
	}

	if (strcmp(_patient_data.Isolation, _patient_data_temp.Isolation) != 0)
	{
		int len = strlen(_patient_data_temp.Isolation);
		memcpy(_patient_data.Isolation, _patient_data_temp.Isolation, ISOLATION_LENGTH);
		Lcd_ColorBox(543, 254, 320, 32, BABY_BLUE);//刷一遍底色，把上一次显示的字刷掉
		LCD_DispString_EN_CH(543, 254, _patient_data.Isolation, BABY_BLUE, Black, 32);
	}

	if (strcmp(_patient_data.Account, _patient_data_temp.Account) != 0)
	{
		int len = strlen(_patient_data_temp.Account);
		memcpy(_patient_data.Account, _patient_data_temp.Account, ACCOUNT_LENGTH);
		Lcd_ColorBox(543, 314, 320, 32, BABY_BLUE);//刷一遍底色，把上一次显示的字刷掉
		LCD_DispString_EN_CH(543, 314, _patient_data.Account, BABY_BLUE, Black, 32);
	}
}

void parseData()
{	
	char *subString;
	char *subStringNext;
	char i = 0;
	if (GetDataFlag)
	{
		GetDataFlag = 0;

		for (i = 0 ; i <= 15 ; i++)
		{
			if (i == 0)
			{
				if ((subString = strstr(Patient_Buffer, ",")) == NULL){
					printf("parse error");
					return;
				}
					
			}
			else
			{
				subString++;
				if ((subStringNext = strstr(subString, ",")) != NULL)
				{
					switch(i)
					{
						case 1:
							if (subStringNext - subString <= NUMBER_LENGTH) {
								memset(_patient_data_temp.Number, 0, NUMBER_LENGTH);
								memcpy(_patient_data_temp.Number, subString, subStringNext - subString);
							}
							break;
						case 2:
							if (subStringNext - subString <= NAME_LENGTH) {
								memset(_patient_data_temp.Name, 0, NAME_LENGTH);
								memcpy(_patient_data_temp.Name, subString, subStringNext - subString);
							}
							break;
						case 3:
							if (subStringNext - subString <= GENDER_LENGTH) {
								memset(_patient_data_temp.Gender, 0, GENDER_LENGTH);
								memcpy(_patient_data_temp.Gender, subString, subStringNext - subString);
							}
							break;
						case 4:
							if (subStringNext - subString <= AGE_LENGTH) {
								memset(_patient_data_temp.Age, 0, AGE_LENGTH);
								memcpy(_patient_data_temp.Age, subString, subStringNext - subString);
							}
							break;
						case 5:
							if (subStringNext - subString <= NURSE_LEVEL_LENGTH) {
								memset(_patient_data_temp.NurseLevel, 0, NURSE_LEVEL_LENGTH);
								memcpy(_patient_data_temp.NurseLevel, subString, subStringNext - subString);
							}
							break;
						case 6:
							if (subStringNext - subString <= HOSP_NUM_LENGTH) {
								memset(_patient_data_temp.HospNum, 0, HOSP_NUM_LENGTH);
								memcpy(_patient_data_temp.HospNum, subString, subStringNext - subString);
							}
							break;
						case 7:
							if (subStringNext - subString <= HOSP_TIME_LENGTH) {
								memset(_patient_data_temp.HospTime, 0, HOSP_TIME_LENGTH);
								memcpy(_patient_data_temp.HospTime, subString, subStringNext - subString);
							}
							break;
						case 8:
							if (subStringNext - subString <= CHARGE_DOCTOR_LENGTH) {
								memset(_patient_data_temp.ChargeDoctor, 0, CHARGE_DOCTOR_LENGTH);
								memcpy(_patient_data_temp.ChargeDoctor, subString, subStringNext - subString);
							}
							 break;
						case 9:
							if (subStringNext - subString <= CHARGE_NURSE_LENGTH) {
								memset(_patient_data_temp.ChargeNurse, 0, CHARGE_NURSE_LENGTH);
								memcpy(_patient_data_temp.ChargeNurse, subString, subStringNext - subString);
							}
							break;
						case 10:
							if (subStringNext - subString <= DIAGNOSIS_LENGTH) {
								memset(_patient_data_temp.Diagnosis, 0, DIAGNOSIS_LENGTH);
								memcpy(_patient_data_temp.Diagnosis, subString, subStringNext - subString);
							}
							break;
						case 11:
							if (subStringNext - subString <= OTHERS_LENGTH) {
								memset(_patient_data_temp.Others, 0, OTHERS_LENGTH);
								memcpy(_patient_data_temp.Others, subString, subStringNext - subString);
							}
							break;
						case 12:
							if (subStringNext - subString <= MEDICARE_LENGTH) {
								memset(_patient_data_temp.Medicare, 0, MEDICARE_LENGTH);
								memcpy(_patient_data_temp.Medicare, subString, subStringNext - subString);
							}
							break;
						case 13:
							if (subStringNext - subString <= DIET_LENGTH) {
								memset(_patient_data_temp.Diet, 0, DIET_LENGTH);
								memcpy(_patient_data_temp.Diet, subString, subStringNext - subString);
							}
							break;
						case 14:
							if (subStringNext - subString <= ISOLATION_LENGTH) {
								memset(_patient_data_temp.Isolation, 0, ISOLATION_LENGTH);
								memcpy(_patient_data_temp.Isolation, subString, subStringNext - subString);
							}
							break;
						case 15:
							if (subStringNext - subString <= ACCOUNT_LENGTH) {
								memset(_patient_data_temp.Account, 0, ACCOUNT_LENGTH);
								memcpy(_patient_data_temp.Account, subString, subStringNext - subString);
							}
							break;
						default:break;
					}

					subString = subStringNext;

				}

			}

		}


		dataProcessing();

	}
}

