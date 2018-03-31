#include "SharedObject.h"


CSharedObject::CSharedObject(void)
{
}


CSharedObject::~CSharedObject(void)
{
}

CSharedObject::CSharedObject(char* _pMemory, int _nMemorySize) : m_pMemory(_pMemory), m_nMemorySize(_nMemorySize)
{

}
char*		CSharedObject::GetMemoryPointer()
{
	return m_pMemory;
}
int			CSharedObject::GetMemorySize()
{
	return m_nMemorySize;
}