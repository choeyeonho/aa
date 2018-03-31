/*
작성자 : 최연호 
날  짜 : 2018-03-27
내  용 : 커넥터의 기본이 되는 클레스
*/

#pragma once

#include "CommonHeader.h"
#include "Server.h"
#include "Connecter.h"
#include "Dispatcher.h"
#include "NetworkUnit.h"

class CConnecterBase : public CServer
{
protected	:
	//< 커넥터와 디스커넥터(디스커넥터는 socket만 닫으면 되기 때문에 굳이 .. )
	//< 오히려 어셉터에서 디스커넥터가 더 많이 활용해야 하고 어셉터를 위한
	//< 클레스여야 할거 같은 기모찌 아니 그래야만 하는!
	CConnecter*				m_Connecter;	

	//< 클라이언트는 서버에 대한 소켓 하나만 가지고 있으면 됩니다.
	//< 그러니 세션하나단위를 가질 필요가 없습니다.
	CNetworkUnit*				m_pNetworkUnit;

	//< 자기 자신에 대한 정보
	CUser*					m_myInfo;

	//< 디스패처
	std::vector<CDispatcher*>	m_dispatchers;


public:
	CConnecterBase(const int _dispatcherCount, const int _maxUser);
	virtual ~CConnecterBase(void);

	virtual BOOL Initializing(const int _nIndex, char* _pIP, const int _nPort, const int _nSendBufSize,const int _nRecvBufSize);

	//< 쓰레드 루틴 전 1회
	virtual HRESULT		Create();

	//< 서버 종료
	virtual BOOL			ServerShutDown();

	//< 서버 루프
	virtual int			Run() override;

};