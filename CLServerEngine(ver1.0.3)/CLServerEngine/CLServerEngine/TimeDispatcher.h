/*
작성자 : 이승하
날  짜 : 2018-03-18
설  명 : 시간이벤트를 관리하는 클래스
*/

#pragma once
#include <map>
#include "Thread.h"
#include "TimeEvent.h"

class CTimeDispatcher : public CThread
{
private:
	CTimeDispatcher(void);
	~CTimeDispatcher(void);

	//TimeDispatcher 싱글톤
	static CTimeDispatcher*	m_pInstance;

public:
	static CTimeDispatcher* GetInstance();

private:
	std::map<int, CTimeEvent*>	m_mEventList;
	bool						m_isThreadRun;

public:
	HRESULT		AddEvent(int _nKey, CTimeEvent* _pEvent);
	HRESULT		RemoveEvent(int _nKey);
	HRESULT		SetEventRun(int _nKey, bool _bRun);
	CTimeEvent* GetEvent(int _nKey);

	int Run();
};

#define STimeDispatcher CTimeDispatcher::GetInstance()