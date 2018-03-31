#include "ThreadManager.h"

CThreadManager* CThreadManager::m_pInstance = nullptr;

CThreadManager::CThreadManager(): m_Cores(nullptr), m_processerCount(0), m_nNowCore(0)
{

}

CThreadManager::~CThreadManager()
{
	SAFE_DELETE_ARRAY(m_Cores);
}
//< 쓰레드 매니저 초기화
void							CThreadManager::Initializing()
{
	SYSTEM_INFO	sysinfo;
	GetSystemInfo( &sysinfo );

	m_Cores = new CCore[sysinfo.dwNumberOfProcessors];

	m_nMaxCore = sysinfo.dwNumberOfProcessors;

	//< 한번씩 밀어서 지정
	for(UINT i = 0 ; i < sysinfo.dwNumberOfProcessors; i++)
		m_Cores[i].SetCoreNumber( 1 << i );
}
int							CThreadManager::AddThread(HANDLE _handle, CThread* _thread)
{
	if( _handle != INVALID_HANDLE_VALUE)
	{
		m_mThreadList.insert( std::pair<HANDLE, CThread*>(_handle, _thread));
		SetCore(_handle);
		return m_nNowCore;
	}
	return -1;
}
HRESULT						CThreadManager::DeleteThread(HANDLE _handle,int _nCoreNumber)
{
	if( _handle != INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	//< 삭제
	m_mThreadList.erase(_handle);

	//< Core에서도 삭제 해줍니다.
	m_Cores[_nCoreNumber].DelThread(_handle);

	//< _beginthreadEx는 내부적으로 closehandle을 호출하지 않습니다.
	CloseHandle(_handle);
	return TRUE;
}
//< 모든 쓰레드 중지
HRESULT						CThreadManager::AllSuspend()
{
	for( std::map<HANDLE, CThread*>::const_iterator iter = m_mThreadList.begin(); 
		iter!= m_mThreadList.end(); iter++)
	{
		//쓰레드 중지
		if(iter->first == INVALID_HANDLE_VALUE)
			return FALSE;

		SuspendThread(iter->first);
	}
	return TRUE;
}
//< 쓰레드를 얻는다.
CThread*						CThreadManager::GetThread(HANDLE _handle)
{
	if ( _handle == INVALID_HANDLE_VALUE )
		return nullptr;

	return m_mThreadList[_handle];
}

//< 현재 작동중인 쓰레드 갯수
DWORD						CThreadManager::GetThreadCount()
{
	return m_mThreadList.size();
}
//< 어느 코어에 들어갈지 지정
void							CThreadManager::SetCore(HANDLE _handle)
{	
	//< 쓰레드가 작동될 Core 선택
	SetThreadAffinityMask(_handle, 1 << m_nNowCore );

	//< Core에 대입
	m_Cores[m_nNowCore].AddThread(_handle);

	//< 증가
	m_nNowCore++;

	//< 조절
	if( m_nNowCore >= m_nMaxCore )
		m_nNowCore = 0;
}

//< 해당 코어에 있는 모든 Thread 종료 
void							CThreadManager::EndThreadInCore(const int _nCoreNumber)
{
	//< 난 당신이 값을 올바르게 넣을거라 믿어요!
	//< 그리고 왠만하면 쓰지 맙시다
	m_Cores[_nCoreNumber].EndThread();
}

//< 해당 코어에 있는 모든 Thread 일시 정지
void							CThreadManager::SuspendThreadInCore(const int _nCoreNumber)
{
	//< 난 당신이 값을 올바르게 넣을거라 믿어요!
	m_Cores[_nCoreNumber].StopThread();
}

//< 해당 코어에 있는 모든 Thread 재시작
void							CThreadManager::ActiveThreadInCore(const int _nCoreNumber)
{
	//< 난 당신이 값을 올바르게 넣을거라 믿어요!
	m_Cores[_nCoreNumber].ActiveThread();
}

CThreadManager*				CThreadManager::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new CThreadManager();
		m_pInstance->Initializing();
	}

	return m_pInstance;
}