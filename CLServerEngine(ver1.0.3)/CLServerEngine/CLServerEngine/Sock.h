#pragma once
/*
작성자 : 최연호
날  짜 : 2018-03-27
내  용 : 소켓 정보 클레스
*/
#include <WinSock2.h>

class CSock
{
protected:
	SOCKET		m_socket;			//< 소켓
	
public:
	CSock(void);	
	~CSock(void);
protected:
	SOCKET		CreateSocket();
	int			CloseSocket();

	//< 기본 설정함수와, 지정설정 함수
	BOOL			SetSocketOption();
	BOOL			SetSocketOption(DWORD	_optname, char* _val );

	//< 세션이 끊겼을때의 옵션
	BOOL			SetLinger(BOOL _bGraceful);
	
public:
	SOCKET		GetSocket();
	void			SetSocket(SOCKET _socket);	//< 클라이언트 접속시 들어오는 소켓 저장

	void			GetIP();
	void			GetLocalIP( char* const _pIP );
	WORD			GetLocalPort( void );

private:			
	//< c++에서 자동으로 복사연산자가 생성됨
	//< 개인적으로 생성하여 private안에 두어 복사 방지

	//< 복사 방지
	CSock (const CSock &);			
	CSock& operator= (const CSock &);
};

