/*
�ۼ��� : �ֿ�ȣ 
��  ¥ : 2018-03-27
��  �� : Ŀ������ �⺻�� �Ǵ� Ŭ����
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
	//< Ŀ���Ϳ� ��Ŀ����(��Ŀ���ʹ� socket�� ������ �Ǳ� ������ ���� .. )
	//< ������ ����Ϳ��� ��Ŀ���Ͱ� �� ���� Ȱ���ؾ� �ϰ� ����͸� ����
	//< Ŭ�������� �Ұ� ���� ����� �ƴ� �׷��߸� �ϴ�!
	CConnecter*				m_Connecter;	

	//< Ŭ���̾�Ʈ�� ������ ���� ���� �ϳ��� ������ ������ �˴ϴ�.
	//< �׷��� �����ϳ������� ���� �ʿ䰡 �����ϴ�.
	CNetworkUnit*				m_pNetworkUnit;

	//< �ڱ� �ڽſ� ���� ����
	CUser*					m_myInfo;

	//< ����ó
	std::vector<CDispatcher*>	m_dispatchers;


public:
	CConnecterBase(const int _dispatcherCount, const int _maxUser);
	virtual ~CConnecterBase(void);

	virtual BOOL Initializing(const int _nIndex, char* _pIP, const int _nPort, const int _nSendBufSize,const int _nRecvBufSize);

	//< ������ ��ƾ �� 1ȸ
	virtual HRESULT		Create();

	//< ���� ����
	virtual BOOL			ServerShutDown();

	//< ���� ����
	virtual int			Run() override;

};