#ifndef __PARSEDATA_
#define __PARSEDATA_

#include "stm32f1xx_hal.h"
#include "main.h"

#define NUMBER_LENGTH 5
#define NAME_LENGTH 10
#define GENDER_LENGTH 3
#define AGE_LENGTH 5
#define NURSE_LEVEL_LENGTH 22
#define HOSP_NUM_LENGTH 22
#define HOSP_TIME_LENGTH 22
#define CHARGE_DOCTOR_LENGTH 22
#define CHARGE_NURSE_LENGTH 22
#define DIAGNOSIS_LENGTH 22
#define OTHERS_LENGTH 22
#define MEDICARE_LENGTH 22
#define DIET_LENGTH 22
#define ISOLATION_LENGTH 22
#define ACCOUNT_LENGTH 22



typedef struct 
{
	char Number[NUMBER_LENGTH];					//编号
	char Name[NAME_LENGTH];						//姓名
	char Gender[GENDER_LENGTH];					//性别
	char Age[AGE_LENGTH];						//年龄
	char NurseLevel[NURSE_LEVEL_LENGTH];		//护理等级
	char HospNum[HOSP_NUM_LENGTH];				//住院号
	char HospTime[HOSP_TIME_LENGTH];			//住院时间
	char ChargeDoctor[CHARGE_DOCTOR_LENGTH];	//责任医生
	char ChargeNurse[CHARGE_NURSE_LENGTH];		//责任护士
	char Diagnosis[DIAGNOSIS_LENGTH];			//诊断
	char Others[OTHERS_LENGTH];					//其他
	char Medicare[MEDICARE_LENGTH];				//医保
	char Diet[DIET_LENGTH];						//饮食
	char Isolation[ISOLATION_LENGTH];			//隔离
	char Account[ACCOUNT_LENGTH];				//计费

} _PatientData;

extern void parseData(void);
#endif

