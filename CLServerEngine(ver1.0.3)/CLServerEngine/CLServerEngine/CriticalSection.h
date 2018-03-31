/*
작성자 : 최연호
날  짜 : 2018-03-27
내  용 : 크리티컬 세에에에엑션
*/
#pragma once

#include <Windows.h>

class CriticalSection
{
private:
	CRITICAL_SECTION m_cs;

public:
	CriticalSection(void);
	~CriticalSection(void);

	void Enter();
	void Leave();

	
};

//< 각 클레스에서 사용할떄 criticalsection의 변수명은 m_cs로 지었을때 사용 가능
#define ENTER m_cs.Enter()
#define LEAVE m_cs.Leave()