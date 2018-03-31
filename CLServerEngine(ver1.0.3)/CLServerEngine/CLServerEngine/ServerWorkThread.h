/*
작성자 : 최연호
날  짜 : 2018-03-29
내  용 : 각 서버의 IOCP상태를 검사하여 그에 해당하는 일을 진행
*/
#pragma once

#include "Thread.h"

class CServerWorkThread : public CThread
{
private:
	int					m_nNumberOfThread;

public:
	CServerWorkThread(const int _nNumberOfThread);
	virtual	~CServerWorkThread(void);


	virtual HRESULT Create() override;

	virtual int Run() override;


};

