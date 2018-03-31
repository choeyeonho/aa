#include "TimeDispatcher.h"
#include "ThreadManager.h"

CTimeDispatcher* CTimeDispatcher::m_pInstance = nullptr;

CTimeDispatcher::CTimeDispatcher(void) : m_isThreadRun(false)
{
}

CTimeDispatcher::~CTimeDispatcher(void)
{
}

//시간이벤트를 등록
HRESULT CTimeDispatcher::AddEvent(int _nKey, CTimeEvent* _pTimeEvent)
{
	if(GetEvent(_nKey) != nullptr)
		return FALSE;

	m_mEventList.insert(std::pair<int, CTimeEvent*>(_nKey, _pTimeEvent));

	if(m_isThreadRun == false)
	{
		StartThread();
		m_isThreadRun = true;
	}

	return TRUE;
}

//시간이벤트를 삭제
HRESULT CTimeDispatcher::RemoveEvent(int _nKey)
{
	if(GetEvent(_nKey) != nullptr)
		return FALSE;

	m_mEventList.erase(_nKey);

	if(m_mEventList.size() == 0)
		m_isThreadRun = false;

	return TRUE;
}

//시간이벤트 발동을 설정
HRESULT CTimeDispatcher::SetEventRun(int _nKey, bool _bRun)
{
	CTimeEvent* pTimeEvent = GetEvent(_nKey);

	if(pTimeEvent == nullptr)
		return FALSE;

	pTimeEvent->SetRun(_bRun);
	return TRUE;
}

//시간이벤트 클래스를 얻는다.
CTimeEvent* CTimeDispatcher::GetEvent(int _nKey)
{
	CTimeEvent* pEvent = nullptr;

	return (m_mEventList.find(_nKey) == m_mEventList.end()) ? nullptr : m_mEventList[_nKey];
}

//쓰레드를 이용하여 등록된 이벤트를 확인하고 작동시켜준다.
int CTimeDispatcher::Run()
{
	std::map<int, CTimeEvent*>::const_iterator cIter;
	CTimeEvent* pEvent = nullptr;

	while(1)
	{
		if(m_isThreadRun == false)
			break;

		for(cIter = m_mEventList.begin(); cIter != m_mEventList.end(); ++cIter)
		{
			pEvent = cIter->second;

			if(pEvent == nullptr)
				continue;

			if(pEvent->IsEventTime() == true)
				pEvent->Execute();
		}
	}

	return 0;
}

CTimeDispatcher* CTimeDispatcher::GetInstance()
{
	if(m_pInstance == nullptr)
		m_pInstance = new CTimeDispatcher();

	return m_pInstance;
}