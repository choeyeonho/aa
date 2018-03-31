/*
작성자 : 이승하
날  짜 : 2018-03-18
설  명 : 특정 시간에 발생하는 이벤트를 작성하는 클래스
변  경 : < 이승하 , 2018-03-20 >
		날짜를 이용한 시간이벤트에서 이벤트발동 날짜를 사용자가 부분적으로
		가능하도록 수정
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

	//시간에 맞춰 실행될 함수
	virtual void	Execute() = 0;
};