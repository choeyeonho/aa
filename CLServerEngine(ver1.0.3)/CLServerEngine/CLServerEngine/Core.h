#pragma once
/*
제작자 : 최연호
작성일 : 2018-03-26
내  용 : 하나의 코어가 가지는 쓰레드들의 정보를 가지고 컨트롤 하는 클레스
*/

#include <Windows.h>
#include <vector>
#include <process.h>

class CCore
{
private:
	//< 이 코어에 있는 쓰레드들의 핸들을 저장하고 있습니다.
	std::vector<HANDLE>		m_vHandleList;

	int						m_nCoreCount;
	int						m_nCoreNumber;	//< 이 코어의 넘버 값
public:

	//< 해당 코어에 쓰레드를 추가 합니다.
	void						AddThread(HANDLE _handle);

	//< 해당 코어에 쓰레드를 제거 합니다.
	void						DelThread(HANDLE _handle);
	
	//< 모든 Thread 종료 
	void						EndThread();

	//< 모든 Thread 일시 정지
	void						StopThread();
	
	//< 모든 Thread 재시작
	void						ActiveThread();

	
	//< Get 함수
	std::vector<HANDLE>		GetHandleList();
	int						GetHandleCount();

	//< Set함수
	void						SetCoreNumber(const int _nCoreNumber);

	CCore();
	~CCore(void);
};

