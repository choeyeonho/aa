/*
�ۼ��� : �̽���
��  ¥ : 2018-03-29
��  �� : Registry�� �а� ���� Ŭ����
*/
#pragma once
#include <Windows.h>
#include <string>

class CRegistry
{
private:
	HKEY		m_hKey;			//������Ʈ�� �ڵ�
	std::string m_strKeyName;	//������Ʈ�� Ű

public:
	CRegistry(HKEY _hRoot, char* _strPath, bool _isCreate = false);
	~CRegistry(void);

	//������Ʈ���� ���� �Լ�
	void OpenRegistry(HKEY _hRoot, char* _strPath, bool _isCreate = false);
	//������Ʈ���� ���� �ִ� �Լ�(������)
	bool WriteInt(char* _strName, DWORD _dwValue, DWORD _dwType = REG_DWORD);
	//������Ʈ���� ���� �ִ� �Լ�(���ڿ�)
	bool WriteString(char* _strName, char* _strValue, DWORD _dwSize, DWORD _dwType = REG_SZ);
	//������Ʈ���� ���� �д� �Լ�
	bool ReadValue(char* _strName, char* _pDest, DWORD _dwSize);
	//������Ʈ�� ����
	void Close();
};