#pragma once
/*
작성자 : 최연호
날  짜 : 2018-03-20
설  명 : 여러 프로세스에서 하나의 메모리에 접근하여 사용할때
CSharedMemory에서 값을 받아와 그 값을 직접적으로 사용할때 사용

포인터를 그대로 SharedMemory에 넣으면 관리가 안됨
이 클레스를 사용해서 사용하길 권장
*/

class CSharedObject
{
private:

	char*		m_pMemory;
	int			m_nMemorySize;

public:
	CSharedObject(void);
	CSharedObject(char* _pMemory, int _nMemorySize);
	~CSharedObject(void);

	char*		GetMemoryPointer();
	int			GetMemorySize();
};