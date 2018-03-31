#pragma once
/*
�ۼ��� : �ֿ�ȣ
��  ¥ : 2018-03-27
��  �� : ���� ��巹�� ���� Ŭ����
*/

#include <WinSock2.h>

class CSockAddr
{
private:
	SOCKADDR_IN			m_sockAddr;
public:
	CSockAddr(void);
	//< Ŭ�󿡼� Addr�� ���鶧
	CSockAddr(const unsigned short _nPort);
	//< �������� Addr�� ���鶧
	CSockAddr(char* _pIP, const unsigned short _nPort);

	~CSockAddr(void);


	SOCKADDR_IN			GetSockAddr();
	void					SetSockAddr();

	char*				GetIP(void);
	unsigned short		GetPort(void);

	
};

