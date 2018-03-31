/*
작성자 : 이승하
날  짜 : 2018-03-18
설  명 : 시간 관련 클래스
변  경 : < 이승하 , 2018-03-20 >
		날짜 비교를 사용자가 비트플래그를 이용하여 지정할 수 있게 수정
*/
#pragma once
#include <Windows.h>

typedef struct ST_DATE
{
	WORD wYear;		//Year
	WORD wMonth;	//Start Since Jan (1~12)
	WORD wWeekDay;	//Start Since Sunday (0 ~ 6)
	WORD wDay;		//Day (1~31)
	WORD wHour;		//Hour (0 ~ 23)
	WORD wMinute;	//Minute (0 ~ 59)
	WORD wSecond;	//Second (0 ~ 59)
}ST_DATE;

enum E_DATE_FLAG
{
	eDF_NONE = 0,
	eDF_SECOND = 1,
	eDF_MINUTE = 2,
	eDF_HOUR = 4,
	eDF_DAY = 8,
	eDF_WEEKDAY = 16,
	eDF_MONTH = 32,
	eDF_YEAR = 64,
	eDF_ALL = 127
};

class CTime
{
private:
	CTime(void);
	~CTime(void);

public:
	static int		GetTime();
	static ST_DATE	GetDate();
	static ST_DATE	CreateDate(WORD _wYear, WORD _wMonth, WORD _wDay, WORD _wHour, WORD _wMinute, WORD _wSecond);
	static bool		CompareDate(ST_DATE& _date1, ST_DATE& _date2, char _cFlag = eDF_ALL);
};