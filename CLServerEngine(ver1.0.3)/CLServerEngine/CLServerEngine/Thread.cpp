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
	//< 뭐 .. 이것 저것 하겠지 ?? .. 
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

		//< 루틴전 1회 실행 함수
		Create();

		//< 생성
		m_hThreadHandle = (HANDLE)::_beginthreadex( 0, 0, ThreadFunction, static_cast<void*>(this), 0, &nThreadID );

		//< 생성 실패
		if( INVALID_HANDLE_VALUE == m_hThreadHandle )								
			return FALSE;				
	}
	else
	{		
		//< 이미 생성되어 있습니다.
		return FALSE;
	}

	//< 성공
	return TRUE;
}
HRESULT		CThread::WaitThread(DWORD dwTimeOut)
{
	//< 대기 !
	DWORD dwResult = WaitForSingleObject( m_hThreadHandle, dwTimeOut );

	//< 처리 완료
	if( WAIT_OBJECT_0 == dwResult )
	{
		return TRUE;
	}
	else if( WAIT_TIMEOUT == dwResult ) //< 처리 실패
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
		//< CPU를 1 m/s 동안 대기열에서 제외
		//< 실제 결과로는 1 m/s후 바로 동작이 아니고 컴퓨터마다 차이가 있습니다.
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
		//< 풀에 등록후 실행
		nCoreNumber = SThreadManager->AddThread(pThis->GetHandle(),pThis);

		if( nCoreNumber == -1 )
		{
			//< Log 추가 할것 CYH_ADD_LOG
			// AddLog->Write( RedWrite, _T(" Create Therad Error() ") );

			//< 강제 종료
			return nTempNum;
		}

		//< 쓰레드 생성 Log추가
		//AddLog->(어쩌구저쩌구, 어느 코어에 할당 됬는지 까지 );

		if( pThis->GetIsObjected() == TRUE )
			nTempNum = pThis->GetFunc()();
		else
			nTempNum = pThis->Run();		
		

		//< 모든 쓰레드가 끝나면 풀에서 삭제	
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