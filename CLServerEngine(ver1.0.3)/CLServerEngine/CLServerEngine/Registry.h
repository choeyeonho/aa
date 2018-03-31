/*
작성자 : 이승하
날  짜 : 2018-03-29
설  명 : Registry를 읽고 쓰는 클래스
*/
#pragma once
#include <Windows.h>
#include <string>

class CRegistry
{
private:
	HKEY		m_hKey;			//레지스트리 핸들
	std::string m_strKeyName;	//레지스트리 키

public:
	CRegistry(HKEY _hRoot, char* _strPath, bool _isCreate = false);
	~CRegistry(void);

	//레지스트리를 여는 함수
	void OpenRegistry(HKEY _hRoot, char* _strPath, bool _isCreate = false);
	//레지스트리에 값을 넣는 함수(정수형)
	bool WriteInt(char* _strName, DWORD _dwValue, DWORD _dwType = REG_DWORD);
	//레지스트리에 값을 넣는 함수(문자열)
	bool WriteString(char* _strName, char* _strValue, DWORD _dwSize, DWORD _dwType = REG_SZ);
	//레지스트리에 값을 읽는 함수
	bool ReadValue(char* _strName, char* _pDest, DWORD _dwSize);
	//레지스트리 종료
	void Close();
};