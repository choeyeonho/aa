/*
작성자 : 최연호 
날  짜 : 2018-03-27
내  용 : 어셉터의 기본이 되는 클레스
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

	//< 쓰레드 루틴 전 1회
	//virtual HRESULT		Create();

	//< 서버 종료됬을때 
	//virtual BOOL			ServerShutDown();

};