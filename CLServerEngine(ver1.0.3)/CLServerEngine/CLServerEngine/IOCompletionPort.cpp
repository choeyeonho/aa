#include "IOCompletionPort.h"


CIOCompletionPort::CIOCompletionPort(int nMaxConcurrency) : m_hIOCP(NULL)
{
	//< 4번째 인자가 0이면 시스템은 시스템에 프로세서가있는 수만큼 동시에 실행중인 스레드를 허용합니다.
	m_hIOCP = ::CreateIoCompletionPort( INVALID_HANDLE_VALUE, NULL, 0, nMaxConcurrency );
	
	if( NULL == m_hIOCP )
	{		
		//< Log 추가 할것 CYH_ADD_LOG
		// AddLog->Write( RedWrite, _T(" CompletionPort Error() - %s"), W2A(GetLastErrorMessage()) );
	}
}
CIOCompletionPort::~CIOCompletionPort(void)
{
	SAFE_CLOSE_HANDLE(m_hIOCP);
}
//< IOCP와 Socket Handle을 묶습니다.
bool		CIOCompletionPort::AssociateSocket(SOCKET _sock,DWORD dwCompletionKey)
{
	if( NULL == ::CreateIoCompletionPort((HANDLE)_sock, m_hIOCP, dwCompletionKey, 0) )
	{
		//< Log 추가 할것 CYH_ADD_LOG
		// AddLog->Write( RedWrite, _T(" AssociateSocket Error() - %s"), W2A(GetLastErrorMessage()) );
		return false;
	}

	return true;
}
//< IOCP로 특정 상태를 보내자
bool		CIOCompletionPort::PostStatus(ULONG_PTR dwCompletionKey, DWORD dwBytes, OVERLAPPED* pOver)
{
	return ( 0 != ::PostQueuedCompletionStatus(m_hIOCP, dwBytes, dwCompletionKey, pOver) );
}
//< IOCP의 현재 상태를 읽는다.
bool		CIOCompletionPort::GetStatus(ULONG_PTR* pdwCompletionKey, DWORD* pdwBytes, OVERLAPPED** ppOver, DWORD dwMilliSeconds)
{
	return ( 0 != ::GetQueuedCompletionStatus(m_hIOCP, pdwBytes, pdwCompletionKey, ppOver, dwMilliSeconds) );
}