/*
작성자 : 최연호
날  짜 : 2018-03-28
설  명 : 패킷을 받거나 처리가 준비 됬을때 처리
		패킷 처리부분은 각 서버에서 지정되있다.
*/
#pragma once

#include <functional>
#include "NetworkUnit.h"


class CUser
{
private:
	//< 자신에 해당되는 Network unit을 받아옵니다.	
	CNetworkUnit*		m_networkUnit;

public:
	CUser(void);
	~CUser(void);

	void				SetUnit(CNetworkUnit*		_pUnit);
	CNetworkUnit*		GetUnit();
};

