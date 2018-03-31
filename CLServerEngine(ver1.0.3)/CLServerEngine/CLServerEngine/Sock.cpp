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

	//< �ɼ� ����
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
	
	//< 0�� ���Խ� �ּҰ����� ���� : 2048 , 256
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

	//< ���� ����
	int on_flag = 1; 
	if( SOCKET_ERROR == setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&on_flag, sizeof(on_flag)) )
	{
		// Logger.AddLog( LOG_FILE_LOG, CERR, L"CSock::SetSocketOption() - %s", GetLastErrorMessage() );
		return false;
	}

	return SetLinger( true );
}
/*
l_onoff == 0 : �� ��� l_linger�� ������ ���� �ʴ´�. 
������ �⺻�������� ���Ϲ��ۿ� ���� �ִ� ��� �����͸� ������.
�̶� close()�� �ٷ� ������ �ϰ� �ǹǷ� ��׶��忡�� �̷��� ���� �Ͼ�� �ȴ�. 
����� ���� ���Ḧ �����Ѵ�.

l_onoff > 0 �̰� l_linger == 0 : 
close()�� �ٷ� ������ �ϸ�, ���Ϲ��ۿ� ���� �����ִ� �����ʹ� ���� ������.
TCP ��������� ��쿡�� ����� ȣ��Ʈ�� ������ ���� RST ��Ŷ�� ������. 
hard Ȥ�� abortive ������ �θ���.

l_onoff > 0 �̰� l_linger > 0 : 
���ۿ� �����ִ� �����͸� ��� ������ ����� ���� ���Ḧ ���Ѵ�. 
�̶� close()������ l_linger�� ������ �ð���ŭ �����¿��� ����Ѵ�. 
���� ������ �ð����� �����͸� ��� ���´ٸ� ������ �ǰ�, 
�ð��� �ʰ��Ǿ��ٸ� ������ �Բ� ������ �ȴ�.
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
void			CSock::SetSocket(SOCKET _socket)	//< Ŭ���̾�Ʈ ���ӽ� ������ ���� ����
{
	m_socket = _socket;
}

void			CSock::GetLocalIP( char* const _pIP )
{
	CHAR Name[256] = { 0, };

	//< ���� ȣ��Ʈ�� �̸��� ����ϴ�. 
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