/*
작성자 : 최연호
날  짜 : 2018-03-26
설  명 : 쓰레드를 관리하는 클레스
변  경 : < 최연호 , 2018-03-26 >
		쓰레드가 들어오면 그 쓰레드에 대한 코어 지정을 해줍니다. 
		코어 지정은 cpu개수를 받고 지정 갯수를 한개씩 올리며 루프를 돕니다
		이렇게 하는 이유는 window10은 물리적인 cpu에게 몰빵해주는 옵션이 생겨
		어떠한 환경에서도 cpu에 쓰레드를 균등이 배분하기 위해서 입니다.
*/

#pragma once

#include "CommonHeader.h"
#include "Thread.h"
#include "Core.h"
#include <map>
#include <process.h>

class CThread;

class CThreadManager
{
private:
	CCore*						m_Cores;			//< Core옵션 정보 지정
	int							m_processerCount; //< cpu 갯수
	int							m_nNowCore;		//< 들어갈 위치의 코어 값	
	int							m_nMaxCore;		//< 최대 값
private:	
	CThreadManager();
	~CThreadManager();
	//< Thread Single ton
	static CThreadManager*			m_pInstance;
public:	
	static CThreadManager*			GetInstance();

private:
	std::map<HANDLE, CThread*>		m_mThreadList;

public:
	int							AddThread(HANDLE _handle, CThread* _thread);	
	HRESULT						DeleteThread(HANDLE _handle,int _nCoreNumber);
	
	//< 모든 쓰레드 중지
	HRESULT						AllSuspend();

	//< 쓰레드를 얻는다.
	CThread*						GetThread(HANDLE _handle);	

	//< 현재 작동중인 쓰레드 갯수
	DWORD						GetThreadCount();

	//< 어느 코어에 들어갈지 지정
	void							SetCore(HANDLE _handle);

	//------------------------ 아래의 함수들은 0~ProcessCount-1 까지 대입

	//< 해당 코어에 있는 모든 Thread 종료 
	void							EndThreadInCore(const int _nCoreNumber);

	//< 해당 코어에 있는 모든 Thread 일시 정지
	void							SuspendThreadInCore(const int _nCoreNumber);
	
	//< 해당 코어에 있는 모든 Thread 재시작
	void							ActiveThreadInCore(const int _nCoreNumber);
	

	//< 쓰레드 매니저 초기화
	void							Initializing();
	
};

//< 문자를 대문자집합은 상수 디파인과 햇갈릴수 있으니 앞에 S붙이고 네이밍
//< 코드 읽을때 위에서 붙어 읽으면 class읽기전에 설정이니 맨밑에
//< 문자적 치환이라고 할수 있지만 문제 나올수 있다고 난 생각
#define SThreadManager CThreadManager::GetInstance()