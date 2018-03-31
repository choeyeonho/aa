/*
�ۼ��� : �ֿ�ȣ
��  ¥ : 2018-03-27
��  �� : ũ��Ƽ�� ������������
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

//< �� Ŭ�������� ����ҋ� criticalsection�� �������� m_cs�� �������� ��� ����
#define ENTER m_cs.Enter()
#define LEAVE m_cs.Leave()