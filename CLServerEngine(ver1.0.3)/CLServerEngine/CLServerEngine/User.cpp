#include "User.h"


CUser::CUser(void)
{
}


CUser::~CUser(void)
{
}
void				CUser::SetUnit(CNetworkUnit*		_pUnit)
{
	m_networkUnit = _pUnit;
}
CNetworkUnit*		CUser::GetUnit()
{
	return m_networkUnit;
}