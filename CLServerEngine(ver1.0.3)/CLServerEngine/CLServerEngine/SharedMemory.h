#pragma once
/*
�ۼ��� : �ֿ�ȣ
��  ¥ : 2018-03-20
��  �� : ���� ���μ������� �ϳ��� �޸𸮿� �����Ͽ� ����ϰų� �޸𸮸� �Ҵ��ϴ� Ŭ����

ó�� �޸� 0���ʹ� '\0'�� ���������� ��� ServerInfo�޸𸮸� ������ ����
�׷� �� Serverinfo�޸𸮸� ���ؼ� ���
*/

#include <Windows.h>
#include "CommonHeader.h"
#include "SharedObject.h"


//< �Ʒ����� ����
#define LOBBYSERVER		0
#define LOGINSERVER		1
#define DBSERVER			2

//< ���� ���� ����ü
struct ST_MEMORY_INFO
{
	int _processNumber;
	int _startMemory;
	int _EndMemory;
};

class CSharedMemory
{
private:
	int					m_nTotalMemorySize;	//< �� �Ҵ�޴� �޸� ������

	int					m_nMemoryInfoCount;	//< ���� ���� ����

	HANDLE				m_hMemoryHandle;		//< �ڵ� ����

	char*				m_pMemoryStart;
public:
	CSharedMemory(void);
	~CSharedMemory(void);

	//<���� �ʱ�ȭ
	bool					InitMakeMemory(LPCWSTR _pMemoryName,int _nMemorySize);
	
	//<�б� �ʱ�ȭ
	bool					InitReadMemory(LPCWSTR _pMemoryName);
	
	//< ó���� ������ �κ��� ����մϴ�.
	void					RegisterServerInfo(int _nProcessNumber, int _nStartMemory, int _nEndMemory);

	//< ���ϰ����� �����ּ�, ������ �ּҸ� �ް� �̰ɷ� ����� ����� �����մϴ�.
	//< targetAddress�� char*�� �־��ָ� �׸�ŭ ��� ����
	//< �׷� ó�� ����� �ƴ� ����� 
	ST_MEMORY_INFO		ExcuteMemory( char* _pTargetAddress,int _nProcessNumber );
	
	//< sharedMemory�� ���� �� �κ��� ���´� ( ��ŭ ���� ������ )
	char*				GetMemoryPointer(const int _nReadSize);

};

