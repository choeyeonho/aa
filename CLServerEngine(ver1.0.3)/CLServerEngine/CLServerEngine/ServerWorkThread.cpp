#include "ServerWorkThread.h"


CServerWorkThread::CServerWorkThread(const int _nNumberOfThread) : m_nNumberOfThread (_nNumberOfThread )
{
	//< 0�̸� �⺻ ���μ��� * 2 + 2��ŭ ����
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