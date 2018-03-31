/*
작성자 : 이승하
날  짜 : 2018-03-17
설  명 : Random클래스를 이용하여 확률을 계산해주는 클래스
*/
#pragma once
#include <vector>
#include "Random.h"

class CPercentage : public CRandom
{
public:
	CPercentage(void);
	virtual ~CPercentage(void);

	static BOOL GetRandomSuccess(float _fPercentage);
	static int GetNumber(int _nMin, int _nMax, std::vector<float>& _vPercentage);
};