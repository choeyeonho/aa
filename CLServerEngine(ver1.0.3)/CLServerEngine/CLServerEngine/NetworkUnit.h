/*
작성자		: 최연호
날  짜		: 2018-03-28
Description	: 하나의 네트워크를 가능케 해주는 Unit
			  이 곳에서는 기초적인 네트워크 셋팅 작업등을 해줍니다.
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
	//< 이 Unit의 주체가 되는 Server의 포인터 주소
	CServer*				m_pServerOwner;

	//< 소켓 정보
	CSockAddr*			m_SockAddr;
	
private:
	CQueueBuffer*			m_pSendBuffer;
	CQueueBuffer*			m_pRecvBuffer;
	
	//< 오버레피드 정보
private:
	stOverlappedGroup		m_overlapped;

public:

	CQueueBuffer*			GetSendBuffer();
	CQueueBuffer*			GetRecvBuffer();

	//< 주체를 설정
	void					SetServer(CServer* _pServer );
	CServer*				GetServer();

	//< 소켓 초기화
	BOOL					InitSocket(const int _sendBufferSize, const int _recvBufferSize);

	//< 버퍼 초기화
	BOOL					InitBuffer(const int _sendBufferSize, const int _recvBufferSize);

	//< 디스커넥트
	BOOL					Disconnect();

	//< 바인딩 작업
	BOOL					Binding(char* _pIP, const int _nPort);	//< 클라
	BOOL					Binding(const int _nPort);				//< 서버

	//< 리스닝 작업
	BOOL					Listening(const int _nBackLog);

	//< send
	void					Send(BUF_PACKET_TYPE _buf);


	stOverlappedGroup		GetOverlappedGroup();

	CNetworkUnit(void);
	~CNetworkUnit(void);
};

