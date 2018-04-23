/**
  ******************************************************************************
  * @file   fatfs.c
  * @brief  Code for fatfs applications
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

#include "fatfs.h"


//uint8_t retSD;    /* Return value for SD */
//char SDPath[4];   /* SD logical drive path */
//FATFS SDFatFS;    /* File system object for SD logical drive */
//FIL file;       /* File object for SD */
//uint8_t retUSER;    /* Return value for USER */
//char USERPath[4];   /* USER logical drive path */
//FATFS USERFatFS;    /* File system object for USER logical drive */
//FIL USERFile;       /* File object for USER */


/* USER CODE BEGIN Variables */

char SPIFLASHPath[4];             /* ����Flash�߼��豸·�� */
char SDPath[4];                   /* SD���߼��豸·�� */

FATFS fs;													/* FatFs�ļ�ϵͳ���� */
FIL file_sd;													/* �ļ����� */
FIL file_flash;													/* �ļ����� */
FRESULT f_res;                    /* �ļ�������� */
UINT fnum;            					  /* �ļ��ɹ���д���� */
BYTE ReadBuffer[1024] = { 0 };        /* �������� */
BYTE WriteBuffer[] = "��ӭʹ��ӲʯSTM32������ �����Ǹ������ӣ��½��ļ�ϵͳ�����ļ�\n";/* д������*/



/* USER CODE END Variables */    

void MX_FATFS_Init(void) 
{
  /*## FatFS: Link the SD driver ###########################*/
  //retSD = FATFS_LinkDriver(&SD_Driver, SDPath);
  /*## FatFS: Link the USER driver ###########################*/
 

  /* USER CODE BEGIN Init */

	BYTE buffer[4096] = {0};
	UINT br, bw;
	//printf("****** ����һ�����ڴ���FLASH��FatFS�ļ�ϵͳʵ�� ******\n");


	/* ע��һ��FatFS�豸������FLASH */
	if (FATFS_LinkDriver(&SPIFLASH_Driver, SPIFLASHPath) == 0)
	{
		printf("��ǰ�豸������ %d  \n", FATFS_GetAttachedDriversNbr());
		printf("��ǰ�豸·���� %s \n", SPIFLASHPath);
		//�ڴ���FLASH�����ļ�ϵͳ���ļ�ϵͳ����ʱ��Դ���FLASH��ʼ��
		f_res = f_mount(&fs, (TCHAR const*)SPIFLASHPath, 1);
		printf_fatfs_error(f_res);
		/*----------------------- ��ʽ������ ---------------------------*/
		/* ���û���ļ�ϵͳ�͸�ʽ�����������ļ�ϵͳ */
		if (f_res == FR_NO_FILESYSTEM)
		{
			printf("������FLASH��û���ļ�ϵͳ���������и�ʽ��...\n");
			/* ��ʽ�� */
			f_res = f_mkfs((TCHAR const*)SPIFLASHPath, 0, 0);

			if (f_res == FR_OK)
			{
				printf("������FLASH�ѳɹ���ʽ���ļ�ϵͳ��\n");
				/* ��ʽ������ȡ������ */
				f_res = f_mount(NULL, (TCHAR const*)SPIFLASHPath, 1);
				/* ���¹���	*/
				f_res = f_mount(&fs, (TCHAR const*)SPIFLASHPath, 1);
			}
			else
			{
				printf("������ʽ��ʧ�ܡ�����\n");
				while (1);
			}
		}
		else if (f_res != FR_OK)
		{
			printf("��������FLASH�����ļ�ϵͳʧ�ܡ�(%d)\n", f_res);
			printf_fatfs_error(f_res);
			//while (1);
		}
		else
		{
			printf("��flash�ļ�ϵͳ���سɹ������Խ��ж�д����\n");
			
		}
	}

	/* ע��һ��FatFS�豸������FLASH */
	//FATFS_UnLinkDriver(SPIFLASHPath);

	/**************************************************************************/
	/* ע��һ��FatFS�豸��SD�� */
	if (FATFS_LinkDriver(&SD_Driver, SDPath) == 0)
	{
		printf("��ǰ�豸������ %d  \n", FATFS_GetAttachedDriversNbr());
		printf("��ǰ�豸·���� %s", SDPath);
		//��SD�������ļ�ϵͳ���ļ�ϵͳ����ʱ���SD����ʼ��
		f_res = f_mount(&fs, (TCHAR const*)SDPath, 1);
		printf_fatfs_error(f_res);
		/*----------------------- ��ʽ������ ---------------------------*/
		/* ���û���ļ�ϵͳ�͸�ʽ�����������ļ�ϵͳ */
		if (f_res == FR_NO_FILESYSTEM)
		{
			printf("��SD����û���ļ�ϵͳ���������и�ʽ��...\n");
			/* ��ʽ�� */
			f_res = f_mkfs((TCHAR const*)SDPath, 0, 0);

			if (f_res == FR_OK)
			{
				printf("��SD���ѳɹ���ʽ���ļ�ϵͳ��\n");
				/* ��ʽ������ȡ������ */
				f_res = f_mount(NULL, (TCHAR const*)SDPath, 1);
				/* ���¹���	*/
				f_res = f_mount(&fs, (TCHAR const*)SDPath, 1);
			}
			else
			{
				printf("������ʽ��ʧ�ܡ�����\n");
				while (1);
			}
		}
		else if (f_res != FR_OK)
		{
			printf("����SD�������ļ�ϵͳʧ�ܡ�(%d)\n", f_res);
			printf_fatfs_error(f_res);
			//while (1);
		}
		else
		{
			printf("��sd�ļ�ϵͳ���سɹ������Խ��ж�д����\n");

			if (f_res == FR_OK)
			{
				f_chdrive("0:");
				f_res = f_open(&file_sd, "24.FON", FA_OPEN_EXISTING | FA_READ);
				printf_fatfs_error(f_res);
				if (f_res == FR_OK)
				{
					f_chdrive("1:");
					f_res = f_open(&file_flash, "f24.FON", FA_CREATE_ALWAYS | FA_WRITE);
					printf_fatfs_error(f_res);
				}

				while (f_res == 0)
				{
					f_res = f_read(&file_sd, buffer, sizeof(buffer), &br);
					HAL_Delay(1);
					printf("f_res = %d,br= %d   ", f_res, br);
					if (f_res || br == 0) break; /* �ļ��������� */
					f_res = f_write(&file_flash, buffer, br, &bw);
					HAL_Delay(1);
					printf("f_res = %d,br= %d,bw=%d  \n", f_res, br, bw);
					if (f_res || bw < br) break; /* ���������� */
				}
			}
			f_close(&file_sd);
			f_close(&file_flash);
		}
	}


	/* ע��һ��FatFS�豸��SD�� */
	//FATFS_UnLinkDriver(SDPath);


  /* USER CODE END Init */
}

