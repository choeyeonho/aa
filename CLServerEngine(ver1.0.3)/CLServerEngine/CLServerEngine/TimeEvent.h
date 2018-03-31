/*
�ۼ��� : �̽���
��  ¥ : 2018-03-18
��  �� : Ư�� �ð��� �߻��ϴ� �̺�Ʈ�� �ۼ��ϴ� Ŭ����
��  �� : < �̽��� , 2018-03-20 >
		��¥�� �̿��� �ð��̺�Ʈ���� �̺�Ʈ�ߵ� ��¥�� ����ڰ� �κ�������
		�����ϵ��� ����
*/

#pragma once
#include "Time.h"

enum TIME_EVENT_TYPE
{
	eTIME_EVENT_NONE = -1,
	eTIMER,
	eDATE
};

class CTimeEvent
{
protected:
	int				m_nActiveTime;
	int				m_nLastActive;
	ST_DATE			m_stActiveDate;
	char			m_cDateFlag;
	int				m_nType;
	bool			m_isRun;

public:
	CTimeEvent(void);
	virtual ~CTimeEvent(void);

	virtual bool	IsEventTime();
	bool			IsEventTime(ST_DATE& _stNowDate);
	void			SetActiveTime(int _nActiveTime);
	void			SetActiveTime(ST_DATE& _stActiveDate, char _cFlag = eDF_ALL);
	void			SetRun(bool _bRun);

	//�ð��� ���� ����� �Լ�
	virtual void	Execute() = 0;
};