#include "Time.h"
#include <time.h>

CTime::CTime(void)
{
}


CTime::~CTime(void)
{
}

//최초 함수 호출로부터 지나간 시간을 반환
int CTime::GetTime()
{
	static int nowTime;

	if(nowTime == 0)
	{
		nowTime = GetTickCount();
		return 0;
	}
	else
		nowTime = GetTickCount();

	return nowTime;
}

//현재 시간을 반환하는 함수
ST_DATE CTime::GetDate()
{
	time_t	tTime;	
	ST_DATE	date;
	struct	tm base_date_local;

	time(&tTime);

	localtime_s(&base_date_local, &tTime);	
	date.wYear = base_date_local.tm_year + 1900;
	date.wMonth = base_date_local.tm_mon + 1;
	date.wWeekDay = base_date_local.tm_wday;
	date.wDay = base_date_local.tm_mday;
	date.wHour = base_date_local.tm_hour;
	date.wMinute = base_date_local.tm_min;
	date.wSecond = base_date_local.tm_sec;

	return date;
}

//값을 넣으면 Date구조체로 만들어 주는 함수
ST_DATE CTime::CreateDate(WORD _wYear, WORD _wMonth, WORD _wDay, WORD _wHour, WORD _wMinute, WORD _wSecond)
{
	ST_DATE stDate;
	stDate.wYear = _wYear;
	stDate.wMonth = _wMonth;
	stDate.wDay = _wDay;
	stDate.wHour = _wHour;
	stDate.wMinute = _wMinute;
	stDate.wSecond = _wSecond;

	int t[] = {0,3,2,5,0,3,5,1,4,6,2,4};

	_wYear-=_wMonth < 3;

	//요일계산
	stDate.wWeekDay = (_wYear + _wYear/4 - _wYear/100 + _wYear/400 + t[_wMonth - 1] + _wDay) % 7;

	return stDate;
}

//두 날짜를 비교하여 같은지 반환하는 함수
//_eFlag에 날짜 조건을 넣는다(ex : day, hour만 같으면 true => (_eFlag = eDF_DAY | eDF_HOUR))
bool CTime::CompareDate(ST_DATE& _date1, ST_DATE& _date2, char _cFlag)
{
	char cBit = 0;
	int nCount = 0;
	char cFlag = _cFlag;
	WORD* pDate1 = nullptr;
	WORD* pDate2 = nullptr;

	if(cFlag > eDF_ALL)
		cFlag = eDF_ALL;

	while(cFlag > 0)
	{
		cBit = cFlag & 1;

		if(cBit == 1)
		{
			pDate1 = ((WORD*)&_date1) + (6 - nCount);
			pDate2 = ((WORD*)&_date2) + (6 - nCount);

			if((*pDate1) != (*pDate2))
				return false;
		}

		++nCount;
		cFlag = cFlag >> 1;
	}

	return true;
}