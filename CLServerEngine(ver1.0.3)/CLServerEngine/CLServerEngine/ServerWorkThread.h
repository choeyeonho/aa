/*
�ۼ��� : �ֿ�ȣ
��  ¥ : 2018-03-29
��  �� : �� ������ IOCP���¸� �˻��Ͽ� �׿� �ش��ϴ� ���� ����
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

