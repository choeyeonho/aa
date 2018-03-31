/*
�ۼ��� : �̽���
��  ¥ : 2018-03-29
��  �� : ini������ �޾� ���� �д� Ŭ����
*/
#pragma once
#include <string>

class CIniReader
{
public:
	CIniReader(void);
	~CIniReader(void);

	//ini���Ͽ��� int���� �н��ϴ�.
	static int			ReadInt(char* _strSection, char* _strKey, char* _strFile);
	//ini���Ͽ��� char*���� �н��ϴ�.(char �ּҰ��� �־ �޾ƿ�)
	static void			ReadString(char* _strSection, char* _strKey, char* _strFile, char* _pDest, int _nSize);
	//ini���Ͽ��� char*���� �н��ϴ�.(std::string�� ��ȯ)
	static std::string	ReadString(char* _strSection, char* _strKey, char* _strFile);
	//ini���Ͽ� ���� ���ϴ�.
	static bool			WriteValue(char* _strSection, char* _strKey, char* _strFile, char* _strValue);
};