#include "SharedMemory.h"


CSharedMemory::CSharedMemory(void) : m_hMemoryHandle(NULL), m_pMemoryStart(nullptr)
{
}


CSharedMemory::~CSharedMemory(void)
{
	SAFE_CLOSE_HANDLE(m_hMemoryHandle);	
}
//<���� �ʱ�ȭ
bool				CSharedMemory::InitMakeMemory(LPCWSTR _pMemoryName,int _nMemorySize)
{
	m_hMemoryHandle = CreateFileMapping(
		INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		0,						
		_nMemorySize,					//< ������ ������
		_pMemoryName);				//< �̸�		

	if( m_hMemoryHandle == NULL )
	{
		//< Log �߰� �Ұ� CYH_ADD_LOG
		// AddLog->Write( RedWrite, _T(" Failed create the shared memory : %d"),GetLastError() );
		return false;
	}	

	return true;
}

//<�б� �ʱ�ȭ
bool				CSharedMemory::InitReadMemory(LPCWSTR _pMemoryName)
{
	m_hMemoryHandle = OpenFileMapping(FILE_MAP_ALL_ACCESS, false, _pMemoryName);

	if( m_hMemoryHandle == NULL )
	{
		//< Log �߰� �Ұ� CYH_ADD_LOG
		// AddLog->Write( RedWrite, _T(" Failed open the shared memory(%s) : %d"),_pMemoryName,GetLastError() );
		return false;
	}


	return true;
}

//< ó���� ������ �κ��� ����մϴ�.
void				CSharedMemory::RegisterServerInfo(int _nProcessNumber, int _nStartMemory, int _nEndMemory)
{
	//< SharedMemory�� ������ �Ŀ� ���;� �ϴµ� �׷��� �ʴٸ� �н��Ѵ�
	if( m_hMemoryHandle == NULL || m_pMemoryStart == nullptr )
	{
		//< Log �߰� �Ұ� CYH_ADD_LOG
		// AddLog->Write( RedWrite, _T("you have to set shared memory"));
		return;
	}

	//< ������ ���� ���� ����
	ST_MEMORY_INFO	stMemInfo;
	
	stMemInfo._processNumber	= _nProcessNumber;
	stMemInfo._startMemory		= _nStartMemory;
	stMemInfo._EndMemory		= _nEndMemory;
	
	//< ����
	memcpy_s(m_pMemoryStart + ( sizeof(ST_MEMORY_INFO) * m_nMemoryInfoCount ),sizeof(ST_MEMORY_INFO),(void*)&stMemInfo,sizeof(ST_MEMORY_INFO));

	//< ����ȣ �����ϸ鼭 ������ ����
	memcpy_s(m_pMemoryStart + (sizeof(ST_MEMORY_INFO) * ++m_nMemoryInfoCount ), 1, '\0', 1);		
}

//< ���ϰ����� �����ּ�, ������ �ּҸ� �ް� �̰ɷ� ����� ����� �����մϴ�.
//< targetAddress�� char*�� �־��ָ� �׸�ŭ ��� ����
//< �׷� ó�� ����� �ƴ� ����� 
ST_MEMORY_INFO	CSharedMemory::ExcuteMemory( char* _pTargetAddress,int _nProcessNumber )
{
	ST_MEMORY_INFO	stReturnMemInfo;
	ST_MEMORY_INFO*	pStMemInfo		= nullptr;	
	int				nIndex			= 0;

	//< -1�̶�� ���� ���ϴ� �������� �н�
	stReturnMemInfo._processNumber		= -1;

	while(1)
	{
		//< ���� ��ġ�� ���� ���� �������̶�� nullptr�� �����Ѵ�.
		if( strcmp( m_pMemoryStart + ( nIndex * sizeof(ST_MEMORY_INFO) ),'\0') == 0 )
			return stReturnMemInfo;

		//< ���� �ε�
		pStMemInfo = ((ST_MEMORY_INFO*)m_pMemoryStart+( nIndex * sizeof(ST_MEMORY_INFO) ));
		
		if( pStMemInfo->_processNumber == _nProcessNumber )
		{
			//< TargetAddress�� ������ġ�� �̵������ش�.
			_pTargetAddress = m_pMemoryStart + pStMemInfo->_startMemory;
			return *pStMemInfo;
		}
	
		nIndex++;
	}

	//< ���� �ƴϸ� �н�
	return stReturnMemInfo;
}

//< sharedMemory�� ���� �� �κ��� ���´� ( ��ŭ ���� ������ )
char*				CSharedMemory::GetMemoryPointer(const int _nReadSize)
{
	//< �̹� ������ �ִٸ� �����մϴ�.
	if( m_pMemoryStart != nullptr )
		return m_pMemoryStart;

	//< �޸� ������ Ȯ��
	m_pMemoryStart = (char*)MapViewOfFile(m_hMemoryHandle,FILE_MAP_ALL_ACCESS,0,0,_nReadSize);

	if( m_pMemoryStart == NULL )
	{		
		//< Log �߰� �Ұ� CYH_ADD_LOG
		// AddLog->Write( RedWrite, _T(" Failed Get shared memory pointer : %d"),GetLastError() );
		return nullptr;
	}

	return m_pMemoryStart;
}