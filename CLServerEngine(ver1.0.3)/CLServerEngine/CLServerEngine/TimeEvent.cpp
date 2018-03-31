#include "TimeEvent.h"
#include <Windows.h>


CTimeEvent::CTimeEvent(void) : m_nActiveTime(0), m_nLastActive(0),
	m_nType(eTIME_EVENT_NONE), m_isRun(false), m_cDateFlag(eDF_NONE)
{
}


CTimeEvent::~CTimeEvent(void)
{
}

//이벤트의 작동시간이 맞는지 반환하는 함수
//가상함수로써 하위 클래스에서 발동조건을 따로 작성 할 수있다.
bool CTimeEvent::IsEventTime()
{
	if(m_isRun == false)
		return false;

	if(m_nType == eDATE)
	{
		ST_DATE nowDate = CTime::GetDate();

		return IsEventTime(nowDate);
	}

	int nowTime = GetTickCount();

	if(nowTime - m_nLastActive >= m_nActiveTime)
	{
		m_nLastActive = nowTime;
		return true;
	}
	else
		return false;
}

//이벤트의 작동시간이 맞는지 반환하는 함수(날짜로 확인)
bool CTimeEvent::IsEventTime(ST_DATE& _stNowDate)
{
	return CTime::CompareDate(m_stActiveDate, _stNowDate, m_cDateFlag);
}

//이벤트의 작동시간을 설정하는 함수(단위 : ms)
void CTimeEvent::SetActiveTime(int _nActiveTime)
{
	m_nActiveTime = _nActiveTime;
	m_nType = eTIMER;
}

//이벤트의 작동시간을 설정하는 함수(단위 : 날짜)
void CTimeEvent::SetActiveTime(ST_DATE& _stActiveDate, char _cFlag)
{
	m_stActiveDate = _stActiveDate;
	m_nType = eDATE;
	m_cDateFlag = _cFlag;
}

//이벤트 작동여부를 설정하는 함수
void CTimeEvent::SetRun(bool _bRun)
{
	m_isRun = _bRun;
	m_nLastActive = GetTickCount();

}