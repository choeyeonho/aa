#include "Thread.h"
#include "ThreadManager.h"

CThread::CThread() : m_hThreadHandle(INVALID_HANDLE_VALUE)
{
}

CThread::~CThread()
{
}
HRESULT		CThread::Create()
{
	//< �� .. �̰� ���� �ϰ��� ?? .. 
	return TRUE;
}
HRESULT		CThread::StartThread(int (*_func)())
{
	if( INVALID_HANDLE_VALUE == m_hThreadHandle )
	{
		if( _func != nullptr )
		{
			m_bISObjected = TRUE;
			m_pFunc = _func;
		}

		unsigned int nThreadID = 0;

		//< ��ƾ�� 1ȸ ���� �Լ�
		Create();

		//< ����
		m_hThreadHandle = (HANDLE)::_beginthreadex( 0, 0, ThreadFunction, static_cast<void*>(this), 0, &nThreadID );

		//< ���� ����
		if( INVALID_HANDLE_VALUE == m_hThreadHandle )								
			return FALSE;				
	}
	else
	{		
		//< �̹� �����Ǿ� �ֽ��ϴ�.
		return FALSE;
	}

	//< ����
	return TRUE;
}
HRESULT		CThread::WaitThread(DWORD dwTimeOut)
{
	//< ��� !
	DWORD dwResult = WaitForSingleObject( m_hThreadHandle, dwTimeOut );

	//< ó�� �Ϸ�
	if( WAIT_OBJECT_0 == dwResult )
	{
		return TRUE;
	}
	else if( WAIT_TIMEOUT == dwResult ) //< ó�� ����
	{
		return FALSE;
	}

	return FALSE;
}
HANDLE		CThread::GetHandle()
{
	return m_hThreadHandle;
}
void			CThread::SetSwitchingTime(DWORD	_dwDelayTime)
{
	m_dwCurTime = m_dwLastTime = GetTickCount();
}
void			CThread::ContextSwitching()
{
	m_dwCurTime = GetTickCount();

	if( m_dwCurTime - m_dwLastTime > m_dwDelayTime )
	{
		//< CPU�� 1 m/s ���� ��⿭���� ����
		//< ���� ����δ� 1 m/s�� �ٷ� ������ �ƴϰ� ��ǻ�͸��� ���̰� �ֽ��ϴ�.
		Sleep(1);

		m_dwLastTime = m_dwCurTime;
	}
}
unsigned int __stdcall CThread::ThreadFunction(void* pv)
{
	CThread*		pThis	= static_cast<CThread*>(pv);
	int			nTempNum = 0;
	int			nCoreNumber = 0;

	//< null check
	if( pThis != nullptr )
	{
		//< Ǯ�� ����� ����
		nCoreNumber = SThreadManager->AddThread(pThis->GetHandle(),pThis);

		if( nCoreNumber == -1 )
		{
			//< Log �߰� �Ұ� CYH_ADD_LOG
			// AddLog->Write( RedWrite, _T(" Create Therad Error() ") );

			//< ���� ����
			return nTempNum;
		}

		//< ������ ���� Log�߰�
		//AddLog->(��¼����¼��, ��� �ھ �Ҵ� ����� ���� );

		if( pThis->GetIsObjected() == TRUE )
			nTempNum = pThis->GetFunc()();
		else
			nTempNum = pThis->Run();		
		

		//< ��� �����尡 ������ Ǯ���� ����	
		SThreadManager->DeleteThread(pThis->GetHandle(),nCoreNumber);		
	}

	return nTempNum;
}
int	CThread::Run() 
{
	return 0;
}
BOOL				CThread::GetIsObjected()
{
	return m_bISObjected;
}
int (*CThread::GetFunc())()
{
	return m_pFunc; 
}