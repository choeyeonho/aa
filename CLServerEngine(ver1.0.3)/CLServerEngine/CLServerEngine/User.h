/*
�ۼ��� : �ֿ�ȣ
��  ¥ : 2018-03-28
��  �� : ��Ŷ�� �ްų� ó���� �غ� ������ ó��
		��Ŷ ó���κ��� �� �������� �������ִ�.
*/
#pragma once

#include <functional>
#include "NetworkUnit.h"


class CUser
{
private:
	//< �ڽſ� �ش�Ǵ� Network unit�� �޾ƿɴϴ�.	
	CNetworkUnit*		m_networkUnit;

public:
	CUser(void);
	~CUser(void);

	void				SetUnit(CNetworkUnit*		_pUnit);
	CNetworkUnit*		GetUnit();
};

