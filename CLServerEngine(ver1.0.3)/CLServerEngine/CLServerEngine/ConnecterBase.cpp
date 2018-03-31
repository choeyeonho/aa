#include "ConnecterBase.h"


CConnecterBase::CConnecterBase(const int _dispatcherCount, const int _maxUser)
{
	RegisterCompletionPort();

	//< ��ϵ� ����ŭ ������ ���
	for(int i = 0 ; i < _dispatcherCount; i++)
	{
		m_dispatchers.push_back( new CDispatcher(_maxUser) );
		m_dispatchers[i]->StartThread();
	}	
}

CConnecterBase::~CConnecterBase(void)
{
	m_dispatchers.clear();
}
//< �̽��� ��Ը�
BOOL CConnecterBase::Initializing(const int _nIndex, char* _pIP, const int _nPort, const int _nSendBufSize,const int _nRecvBufSize)
{
	//< ���� �ʱ�ȭ
	m_pNetworkUnit = new CNetworkUnit();	
	m_pNetworkUnit->InitSocket(_nSendBufSize,_nRecvBufSize);

	//< ��Ʈ��ũ ������ ��ü�� �������� ����
	m_pNetworkUnit->SetServer(this);

	//< ���� �ε��� ����
	m_Index		 = _nIndex;

	//< ���ø��� ��Ʈ�� ���� ( Comlpetion Key�� �ڱ��ڽ��� �־��ݴϴ�. )
	m_Completion->AssociateSocket(m_pNetworkUnit->GetSocket(),(DWORD)this);

	//< ���ε�
	m_pNetworkUnit->Binding(_pIP,_nPort);

	//< Ŀ���� < �߰��۾� �ʿ� >
	m_Connecter = new CConnecter();
	
	return TRUE;
}

//< ������ ��ƾ �� 1ȸ
HRESULT		CConnecterBase::Create()
{

	return TRUE;
}

//< ���� ����
BOOL			CConnecterBase::ServerShutDown()
{
	return TRUE;
}
int			CConnecterBase::Run()
{
	//< ���� ��
	CServer::Run();

	return 0;
}