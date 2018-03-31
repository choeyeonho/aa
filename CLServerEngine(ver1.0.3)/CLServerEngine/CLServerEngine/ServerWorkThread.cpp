#include "ServerWorkThread.h"


CServerWorkThread::CServerWorkThread(const int _nNumberOfThread) : m_nNumberOfThread (_nNumberOfThread )
{
	//< 0이면 기본 프로세서 * 2 + 2만큼 생성
	if ( _nNumberOfThread == 0 )
	{
		SYSTEM_INFO si;
		GetSystemInfo( &si );

		
		m_nNumberOfThread = si.dwNumberOfProcessors * 2 + 2;
	}
}


CServerWorkThread::~CServerWorkThread(void)
{
}

HRESULT CServerWorkThread::Create()
{

	return TRUE;
}

int CServerWorkThread::Run()
{
	return 0;
}