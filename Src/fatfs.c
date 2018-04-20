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

char SPIFLASHPath[4];             /* 串行Flash逻辑设备路径 */
char SDPath[4];                   /* SD卡逻辑设备路径 */

FATFS fs;													/* FatFs文件系统对象 */
FIL file_sd;													/* 文件对象 */
FIL file_flash;													/* 文件对象 */
FRESULT f_res;                    /* 文件操作结果 */
UINT fnum;            					  /* 文件成功读写数量 */
BYTE ReadBuffer[1024] = { 0 };        /* 读缓冲区 */
BYTE WriteBuffer[] = "欢迎使用硬石STM32开发板 今天是个好日子，新建文件系统测试文件\n";/* 写缓冲区*/



/* USER CODE END Variables */    

void MX_FATFS_Init(void) 
{
  /*## FatFS: Link the SD driver ###########################*/
  //retSD = FATFS_LinkDriver(&SD_Driver, SDPath);
  /*## FatFS: Link the USER driver ###########################*/
 

  /* USER CODE BEGIN Init */

	BYTE buffer[4096] = {0};
	UINT br, bw;
	//printf("****** 这是一个基于串行FLASH的FatFS文件系统实验 ******\n");


	/* 注册一个FatFS设备：串行FLASH */
	if (FATFS_LinkDriver(&SPIFLASH_Driver, SPIFLASHPath) == 0)
	{
		printf("当前设备数量： %d  \n", FATFS_GetAttachedDriversNbr());
		printf("当前设备路径： %s \n", SPIFLASHPath);
		//在串行FLASH挂载文件系统，文件系统挂载时会对串行FLASH初始化
		f_res = f_mount(&fs, (TCHAR const*)SPIFLASHPath, 1);
		printf_fatfs_error(f_res);
		/*----------------------- 格式化测试 ---------------------------*/
		/* 如果没有文件系统就格式化创建创建文件系统 */
		if (f_res == FR_NO_FILESYSTEM)
		{
			printf("》串行FLASH还没有文件系统，即将进行格式化...\n");
			/* 格式化 */
			f_res = f_mkfs((TCHAR const*)SPIFLASHPath, 0, 0);

			if (f_res == FR_OK)
			{
				printf("》串行FLASH已成功格式化文件系统。\n");
				/* 格式化后，先取消挂载 */
				f_res = f_mount(NULL, (TCHAR const*)SPIFLASHPath, 1);
				/* 重新挂载	*/
				f_res = f_mount(&fs, (TCHAR const*)SPIFLASHPath, 1);
			}
			else
			{
				printf("《《格式化失败。》》\n");
				while (1);
			}
		}
		else if (f_res != FR_OK)
		{
			printf("！！串行FLASH挂载文件系统失败。(%d)\n", f_res);
			printf_fatfs_error(f_res);
			//while (1);
		}
		else
		{
			printf("》flash文件系统挂载成功，可以进行读写测试\n");
			
		}
	}

	/* 注销一个FatFS设备：串行FLASH */
	//FATFS_UnLinkDriver(SPIFLASHPath);

	/**************************************************************************/
	/* 注册一个FatFS设备：SD卡 */
	if (FATFS_LinkDriver(&SD_Driver, SDPath) == 0)
	{
		printf("当前设备数量： %d  \n", FATFS_GetAttachedDriversNbr());
		printf("当前设备路径： %s", SDPath);
		//在SD卡挂载文件系统，文件系统挂载时会对SD卡初始化
		f_res = f_mount(&fs, (TCHAR const*)SDPath, 1);
		printf_fatfs_error(f_res);
		/*----------------------- 格式化测试 ---------------------------*/
		/* 如果没有文件系统就格式化创建创建文件系统 */
		if (f_res == FR_NO_FILESYSTEM)
		{
			printf("》SD卡还没有文件系统，即将进行格式化...\n");
			/* 格式化 */
			f_res = f_mkfs((TCHAR const*)SDPath, 0, 0);

			if (f_res == FR_OK)
			{
				printf("》SD卡已成功格式化文件系统。\n");
				/* 格式化后，先取消挂载 */
				f_res = f_mount(NULL, (TCHAR const*)SDPath, 1);
				/* 重新挂载	*/
				f_res = f_mount(&fs, (TCHAR const*)SDPath, 1);
			}
			else
			{
				printf("《《格式化失败。》》\n");
				while (1);
			}
		}
		else if (f_res != FR_OK)
		{
			printf("！！SD卡挂载文件系统失败。(%d)\n", f_res);
			printf_fatfs_error(f_res);
			//while (1);
		}
		else
		{
			printf("》sd文件系统挂载成功，可以进行读写测试\n");

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
					if (f_res || br == 0) break; /* 文件结束错误 */
					f_res = f_write(&file_flash, buffer, br, &bw);
					HAL_Delay(1);
					printf("f_res = %d,br= %d,bw=%d  \n", f_res, br, bw);
					if (f_res || bw < br) break; /* 磁盘满错误 */
				}
			}
			f_close(&file_sd);
			f_close(&file_flash);
		}
	}


	/* 注销一个FatFS设备：SD卡 */
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
* 函数功能: FatFS文件系统操作结果信息处理.
* 输入参数: FatFS文件系统操作结果：FRESULT
* 返 回 值: 无
* 说    明: 无
*/
void printf_fatfs_error(FRESULT fresult)
{
	switch (fresult)
	{
	case FR_OK:                   //(0)
		printf("》操作成功。\n");
		break;
	case FR_DISK_ERR:             //(1)
		printf("！！硬件输入输出驱动出错。\n");
		break;
	case FR_INT_ERR:              //(2)
		printf("！！断言错误。\n");
		break;
	case FR_NOT_READY:            //(3)
		printf("！！物理设备无法工作。\n");
		break;
	case FR_NO_FILE:              //(4)
		printf("！！无法找到文件。\n");
		break;
	case FR_NO_PATH:              //(5)
		printf("！！无法找到路径。\n");
		break;
	case FR_INVALID_NAME:         //(6)
		printf("！！无效的路径名。\n");
		break;
	case FR_DENIED:               //(7)
	case FR_EXIST:                //(8)
		printf("！！拒绝访问。\n");
		break;
	case FR_INVALID_OBJECT:       //(9)
		printf("！！无效的文件或路径。\n");
		break;
	case FR_WRITE_PROTECTED:      //(10)
		printf("！！逻辑设备写保护。\n");
		break;
	case FR_INVALID_DRIVE:        //(11)
		printf("！！无效的逻辑设备。\n");
		break;
	case FR_NOT_ENABLED:          //(12)
		printf("！！无效的工作区。\n");
		break;
	case FR_NO_FILESYSTEM:        //(13)
		printf("！！无效的文件系统。\n");
		break;
	case FR_MKFS_ABORTED:         //(14)
		printf("！！因函数参数问题导致f_mkfs函数操作失败。\n");
		break;
	case FR_TIMEOUT:              //(15)
		printf("！！操作超时。\n");
		break;
	case FR_LOCKED:               //(16)
		printf("！！文件被保护。\n");
		break;
	case FR_NOT_ENOUGH_CORE:      //(17)
		printf("！！长文件名支持获取堆空间失败。\n");
		break;
	case FR_TOO_MANY_OPEN_FILES:  //(18)
		printf("！！打开太多文件。\n");
		break;
	case FR_INVALID_PARAMETER:    // (19)
		printf("！！参数无效。\n");
		break;
	}
}

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
