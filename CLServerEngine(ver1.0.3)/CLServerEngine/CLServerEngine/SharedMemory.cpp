#include "SharedMemory.h"


CSharedMemory::CSharedMemory(void) : m_hMemoryHandle(NULL), m_pMemoryStart(nullptr)
{
}


CSharedMemory::~CSharedMemory(void)
{
	SAFE_CLOSE_HANDLE(m_hMemoryHandle);	
}
//<생성 초기화
bool				CSharedMemory::InitMakeMemory(LPCWSTR _pMemoryName,int _nMemorySize)
{
	m_hMemoryHandle = CreateFileMapping(
		INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		0,						
		_nMemorySize,					//< 생성할 사이즈
		_pMemoryName);				//< 이름		

	if( m_hMemoryHandle == NULL )
	{
		//< Log 추가 할것 CYH_ADD_LOG
		// AddLog->Write( RedWrite, _T(" Failed create the shared memory : %d"),GetLastError() );
		return false;
	}	

	return true;
}

//<읽기 초기화
bool				CSharedMemory::InitReadMemory(LPCWSTR _pMemoryName)
{
	m_hMemoryHandle = OpenFileMapping(FILE_MAP_ALL_ACCESS, false, _pMemoryName);

	if( m_hMemoryHandle == NULL )
	{
		//< Log 추가 할것 CYH_ADD_LOG
		// AddLog->Write( RedWrite, _T(" Failed open the shared memory(%s) : %d"),_pMemoryName,GetLastError() );
		return false;
	}


	return true;
}

//< 처음에 서버앞 부분을 등록합니다.
void				CSharedMemory::RegisterServerInfo(int _nProcessNumber, int _nStartMemory, int _nEndMemory)
{
	//< SharedMemory가 설정된 후에 들어와야 하는데 그렇지 않다면 패스한다
	if( m_hMemoryHandle == NULL || m_pMemoryStart == nullptr )
	{
		//< Log 추가 할것 CYH_ADD_LOG
		// AddLog->Write( RedWrite, _T("you have to set shared memory"));
		return;
	}

	//< 각각의 서버 인포 지정
	ST_MEMORY_INFO	stMemInfo;
	
	stMemInfo._processNumber	= _nProcessNumber;
	stMemInfo._startMemory		= _nStartMemory;
	stMemInfo._EndMemory		= _nEndMemory;
	
	//< 지정
	memcpy_s(m_pMemoryStart + ( sizeof(ST_MEMORY_INFO) * m_nMemoryInfoCount ),sizeof(ST_MEMORY_INFO),(void*)&stMemInfo,sizeof(ST_MEMORY_INFO));

	//< 끝번호 지정하면서 갯수도 증가
	memcpy_s(m_pMemoryStart + (sizeof(ST_MEMORY_INFO) * ++m_nMemoryInfoCount ), 1, '\0', 1);		
}

//< 리턴값으로 시작주소, 마지막 주소를 받고 이걸로 사이즈를 계산이 가능합니다.
//< targetAddress에 char*를 넣어주면 그만큼 사용 가능
//< 그럼 처음 사이즈를 아는 방법은 
ST_MEMORY_INFO	CSharedMemory::ExcuteMemory( char* _pTargetAddress,int _nProcessNumber )
{
	ST_MEMORY_INFO	stReturnMemInfo;
	ST_MEMORY_INFO*	pStMemInfo		= nullptr;	
	int				nIndex			= 0;

	//< -1이라면 읽지 못하는 값임으로 패스
	stReturnMemInfo._processNumber		= -1;

	while(1)
	{
		//< 만약 위치가 서버 정보 마지막이라면 nullptr을 리턴한다.
		if( strcmp( m_pMemoryStart + ( nIndex * sizeof(ST_MEMORY_INFO) ),'\0') == 0 )
			return stReturnMemInfo;

		//< 정보 로딩
		pStMemInfo = ((ST_MEMORY_INFO*)m_pMemoryStart+( nIndex * sizeof(ST_MEMORY_INFO) ));
		
		if( pStMemInfo->_processNumber == _nProcessNumber )
		{
			//< TargetAddress를 시작위치로 이동시켜준다.
			_pTargetAddress = m_pMemoryStart + pStMemInfo->_startMemory;
			return *pStMemInfo;
		}
	
		nIndex++;
	}

	//< 뭣도 아니면 패스
	return stReturnMemInfo;
}

//< sharedMemory의 제일 앞 부분을 얻어온다 ( 얼만큼 읽을 것인지 )
char*				CSharedMemory::GetMemoryPointer(const int _nReadSize)
{
	//< 이미 정보가 있다면 리턴합니다.
	if( m_pMemoryStart != nullptr )
		return m_pMemoryStart;

	//< 메모리 포인터 확인
	m_pMemoryStart = (char*)MapViewOfFile(m_hMemoryHandle,FILE_MAP_ALL_ACCESS,0,0,_nReadSize);

	if( m_pMemoryStart == NULL )
	{		
		//< Log 추가 할것 CYH_ADD_LOG
		// AddLog->Write( RedWrite, _T(" Failed Get shared memory pointer : %d"),GetLastError() );
		return nullptr;
	}

	return m_pMemoryStart;
}