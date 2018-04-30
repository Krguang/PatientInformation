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
	char Number[NUMBER_LENGTH];					//���
	char Name[NAME_LENGTH];						//����
	char Gender[GENDER_LENGTH];					//�Ա�
	char Age[AGE_LENGTH];						//����
	char NurseLevel[NURSE_LEVEL_LENGTH];		//����ȼ�
	char HospNum[HOSP_NUM_LENGTH];				//סԺ��
	char HospTime[HOSP_TIME_LENGTH];			//סԺʱ��
	char ChargeDoctor[CHARGE_DOCTOR_LENGTH];	//����ҽ��
	char ChargeNurse[CHARGE_NURSE_LENGTH];		//���λ�ʿ
	char Diagnosis[DIAGNOSIS_LENGTH];			//���
	char Others[OTHERS_LENGTH];					//����
	char Medicare[MEDICARE_LENGTH];				//ҽ��
	char Diet[DIET_LENGTH];						//��ʳ
	char Isolation[ISOLATION_LENGTH];			//����
	char Account[ACCOUNT_LENGTH];				//�Ʒ�

} _PatientData;

extern void parseData(void);
#endif

