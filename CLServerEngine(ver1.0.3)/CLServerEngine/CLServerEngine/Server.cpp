#include "Server.h"


CServer::CServer(void) : m_Index(0), m_Completion(nullptr)
{
}


CServer::~CServer(void)
{
}

//< ���� �ε����� Set & Get
void		CServer::SetIndex(const int _nIndex)
{
	m_Index = _nIndex;
}
int		CServer::GetIndex()
{
	return m_Index;
}
//< ���ø��� ��Ʈ ���
void		CServer::RegisterCompletionPort()
{
	//< �⺻����
	m_Completion = new CIOCompletionPort();
}