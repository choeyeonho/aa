#pragma once
/*
작성자 : 최연호
날  짜 : 2018-03-27
내  용 : 소켓 어드레스 정보 클레스
*/

#include <WinSock2.h>

class CSockAddr
{
private:
	SOCKADDR_IN			m_sockAddr;
public:
	CSockAddr(void);
	//< 클라에서 Addr을 만들때
	CSockAddr(const unsigned short _nPort);
	//< 서버에서 Addr을 만들때
	CSockAddr(char* _pIP, const unsigned short _nPort);

	~CSockAddr(void);


	SOCKADDR_IN			GetSockAddr();
	void					SetSockAddr();

	char*				GetIP(void);
	unsigned short		GetPort(void);

	
};

