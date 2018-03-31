#include "SockAddr.h"


CSockAddr::CSockAddr(void)
{
}

//< 클라에서 Addr을 만들때
CSockAddr::CSockAddr(const unsigned short _nPort)
{
	memset( &m_sockAddr, 0x00, sizeof(m_sockAddr) );

	m_sockAddr.sin_family			= AF_INET;
	m_sockAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	m_sockAddr.sin_port			= htons(_nPort);
}

//< 서버에서 Addr을 만들때
CSockAddr::CSockAddr(char* _pIP, const unsigned short _nPort)
{
	memset( &m_sockAddr, 0x00, sizeof(m_sockAddr) );

	m_sockAddr.sin_family			= AF_INET;
	m_sockAddr.sin_addr.S_un.S_addr = inet_addr(_pIP);
	m_sockAddr.sin_port			= htons(_nPort);
}

CSockAddr::~CSockAddr(void)
{

}

SOCKADDR_IN			CSockAddr::GetSockAddr()
{
	return m_sockAddr;
}

char*				CSockAddr::GetIP(void)
{
	return inet_ntoa( m_sockAddr.sin_addr );
}

unsigned short		CSockAddr::GetPort(void)
{
	return ntohs( m_sockAddr.sin_port );
}