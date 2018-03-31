#include "TimeDispatcher.h"
#include "ThreadManager.h"

CTimeDispatcher* CTimeDispatcher::m_pInstance = nullptr;

CTimeDispatcher::CTimeDispatcher(void) : m_isThreadRun(false)
{
}

CTimeDispatcher::~CTimeDispatcher(void)
{
}

//�ð��̺�Ʈ�� ���
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

//�ð��̺�Ʈ�� ����
HRESULT CTimeDispatcher::RemoveEvent(int _nKey)
{
	if(GetEvent(_nKey) != nullptr)
		return FALSE;

	m_mEventList.erase(_nKey);

	if(m_mEventList.size() == 0)
		m_isThreadRun = false;

	return TRUE;
}

//�ð��̺�Ʈ �ߵ��� ����
HRESULT CTimeDispatcher::SetEventRun(int _nKey, bool _bRun)
{
	CTimeEvent* pTimeEvent = GetEvent(_nKey);

	if(pTimeEvent == nullptr)
		return FALSE;

	pTimeEvent->SetRun(_bRun);
	return TRUE;
}

//�ð��̺�Ʈ Ŭ������ ��´�.
CTimeEvent* CTimeDispatcher::GetEvent(int _nKey)
{
	CTimeEvent* pEvent = nullptr;

	return (m_mEventList.find(_nKey) == m_mEventList.end()) ? nullptr : m_mEventList[_nKey];
}

//�����带 �̿��Ͽ� ��ϵ� �̺�Ʈ�� Ȯ���ϰ� �۵������ش�.
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