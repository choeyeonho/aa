/*
�ۼ��� : �ֿ�ȣ 
��  ¥ : 2018-03-27
��  �� : ������� �⺻�� �Ǵ� Ŭ����
*/

#pragma once

#include "CommonHeader.h"
#include "Server.h"

class CAccepterBase : public CServer
{
public:
	CAccepterBase(void);
	virtual ~CAccepterBase(void);

	virtual BOOL			Initializing(const int _nPort);

	//< ������ ��ƾ �� 1ȸ
	//virtual HRESULT		Create();

	//< ���� ��������� 
	//virtual BOOL			ServerShutDown();

};