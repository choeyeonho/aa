
/*
�ۼ���	: �ֿ�ȣ
��  ¥	: 2018-03-27
��  ��	: �� ������ ������ �Ǵ� ���� Ŭ����
		  
		  ������ ���� �ܼ��� �۾�
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



	//< ���� �ε����� Set & Get
	void				SetIndex(const int _nIndex);
	int					GetIndex();

	//< ���ø��� ��Ʈ ���
	void					RegisterCompletionPort();
};

