/*
�ۼ��� : �̽���
��  ¥ : 2018-03-17
��  �� : RandomŬ������ �̿��Ͽ� Ȯ���� ������ִ� Ŭ����
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