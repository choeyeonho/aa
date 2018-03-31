#pragma once
/*
작성자 : 최연호
날  짜 : 2018-03-20
설  명 : 여러 프로세스에서 하나의 메모리에 접근하여 사용하거나 메모리를 할당하는 클레스

처음 메모리 0부터는 '\0'을 만날떄까지 계속 ServerInfo메모리를 저장할 예정
그럼 이 Serverinfo메모리를 통해서 사용
*/

#include <Windows.h>
#include "CommonHeader.h"
#include "SharedObject.h"


//< 아래것은 예제
#define LOBBYSERVER		0
#define LOGINSERVER		1
#define DBSERVER			2

//< 서버 인포 구조체
struct ST_MEMORY_INFO
{
	int _processNumber;
	int _startMemory;
	int _EndMemory;
};

class CSharedMemory
{
private:
	int					m_nTotalMemorySize;	//< 총 할당받는 메모리 사이즈

	int					m_nMemoryInfoCount;	//< 서버 정보 갯수

	HANDLE				m_hMemoryHandle;		//< 핸들 정보

	char*				m_pMemoryStart;
public:
	CSharedMemory(void);
	~CSharedMemory(void);

	//<생성 초기화
	bool					InitMakeMemory(LPCWSTR _pMemoryName,int _nMemorySize);
	
	//<읽기 초기화
	bool					InitReadMemory(LPCWSTR _pMemoryName);
	
	//< 처음에 서버앞 부분을 등록합니다.
	void					RegisterServerInfo(int _nProcessNumber, int _nStartMemory, int _nEndMemory);

	//< 리턴값으로 시작주소, 마지막 주소를 받고 이걸로 사이즈를 계산이 가능합니다.
	//< targetAddress에 char*를 넣어주면 그만큼 사용 가능
	//< 그럼 처음 사이즈를 아는 방법은 
	ST_MEMORY_INFO		ExcuteMemory( char* _pTargetAddress,int _nProcessNumber );
	
	//< sharedMemory의 제일 앞 부분을 얻어온다 ( 얼만큼 읽을 것인지 )
	char*				GetMemoryPointer(const int _nReadSize);

};

