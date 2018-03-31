#include "Percentage.h"


CPercentage::CPercentage(void)
{
}


CPercentage::~CPercentage(void)
{
}

//_fPercentage�� Ȯ��� ����, ���и� ��ȯ
BOOL	CPercentage::GetRandomSuccess(float _fPercentage)
{
	float fRandom = GetFloat(0.01f, 100.0f);

	return (fRandom <= ROUND(_fPercentage, 2))? TRUE : FALSE;
}

//_nMin ~ _nMax ������ �� �߿��� Ư�� Ȯ���� ���� ���� ��ȯ�ϴ� �Լ�
//_vPercentage�� ������ ���� ���� Ȯ���� �־��ش�.
int		CPercentage::GetNumber(int _nMin, int _nMax, std::vector<float>& _vPercentage)
{
	int nCount = _nMax - _nMin + 1;
	float fSum = 0;
	float fRandom = GetFloat(0.01f, 100.0f);
	int nResult = -1;

	for(unsigned int index = 0; index < _vPercentage.size(); ++index)
	{
		fSum += _vPercentage[index];

		if(fRandom <= fSum)
		{
			nResult = _nMin + index;
			break;
		}
	}

	return nResult;
}