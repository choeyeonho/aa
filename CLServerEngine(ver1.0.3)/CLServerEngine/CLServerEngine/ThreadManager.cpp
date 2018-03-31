#include "ThreadManager.h"

CThreadManager* CThreadManager::m_pInstance = nullptr;

CThreadManager::CThreadManager(): m_Cores(nullptr), m_processerCount(0), m_nNowCore(0)
{

}

CThreadManager::~CThreadManager()
{
	SAFE_DELETE_ARRAY(m_Cores);
}
//< ������ �Ŵ��� �ʱ�ȭ
void							CThreadManager::Initializing()
{
	SYSTEM_INFO	sysinfo;
	GetSystemInfo( &sysinfo );

	m_Cores = new CCore[sysinfo.dwNumberOfProcessors];

	m_nMaxCore = sysinfo.dwNumberOfProcessors;

	//< �ѹ��� �о ����
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

	//< ����
	m_mThreadList.erase(_handle);

	//< Core������ ���� ���ݴϴ�.
	m_Cores[_nCoreNumber].DelThread(_handle);

	//< _beginthreadEx�� ���������� closehandle�� ȣ������ �ʽ��ϴ�.
	CloseHandle(_handle);
	return TRUE;
}
//< ��� ������ ����
HRESULT						CThreadManager::AllSuspend()
{
	for( std::map<HANDLE, CThread*>::const_iterator iter = m_mThreadList.begin(); 
		iter!= m_mThreadList.end(); iter++)
	{
		//������ ����
		if(iter->first == INVALID_HANDLE_VALUE)
			return FALSE;

		SuspendThread(iter->first);
	}
	return TRUE;
}
//< �����带 ��´�.
CThread*						CThreadManager::GetThread(HANDLE _handle)
{
	if ( _handle == INVALID_HANDLE_VALUE )
		return nullptr;

	return m_mThreadList[_handle];
}

//< ���� �۵����� ������ ����
DWORD						CThreadManager::GetThreadCount()
{
	return m_mThreadList.size();
}
//< ��� �ھ ���� ����
void							CThreadManager::SetCore(HANDLE _handle)
{	
	//< �����尡 �۵��� Core ����
	SetThreadAffinityMask(_handle, 1 << m_nNowCore );

	//< Core�� ����
	m_Cores[m_nNowCore].AddThread(_handle);

	//< ����
	m_nNowCore++;

	//< ����
	if( m_nNowCore >= m_nMaxCore )
		m_nNowCore = 0;
}

//< �ش� �ھ �ִ� ��� Thread ���� 
void							CThreadManager::EndThreadInCore(const int _nCoreNumber)
{
	//< �� ����� ���� �ùٸ��� �����Ŷ� �Ͼ��!
	//< �׸��� �ظ��ϸ� ���� ���ô�
	m_Cores[_nCoreNumber].EndThread();
}

//< �ش� �ھ �ִ� ��� Thread �Ͻ� ����
void							CThreadManager::SuspendThreadInCore(const int _nCoreNumber)
{
	//< �� ����� ���� �ùٸ��� �����Ŷ� �Ͼ��!
	m_Cores[_nCoreNumber].StopThread();
}

//< �ش� �ھ �ִ� ��� Thread �����
void							CThreadManager::ActiveThreadInCore(const int _nCoreNumber)
{
	//< �� ����� ���� �ùٸ��� �����Ŷ� �Ͼ��!
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