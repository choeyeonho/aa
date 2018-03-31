/*
�ۼ���		: �ֿ�ȣ
��  ¥		: 2018-03-28
Description	: �ϳ��� ��Ʈ��ũ�� ������ ���ִ� Unit
			  �� �������� �������� ��Ʈ��ũ ���� �۾����� ���ݴϴ�.
*/
#pragma once

#include "Server.h"
#include "Sock.h"
#include "SockAddr.h"
#include "QueueBuffer.h"

struct stOverlappedGroup
{
	WSAOVERLAPPED			m_ConnectOverlapped;
	WSAOVERLAPPED			m_ReadOverlapped;
	WSAOVERLAPPED			m_WriteOverlapped;
	WSAOVERLAPPED			m_DisconnectOverlapped;
};

class CNetworkUnit : public CSock
{
private:
	//< �� Unit�� ��ü�� �Ǵ� Server�� ������ �ּ�
	CServer*				m_pServerOwner;

	//< ���� ����
	CSockAddr*			m_SockAddr;
	
private:
	CQueueBuffer*			m_pSendBuffer;
	CQueueBuffer*			m_pRecvBuffer;
	
	//< �������ǵ� ����
private:
	stOverlappedGroup		m_overlapped;

public:

	CQueueBuffer*			GetSendBuffer();
	CQueueBuffer*			GetRecvBuffer();

	//< ��ü�� ����
	void					SetServer(CServer* _pServer );
	CServer*				GetServer();

	//< ���� �ʱ�ȭ
	BOOL					InitSocket(const int _sendBufferSize, const int _recvBufferSize);

	//< ���� �ʱ�ȭ
	BOOL					InitBuffer(const int _sendBufferSize, const int _recvBufferSize);

	//< ��Ŀ��Ʈ
	BOOL					Disconnect();

	//< ���ε� �۾�
	BOOL					Binding(char* _pIP, const int _nPort);	//< Ŭ��
	BOOL					Binding(const int _nPort);				//< ����

	//< ������ �۾�
	BOOL					Listening(const int _nBackLog);

	//< send
	void					Send(BUF_PACKET_TYPE _buf);


	stOverlappedGroup		GetOverlappedGroup();

	CNetworkUnit(void);
	~CNetworkUnit(void);
};

