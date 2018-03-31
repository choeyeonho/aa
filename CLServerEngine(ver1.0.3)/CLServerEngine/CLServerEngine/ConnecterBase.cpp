#include "ConnecterBase.h"


CConnecterBase::CConnecterBase(const int _dispatcherCount, const int _maxUser)
{
	RegisterCompletionPort();

	//< 등록된 수만큼 디스패쳐 등록
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
//< 이승하 김규리
BOOL CConnecterBase::Initializing(const int _nIndex, char* _pIP, const int _nPort, const int _nSendBufSize,const int _nRecvBufSize)
{
	//< 소켓 초기화
	m_pNetworkUnit = new CNetworkUnit();	
	m_pNetworkUnit->InitSocket(_nSendBufSize,_nRecvBufSize);

	//< 네트워크 유닛의 주체가 누구인지 설정
	m_pNetworkUnit->SetServer(this);

	//< 서버 인덱스 설정
	m_Index		 = _nIndex;

	//< 컴플리션 포트에 연결 ( Comlpetion Key는 자기자신을 넣어줍니다. )
	m_Completion->AssociateSocket(m_pNetworkUnit->GetSocket(),(DWORD)this);

	//< 바인딩
	m_pNetworkUnit->Binding(_pIP,_nPort);

	//< 커넥팅 < 추가작업 필요 >
	m_Connecter = new CConnecter();
	
	return TRUE;
}

//< 쓰레드 루틴 전 1회
HRESULT		CConnecterBase::Create()
{

	return TRUE;
}

//< 서버 종료
BOOL			CConnecterBase::ServerShutDown()
{
	return TRUE;
}
int			CConnecterBase::Run()
{
	//< 서버 런
	CServer::Run();

	return 0;
}