/*
작성자 : 이승하
날  짜 : 2018-03-25
설  명 : 패킷 처리 클래스 쓰레드를 사용하여 별도로 돌아간다.
*/
/*
수정자 : 최연호
날  짜 : 2018-03-28
설  명 : 여러유저를 처리하데 쓰레드를 나눠서 동시 처리하게 만든다.
		현재 이 전의 디스패쳐는 한 유저에 하나의 쓰레드를 배분했지만
		이 디스패쳐를 여러게 만들어서 처리

		두번째로는 이 전의 클레스는 고정된 인자만 받아야 했지만
		외부에서 자신이 원하는 클레스대로 쓰기 위해서는 변경이 필요
		( 즉, 기본의 베이스를 따르데 자신이 원하는 개념을 넣을수 있게 하기 위함 )

		세번째로 승하가 쓴 큐를 써도 돼지만 유지관리가 안되는 단점이 있고
		지속적으로 push,pop이 일어나야 하며 쓸데없는 중간과정들이 많다고 생각해서
		vector로 변경
				
		http://www.tipssoft.com/bulletin/board.php?bo_table=story&wr_id=197
*/
#pragma once

#define		DEF_CYH_IMPROVE_DISPATCHER		//< 최연호, 디스패처 수정 ( 4월 6일 최종적 선택 예정 )

#include <functional>
#include <map>
#include <vector>
#include "User.h"
#include "Thread.h"
#include "CriticalSection.h"


//패킷 프로토콜 함수포인터
typedef std::function< void(BUF_PACKET_TYPE,CUser*)>		PROTOCOL_TYPE;


class CDispatcher : public CThread
{
private:
	//< 커맨드 리스트 ( 헤더, 데이터, 유저 포인터 )
	std::map<DWORD,PROTOCOL_TYPE>	m_commandList;
	std::map<DWORD,PROTOCOL_TYPE>::iterator		m_mapiter;
	//< 체크할 유저 리스트
	std::vector<CUser*>			m_vUserList;	

	//< 크리티카르 섹셔르
	CriticalSection				m_cs;
	
	//< 각각의 디스패쳐들간의 데이터 대입연산자
	CDispatcher& operator = (CDispatcher& _p)
	{
		//< 유저 데이터 대입
		m_vUserList		= _p.GetvUserList();
		
		//< 커맨드 데이터 대입
		m_commandList		= _p.GetCommandList();
	}

public:
	std::vector<CUser*>			GetvUserList();
	std::map<DWORD,PROTOCOL_TYPE>	GetCommandList();

	//< 유저를 넣어주면 리스트에 셋팅
	void PushUser(CUser* _user);	

public:
	CDispatcher(const int _maxUser);	
	virtual ~CDispatcher(void);	

	virtual int Run() override;

};

//프로토콜을 추가해주는 매크로
#define ADD_PROTOCOL(key, func) AddProtocol(key, std::bind(func, this, std::placeholders::_1, std::placeholders::_2))