#include "IniReader.h"
#include "CommonHeader.h"
#include <Windows.h>

int CIniReader::ReadInt(char* _strSection, char* _strKey, char* _strFile)
{
	int nResult = GetPrivateProfileIntA(_strSection, _strKey, -1, _strFile);

	return nResult;
}


void CIniReader::ReadString(char* _strSection, char* _strKey, char* _strFile, char* _pDest, int _nSize)
{
	if(_pDest == nullptr)
		return;

	GetPrivateProfileStringA(_strSection, _strKey, "", _pDest, _nSize, _strFile);
}

std::string CIniReader::ReadString(char* _strSection, char* _strKey, char* _strFile)
{
	char		strResult[30];
	std::string strValue;

	ReadString(_strSection, _strKey, _strFile, strResult, 30);
	strValue = strResult;
	
	return strValue;
}

bool CIniReader::WriteValue(char* _strSection, char* _strKey, char* _strFile, char* _strValue)
{
	return WritePrivateProfileStringA(_strSection, _strKey, _strValue, _strFile);
}