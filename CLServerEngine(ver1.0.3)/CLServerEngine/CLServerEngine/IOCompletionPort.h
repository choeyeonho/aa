#pragma once

#include "CommonHeader.h"
#include <Windows.h>

class CIOCompletionPort
{
private:
	HANDLE	m_hIOCP;
public:
	CIOCompletionPort(int nMaxConcurrency = 0);
	~CIOCompletionPort(void);

	bool		AssociateSocket(SOCKET _sock,DWORD dwCompletionKey);
	bool		PostStatus(ULONG_PTR dwCompletionKey, DWORD dwBytes, OVERLAPPED* pOver);
	bool		GetStatus(ULONG_PTR* pdwCompletionKey, DWORD* pdwBytes, OVERLAPPED** ppOver, DWORD dwMilliSeconds = INFINITE);
};

