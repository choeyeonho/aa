/*
�ۼ��� : �̽���
��  ¥ : 2018-03-16
��  �� : WELL512 �˰����� ����Ͽ� ������ �߻������ִ� Ŭ����
*/
#pragma once
#include <Windows.h>
#include <math.h>

//Ư�� �Ҽ��� �ݿø��� ���ִ� �Լ�
//float���� ������ ���ؼ� ���
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