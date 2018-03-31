/*
작성자 : 이승하
날  짜 : 2018-03-29
설  명 : ini파일을 받아 값을 읽는 클래스
*/
#pragma once
#include <string>

class CIniReader
{
public:
	CIniReader(void);
	~CIniReader(void);

	//ini파일에서 int값을 읽습니다.
	static int			ReadInt(char* _strSection, char* _strKey, char* _strFile);
	//ini파일에서 char*값을 읽습니다.(char 주소값을 넣어서 받아옴)
	static void			ReadString(char* _strSection, char* _strKey, char* _strFile, char* _pDest, int _nSize);
	//ini파일에서 char*값을 읽습니다.(std::string로 반환)
	static std::string	ReadString(char* _strSection, char* _strKey, char* _strFile);
	//ini파일에 값을 씁니다.
	static bool			WriteValue(char* _strSection, char* _strKey, char* _strFile, char* _strValue);
};