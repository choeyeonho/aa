#include "Time.h"
#include <time.h>

CTime::CTime(void)
{
}


CTime::~CTime(void)
{
}

//���� �Լ� ȣ��κ��� ������ �ð��� ��ȯ
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

//���� �ð��� ��ȯ�ϴ� �Լ�
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

//���� ������ Date����ü�� ����� �ִ� �Լ�
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

	//���ϰ��
	stDate.wWeekDay = (_wYear + _wYear/4 - _wYear/100 + _wYear/400 + t[_wMonth - 1] + _wDay) % 7;

	return stDate;
}

//�� ��¥�� ���Ͽ� ������ ��ȯ�ϴ� �Լ�
//_eFlag�� ��¥ ������ �ִ´�(ex : day, hour�� ������ true => (_eFlag = eDF_DAY | eDF_HOUR))
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