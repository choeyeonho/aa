#include "IOCompletionPort.h"


CIOCompletionPort::CIOCompletionPort(int nMaxConcurrency) : m_hIOCP(NULL)
{
	//< 4��° ���ڰ� 0�̸� �ý����� �ý��ۿ� ���μ������ִ� ����ŭ ���ÿ� �������� �����带 ����մϴ�.
	m_hIOCP = ::CreateIoCompletionPort( INVALID_HANDLE_VALUE, NULL, 0, nMaxConcurrency );
	
	if( NULL == m_hIOCP )
	{		
		//< Log �߰� �Ұ� CYH_ADD_LOG
		// AddLog->Write( RedWrite, _T(" CompletionPort Error() - %s"), W2A(GetLastErrorMessage()) );
	}
}
CIOCompletionPort::~CIOCompletionPort(void)
{
	SAFE_CLOSE_HANDLE(m_hIOCP);
}
//< IOCP�� Socket Handle�� �����ϴ�.
bool		CIOCompletionPort::AssociateSocket(SOCKET _sock,DWORD dwCompletionKey)
{
	if( NULL == ::CreateIoCompletionPort((HANDLE)_sock, m_hIOCP, dwCompletionKey, 0) )
	{
		//< Log �߰� �Ұ� CYH_ADD_LOG
		// AddLog->Write( RedWrite, _T(" AssociateSocket Error() - %s"), W2A(GetLastErrorMessage()) );
		return false;
	}

	return true;
}
//< IOCP�� Ư�� ���¸� ������
bool		CIOCompletionPort::PostStatus(ULONG_PTR dwCompletionKey, DWORD dwBytes, OVERLAPPED* pOver)
{
	return ( 0 != ::PostQueuedCompletionStatus(m_hIOCP, dwBytes, dwCompletionKey, pOver) );
}
//< IOCP�� ���� ���¸� �д´�.
bool		CIOCompletionPort::GetStatus(ULONG_PTR* pdwCompletionKey, DWORD* pdwBytes, OVERLAPPED** ppOver, DWORD dwMilliSeconds)
{
	return ( 0 != ::GetQueuedCompletionStatus(m_hIOCP, pdwBytes, pdwCompletionKey, ppOver, dwMilliSeconds) );
}