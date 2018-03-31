#include "Percentage.h"


CPercentage::CPercentage(void)
{
}


CPercentage::~CPercentage(void)
{
}

//_fPercentage의 확룔로 성공, 실패를 반환
BOOL	CPercentage::GetRandomSuccess(float _fPercentage)
{
	float fRandom = GetFloat(0.01f, 100.0f);

	return (fRandom <= ROUND(_fPercentage, 2))? TRUE : FALSE;
}

//_nMin ~ _nMax 까지의 수 중에서 특정 확률에 따라 값을 반환하는 함수
//_vPercentage에 각각의 수가 나올 확률을 넣어준다.
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