#include "CriticalSection.h"


CriticalSection::CriticalSection(void)
{
	InitializeCriticalSection( &m_cs );
}


CriticalSection::~CriticalSection(void)
{
	DeleteCriticalSection( &m_cs );
}

void CriticalSection::Enter()
{
	EnterCriticalSection( &m_cs );
}

void CriticalSection::Leave()
{
	LeaveCriticalSection( &m_cs );
}