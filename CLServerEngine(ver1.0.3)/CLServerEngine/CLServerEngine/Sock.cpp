#include "Sock.h"


CSock::CSock(void)
{
}


CSock::~CSock(void)
{
}
SOCKET		CSock::CreateSocket()
{
	m_socket = WSASocket( AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED );

	if( INVALID_SOCKET == m_socket )
	{
		// Logger.AddLog( LOG_FILE_LOG, CERR, L"CSock::CreateSocket() - %s", GetLastErrorMessage() );
		return SOCKET_ERROR;
	}

	//< 옵션 설정
	if ( SetSocketOption() == false )
		return SOCKET_ERROR;	

	return m_socket;
}
int			CSock::CloseSocket()
{
	::closesocket(m_socket);
}
BOOL			CSock::SetSocketOption(DWORD	_optname, char* _val )
{
	if( SOCKET_ERROR == setsockopt(m_socket, SOL_SOCKET, _optname, (char*)_val, sizeof(int)) )
	{
		// Logger.AddLog( LOG_FILE_LOG, CERR, L"CSock::SetSocketOption() - %s", GetLastErrorMessage() );
		return false;
	}
	return true;
}
BOOL			CSock::SetSocketOption()
{
	
	//< 0을 대입시 최소값으로 잡힘 : 2048 , 256
	int nZero = 0;

	if( SOCKET_ERROR == setsockopt(m_socket, SOL_SOCKET, SO_RCVBUF, (char*)&nZero, sizeof(int)) )
	{
		// Logger.AddLog( LOG_FILE_LOG, CERR, L"CSock::SetSocketOption() - %s", GetLastErrorMessage() );
		return false;
	}

	nZero = 0;
	if( SOCKET_ERROR == setsockopt(m_socket, SOL_SOCKET, SO_SNDBUF, (char*)&nZero, sizeof(int)) )
	{
		// Logger.AddLog( LOG_FILE_LOG, CERR, L"CSock::SetSocketOption() - %s", GetLastErrorMessage() );
		return false;
	}	

	//< 재사용 개꿀
	int on_flag = 1; 
	if( SOCKET_ERROR == setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&on_flag, sizeof(on_flag)) )
	{
		// Logger.AddLog( LOG_FILE_LOG, CERR, L"CSock::SetSocketOption() - %s", GetLastErrorMessage() );
		return false;
	}

	return SetLinger( true );
}
/*
l_onoff == 0 : 이 경우 l_linger의 영향을 받지 않는다. 
소켓의 기본설정으로 소켓버퍼에 남아 있는 모든 데이터를 보낸다.
이때 close()는 바로 리턴을 하게 되므로 백그라운드에서 이러한 일이 일어나게 된다. 
우아한 연결 종료를 보장한다.

l_onoff > 0 이고 l_linger == 0 : 
close()는 바로 리턴을 하며, 소켓버퍼에 아직 남아있는 데이터는 버려 버린다.
TCP 연결상태일 경우에는 상대편 호스트에 리셋을 위한 RST 패킷을 보낸다. 
hard 혹은 abortive 종료라고 부른다.

l_onoff > 0 이고 l_linger > 0 : 
버퍼에 남아있는 데이터를 모두 보내는 우아한 연결 종료를 행한다. 
이때 close()에서는 l_linger에 지정된 시간만큼 블럭상태에서 대기한다. 
만약 지정된 시간내에 데이터를 모두 보냈다면 리턴이 되고, 
시간이 초과되었다면 에러와 함께 리턴이 된다.
*/
BOOL			CSock::SetLinger(BOOL _bGraceful)
{
	if( INVALID_SOCKET == m_socket )
	{
		return false;
	}

	LINGER stLinger = {0};

	if( _bGraceful )
	{
		stLinger.l_onoff = 1;
		stLinger.l_linger = 0;
	}
	else
	{
		stLinger.l_onoff = 0;
		stLinger.l_linger = 1;
	}

	if( SOCKET_ERROR == setsockopt(m_socket, SOL_SOCKET, SO_LINGER, (char*)&stLinger, sizeof(stLinger)) )
	{
		// Logger.AddLog( LOG_FILE_LOG, CERR, L"CSockStream::SetLinger() - %s", GetLastErrorMessage() );
		return false;
	}

	return true;
}

SOCKET		CSock::GetSocket()
{
	return m_socket;
}
void			CSock::SetSocket(SOCKET _socket)	//< 클라이언트 접속시 들어오는 소켓 저장
{
	m_socket = _socket;
}

void			CSock::GetLocalIP( char* const _pIP )
{
	CHAR Name[256] = { 0, };

	//< 로컬 호스트의 이름을 얻습니다. 
	int nResult = gethostname( Name, sizeof(Name) ); 
	if( 0 != nResult )
	{
		return;
	}

	PHOSTENT host = gethostbyname( Name );
	if( NULL != host )
	{
		strcpy_s( _pIP, sizeof(_pIP), inet_ntoa(*(struct in_addr *)*host->h_addr_list) );
	}
}

WORD			CSock::GetLocalPort( void )
{
	SOCKADDR_IN Addr;
	ZeroMemory( &Addr, sizeof(Addr) );

	INT AddrLength = sizeof( Addr );
	if( getsockname(m_socket, (SOCKADDR*)&Addr, &AddrLength) != SOCKET_ERROR )
	{		
		return ntohs( Addr.sin_port );
	}

	return 0;
}