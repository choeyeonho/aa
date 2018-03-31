#include "Server.h"


CServer::CServer(void) : m_Index(0), m_Completion(nullptr)
{
}


CServer::~CServer(void)
{
}

//< 서버 인덱스를 Set & Get
void		CServer::SetIndex(const int _nIndex)
{
	m_Index = _nIndex;
}
int		CServer::GetIndex()
{
	return m_Index;
}
//< 컴플리션 포트 등록
void		CServer::RegisterCompletionPort()
{
	//< 기본개수
	m_Completion = new CIOCompletionPort();
}