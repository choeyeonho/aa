#pragma once
/*
�ۼ��� : �ֿ�ȣ
��  ¥ : 2018-03-27
��  �� : ���� ���� Ŭ����
*/
#include <WinSock2.h>

class CSock
{
protected:
	SOCKET		m_socket;			//< ����
	
public:
	CSock(void);	
	~CSock(void);
protected:
	SOCKET		CreateSocket();
	int			CloseSocket();

	//< �⺻ �����Լ���, �������� �Լ�
	BOOL			SetSocketOption();
	BOOL			SetSocketOption(DWORD	_optname, char* _val );

	//< ������ ���������� �ɼ�
	BOOL			SetLinger(BOOL _bGraceful);
	
public:
	SOCKET		GetSocket();
	void			SetSocket(SOCKET _socket);	//< Ŭ���̾�Ʈ ���ӽ� ������ ���� ����

	void			GetIP();
	void			GetLocalIP( char* const _pIP );
	WORD			GetLocalPort( void );

private:			
	//< c++���� �ڵ����� ���翬���ڰ� ������
	//< ���������� �����Ͽ� private�ȿ� �ξ� ���� ����

	//< ���� ����
	CSock (const CSock &);			
	CSock& operator= (const CSock &);
};

