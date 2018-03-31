#include "TimeEvent.h"
#include <Windows.h>


CTimeEvent::CTimeEvent(void) : m_nActiveTime(0), m_nLastActive(0),
	m_nType(eTIME_EVENT_NONE), m_isRun(false), m_cDateFlag(eDF_NONE)
{
}


CTimeEvent::~CTimeEvent(void)
{
}

//�̺�Ʈ�� �۵��ð��� �´��� ��ȯ�ϴ� �Լ�
//�����Լ��ν� ���� Ŭ�������� �ߵ������� ���� �ۼ� �� ���ִ�.
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

//�̺�Ʈ�� �۵��ð��� �´��� ��ȯ�ϴ� �Լ�(��¥�� Ȯ��)
bool CTimeEvent::IsEventTime(ST_DATE& _stNowDate)
{
	return CTime::CompareDate(m_stActiveDate, _stNowDate, m_cDateFlag);
}

//�̺�Ʈ�� �۵��ð��� �����ϴ� �Լ�(���� : ms)
void CTimeEvent::SetActiveTime(int _nActiveTime)
{
	m_nActiveTime = _nActiveTime;
	m_nType = eTIMER;
}

//�̺�Ʈ�� �۵��ð��� �����ϴ� �Լ�(���� : ��¥)
void CTimeEvent::SetActiveTime(ST_DATE& _stActiveDate, char _cFlag)
{
	m_stActiveDate = _stActiveDate;
	m_nType = eDATE;
	m_cDateFlag = _cFlag;
}

//�̺�Ʈ �۵����θ� �����ϴ� �Լ�
void CTimeEvent::SetRun(bool _bRun)
{
	m_isRun = _bRun;
	m_nLastActive = GetTickCount();

}