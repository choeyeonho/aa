#include "Core.h"


CCore::CCore() : m_nCoreCount(0), m_nCoreNumber(0)
{

}


CCore::~CCore(void)
{

}

//< 해당 코어에 쓰레드를 추가 합니다.
void						CCore::AddThread(HANDLE _handle)
{
	m_vHandleList.push_back(_handle);
	m_nCoreCount++;
}

//< 해당 코어에 쓰레드를 제거 합니다.
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

//< 모든 Thread 종료 
//< 가능하면 해당 쓰레드에서 return을 만나 종료하게 하는것이 제일 좋습니다.아니 그래야만 합니다.
//< 위험성이 무지막지 합니다. 강제로 종료하다 보니 쓰레드 내부에서 사용하던 메모리 정리 x
//< 그래도 만들어 둡니당.
void						CCore::EndThread()
{
	std::vector<HANDLE>::const_iterator iter;

	for( iter = m_vHandleList.begin(); iter != m_vHandleList.end(); ++iter)
	{
		//< 강제종료 ( 위험성 엄청 높음 )
		TerminateThread(*(iter),0);		
		CloseHandle( *(iter) );
	}
}

//< 모든 Thread 일시 정지 
void						CCore::StopThread()
{
	std::vector<HANDLE>::const_iterator iter;

	for( iter = m_vHandleList.begin(); iter != m_vHandleList.end(); ++iter)
	{
		
		SuspendThread( *(iter) );
	}
}

//< 모든 Thread 재시작
void						CCore::ActiveThread()
{
	std::vector<HANDLE>::const_iterator iter;

	for( iter = m_vHandleList.begin(); iter != m_vHandleList.end(); ++iter)
	{		
		ResumeThread( *(iter) );
	}
}

//< Get 함수
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