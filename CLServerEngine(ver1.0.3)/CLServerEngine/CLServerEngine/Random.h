/*
작성자 : 이승하
날  짜 : 2018-03-16
설  명 : WELL512 알고리즘을 사용하여 난수를 발생시켜주는 클래스
*/
#pragma once
#include <Windows.h>
#include <math.h>

//특정 소수점 반올림을 해주는 함수
//float값의 고정을 위해서 사용
#define ROUND(x, digit) (floor((x) * pow(static_cast<float>(10), digit) + 0.5f) / pow(static_cast<float>(10), digit))

class CRandom
{
private:
	static DWORD m_dwState[16];
	static unsigned int m_nIndex;
	static bool m_isSeed;

public:
	static void SetSeed(int _nSeed);
	static void SetSeed();

	static DWORD GetNumber();
	static DWORD GetNumber(DWORD _dwMin, DWORD _dwMax);
	static float GetFloat();
	static float GetFloat(float _fMin, float _fMax);

	CRandom(void);
	~CRandom(void);
};