/**
  * @brief  Gets Time from RTC 
  * @param  None
  * @retval Time in DWORD
  */
DWORD get_fattime(void)
{
  /* USER CODE BEGIN get_fattime */
  return 0;
  /* USER CODE END get_fattime */  
}

/* USER CODE BEGIN Application */
     
/**
* ��������: FatFS�ļ�ϵͳ���������Ϣ����.
* �������: FatFS�ļ�ϵͳ���������FRESULT
* �� �� ֵ: ��
* ˵    ��: ��
*/
void printf_fatfs_error(FRESULT fresult)
{
	switch (fresult)
	{
	case FR_OK:                   //(0)
		printf("�������ɹ���\n");
		break;
	case FR_DISK_ERR:             //(1)
		printf("����Ӳ�����������������\n");
		break;
	case FR_INT_ERR:              //(2)
		printf("�������Դ���\n");
		break;
	case FR_NOT_READY:            //(3)
		printf("���������豸�޷�������\n");
		break;
	case FR_NO_FILE:              //(4)
		printf("�����޷��ҵ��ļ���\n");
		break;
	case FR_NO_PATH:              //(5)
		printf("�����޷��ҵ�·����\n");
		break;
	case FR_INVALID_NAME:         //(6)
		printf("������Ч��·������\n");
		break;
	case FR_DENIED:               //(7)
	case FR_EXIST:                //(8)
		printf("�����ܾ����ʡ�\n");
		break;
	case FR_INVALID_OBJECT:       //(9)
		printf("������Ч���ļ���·����\n");
		break;
	case FR_WRITE_PROTECTED:      //(10)
		printf("�����߼��豸д������\n");
		break;
	case FR_INVALID_DRIVE:        //(11)
		printf("������Ч���߼��豸��\n");
		break;
	case FR_NOT_ENABLED:          //(12)
		printf("������Ч�Ĺ�������\n");
		break;
	case FR_NO_FILESYSTEM:        //(13)
		printf("������Ч���ļ�ϵͳ��\n");
		break;
	case FR_MKFS_ABORTED:         //(14)
		printf("���������������⵼��f_mkfs��������ʧ�ܡ�\n");
		break;
	case FR_TIMEOUT:              //(15)
		printf("����������ʱ��\n");
		break;
	case FR_LOCKED:               //(16)
		printf("�����ļ���������\n");
		break;
	case FR_NOT_ENOUGH_CORE:      //(17)
		printf("�������ļ���֧�ֻ�ȡ�ѿռ�ʧ�ܡ�\n");
		break;
	case FR_TOO_MANY_OPEN_FILES:  //(18)
		printf("������̫���ļ���\n");
		break;
	case FR_INVALID_PARAMETER:    // (19)
		printf("����������Ч��\n");
		break;
	}
}

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
