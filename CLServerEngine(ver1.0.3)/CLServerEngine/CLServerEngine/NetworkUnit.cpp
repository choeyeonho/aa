#include "NetworkUnit.h"
#include "CommonHeader.h"

CNetworkUnit::CNetworkUnit(void)
{
}


CNetworkUnit::~CNetworkUnit(void)
{
}
//< 주체를 설정
void		CNetworkUnit::SetServer( CServer* _pServer )
{
	if( _pServer != nullptr )
		m_pServerOwner = _pServer;
}
CServer*	CNetworkUnit::GetServer()
{
	return m_pServerOwner;
}
//< 소켓 초기화
BOOL		CNetworkUnit::InitSocket(const int _sendBufferSize, const int _recvBufferSize)
{
	if( CreateSocket() == SOCKET_ERROR )
	{
		return false;
	}

	return InitBuffer(_sendBufferSize,_recvBufferSize);
}

//< 버퍼 초기화
BOOL		CNetworkUnit::InitBuffer(const int _sendBufferSize, const int _recvBufferSize)
{
	m_pSendBuffer = new CQueueBuffer();
	m_pRecvBuffer = new CQueueBuffer();

	//< 사이즈 조절
	m_pSendBuffer->Initializing(_sendBufferSize);
	m_pRecvBuffer->Initializing(_recvBufferSize);

	return TRUE;
}


//< 디스커넥트
BOOL		CNetworkUnit::Disconnect()
{	
	SAFE_DELETE(m_pRecvBuffer);
	SAFE_DELETE(m_pSendBuffer);

	CloseSocket();	

	return TRUE;
}

//< 바인딩 작업
BOOL		CNetworkUnit::Binding(char* _pIP, const int _nPort)
{
	m_SockAddr = new CSockAddr(_pIP,_nPort);
	if( bind( m_socket, (SOCKADDR*)&m_SockAddr->GetSockAddr(),sizeof(SOCKADDR_IN)) == SOCKET_ERROR )
	{
		return FALSE;
	}
	return TRUE;
}

BOOL		CNetworkUnit::Binding(const int _nPort)
{
	m_SockAddr = new CSockAddr(_nPort);
	if( bind( m_socket, (SOCKADDR*)&m_SockAddr->GetSockAddr(),sizeof(SOCKADDR_IN)) == SOCKET_ERROR )
	{
		return FALSE;
	}
	return TRUE;
}

//< 리스닝 작업
BOOL		CNetworkUnit::Listening(const int _nBackLog)
{
	listen(m_socket,_nBackLog);

	return TRUE;
}
CQueueBuffer*			CNetworkUnit::GetSendBuffer()
{
	return m_pSendBuffer;
}
CQueueBuffer*			CNetworkUnit::GetRecvBuffer()
{
	return m_pRecvBuffer;
}

void					CNetworkUnit::Send(BUF_PACKET_TYPE _buf)
{
	//< 변경해야함
}
stOverlappedGroup		CNetworkUnit::GetOverlappedGroup()
{
	return m_overlapped;
}