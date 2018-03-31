#include "Registry.h"

CRegistry::CRegistry(HKEY _hRoot, char* _strPath, bool _isCreate) : m_hKey(NULL)
{
	OpenRegistry(_hRoot, _strPath, _isCreate);
}

CRegistry::~CRegistry(void)
{
	Close();
}

void CRegistry::OpenRegistry(HKEY _hRoot, char* _strPath, bool _isCreate)
{
	Close();

	LONG lResult = RegOpenKeyExA(_hRoot, _strPath, NULL, KEY_ALL_ACCESS, &m_hKey);

	//레지스트리가 없을 시 생성
	if(lResult == ERROR_FILE_NOT_FOUND && _isCreate == true)
	{
		lResult = RegCreateKeyExA(_hRoot, _strPath, NULL, NULL, REG_OPTION_NON_VOLATILE, 
			KEY_ALL_ACCESS, NULL, &m_hKey, NULL);
	}

	//레지스트리 열기, 생성 실패
	if(lResult != ERROR_SUCCESS)
		m_hKey = NULL;
	else
		m_strKeyName = _strPath;
}

bool CRegistry::WriteInt(char* _strName, DWORD _dwValue, DWORD _dwType)
{
	if(m_hKey == NULL)
		return false;

	LONG lResult = RegSetValueExA(m_hKey, _strName, 0, _dwType, (BYTE*)&_dwValue, sizeof(DWORD));

	return (lResult != ERROR_SUCCESS)? false : true;
}

bool CRegistry::WriteString(char* _strName, char* _strValue, DWORD _dwSize, DWORD _dwType)
{
	if(m_hKey == NULL)
		return false;

	LONG lResult = RegSetValueExA(m_hKey, _strName, 0, _dwType, (BYTE*)_strValue, _dwSize);
	
	return (lResult != ERROR_SUCCESS)? false : true;
}

bool CRegistry::ReadValue(char* _strName, char* _pDest, DWORD _dwSize)
{
	if(m_hKey == NULL || _pDest == nullptr)
		return false;

	LONG lResult = RegQueryValueExA(m_hKey, _strName, 0, NULL, (BYTE*)_pDest, &_dwSize);
	
	return (lResult != ERROR_SUCCESS)? false : true;
}

void CRegistry::Close()
{
	if(m_hKey != NULL)
		RegCloseKey(m_hKey);
}