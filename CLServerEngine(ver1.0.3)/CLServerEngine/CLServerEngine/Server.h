
/*
작성자	: 최연호
날  짜	: 2018-03-27
내  용	: 각 서버의 기준이 되는 상위 클레스
		  
		  지금은 그저 단순한 작업
*/

#pragma once

#include "Thread.h"
#include "IOCompletionPort.h"


class CServer : public CThread
{
protected:
	int					m_Index;
	CIOCompletionPort*		m_Completion;
	
public:
	
	CServer(void);
	~CServer(void);



	//< 서버 인덱스를 Set & Get
	void				SetIndex(const int _nIndex);
	int					GetIndex();

	//< 컴플리션 포트 등록
	void					RegisterCompletionPort();
};

