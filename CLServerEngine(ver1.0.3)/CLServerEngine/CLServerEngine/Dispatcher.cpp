#include "Dispatcher.h"


CDispatcher::CDispatcher(const int _maxUser)
{	
	m_vUserList.reserve(_maxUser);
}
CDispatcher::~CDispatcher(void)
{
	m_vUserList.clear();
}

int CDispatcher::Run()
{
	CNetworkUnit*							tempUnit;
	CUser*								tempUser;
	std::vector<CUser*>::const_iterator		tempiter;
	std::vector<CUser*>					tempVec;
	BUF_PACKET_TYPE						tempBuf;

	while(1)
	{
		//< ������ ó��
		ENTER;
		tempVec = m_vUserList;
		LEAVE;

		for( tempiter = tempVec.begin(); tempiter != tempVec.end(); )
		{
			tempUser = *(tempiter);
			tempUnit = tempUser->GetUnit();

			//< readBuf�� SendBuf�� �޾Ƽ� ó���մϴ�.
			tempBuf = tempUnit->GetRecvBuffer()->Popdata();
			if( tempBuf._pSize != nullptr )
			{
				//< Ŀ�ǵ� �ѹ��� ���ϱ� +2�� queueBuffer���� ������ �����ϰ� �ɴϴ�.
				m_mapiter = m_commandList.find(*((WORD*)tempBuf._pData+0));

				//< ����
				if( m_mapiter != m_commandList.end() )				
					(*m_mapiter).second(tempBuf,tempUser);

			}

			tempBuf = tempUnit->GetSendBuffer()->Popdata();

			if( tempBuf._pSize != nullptr )
				tempUnit->Send(tempBuf);


			if( tempiter != tempVec.end() )
				tempiter++;
		}
	}

	return 0;
}
void CDispatcher::PushUser(CUser* _user)
{
	if( _user != nullptr )
		m_vUserList.push_back(_user);
}
std::map<DWORD,PROTOCOL_TYPE>	CDispatcher::GetCommandList()
{
	return m_commandList;
}
std::vector<CUser*>			CDispatcher::GetvUserList()
{
	return m_vUserList;
}