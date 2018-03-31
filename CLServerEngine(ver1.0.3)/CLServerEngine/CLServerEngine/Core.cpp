#include "Core.h"


CCore::CCore() : m_nCoreCount(0), m_nCoreNumber(0)
{

}


CCore::~CCore(void)
{

}

//< �ش� �ھ �����带 �߰� �մϴ�.
void						CCore::AddThread(HANDLE _handle)
{
	m_vHandleList.push_back(_handle);
	m_nCoreCount++;
}

//< �ش� �ھ �����带 ���� �մϴ�.
void						CCore::DelThread(HANDLE _handle)
{
	std::vector<HANDLE>::const_iterator iter;

	for( iter = m_vHandleList.begin(); iter != m_vHandleList.end(); ++iter)
	{
		if( *(iter) == _handle )
		{
			m_vHandleList.erase(iter);
			m_nCoreCount--;
			break;
		}
	}
}

//< ��� Thread ���� 
//< �����ϸ� �ش� �����忡�� return�� ���� �����ϰ� �ϴ°��� ���� �����ϴ�.�ƴ� �׷��߸� �մϴ�.
//< ���輺�� �������� �մϴ�. ������ �����ϴ� ���� ������ ���ο��� ����ϴ� �޸� ���� x
//< �׷��� ����� �Ӵϴ�.
void						CCore::EndThread()
{
	std::vector<HANDLE>::const_iterator iter;

	for( iter = m_vHandleList.begin(); iter != m_vHandleList.end(); ++iter)
	{
		//< �������� ( ���輺 ��û ���� )
		TerminateThread(*(iter),0);		
		CloseHandle( *(iter) );
	}
}

//< ��� Thread �Ͻ� ���� 
void						CCore::StopThread()
{
	std::vector<HANDLE>::const_iterator iter;

	for( iter = m_vHandleList.begin(); iter != m_vHandleList.end(); ++iter)
	{
		
		SuspendThread( *(iter) );
	}
}

//< ��� Thread �����
void						CCore::ActiveThread()
{
	std::vector<HANDLE>::const_iterator iter;

	for( iter = m_vHandleList.begin(); iter != m_vHandleList.end(); ++iter)
	{		
		ResumeThread( *(iter) );
	}
}

//< Get �Լ�
std::vector<HANDLE>		CCore::GetHandleList()
{
	return m_vHandleList;
}

int						CCore::GetHandleCount()
{
	return m_nCoreCount;
}
void						CCore::SetCoreNumber(const int _nCoreNumber)
{
	m_nCoreNumber = _nCoreNumber;
}