/*
작성자		: 최연호
수정날짜		: 2018-03-26
내용			: Sleep(%d)를 사용하여 일정 시간, 혹은 그 순간에 바로
			  컨택스트를 변경했는데 win10부터는 기존에 무작정 여유있는 쓰레드에 대입
			  했었다면 win10부터는 물리코어로 생성된 쓰레드에 우선적으로 배분하고
			  이 후에 SMT로 생성된 쓰레드에 배분하게 되면서 cpu를 사용하지 않는 부분도
			  생겼습니다.

			  테스트 결과 : 작은 갯수의 쓰레드를 돌리면 가능한한 구역내에서 돌리지만
			  255개의 쓰레드를 돌렸을때는 모든 CPU를 모두 사용
			  결국에는 우선적으로 대입할 뿐
			  
			  대처 법		: 하나의 코어에 하나의 쓰레드를 담당하게 만듭니다.
						  하나의 빈 쓰레드가 존재할 경우에
						  아래는 그에 해당되는 링크
			  (http://grandstayner.tistory.com/entry/Thread-Thread%EB%A5%BC-Core%EC%97%90-%ED%95%A0%EB%8B%B9%ED%95%98%EA%B8%B0)

			  
참고			: http://colomy.tistory.com/120
			  http://www.hwbattle.com/bbs/board.php?bo_table=news&wr_id=70307

*/

#pragma once
#include <WinSock2.h>
#include <Windows.h>

//< 이 쓰레드는 priority에 대한 설정은 하지 않습니다. 코어에 해당되기 때문
//< 나중에 필요하게 되면 추가할 것
class CThread
{
private:
	//< 쓰레드 핸들 넘버값
	HANDLE	m_hThreadHandle;	
	

	DWORD	m_dwCurTime;
	DWORD	m_dwLastTime;
	DWORD	m_dwDelayTime;
public:
	CThread();
	~CThread();

	//< CPU를 대기상태로 바꾸는 작업
	//< context변경은 하위 Run에서 꼭 불러주도록 한다.
	void			SetSwitchingTime(DWORD	_dwDelayTime);
	void			ContextSwitching();

	//< 하위에서 Run에 대한 함수를 만들면 됨
	virtual int	Run();
	
	//< 기본기능
	HRESULT		StartThread(int (*_func)() = nullptr);	
	HRESULT		WaitThread(DWORD dwTimeOut);

	HANDLE		GetHandle();

	//< 생성될때 하게 될 일
	virtual HRESULT		Create();

	//< 쓰레드 함수
	static unsigned int __stdcall ThreadFunction (void* pv);		

	/* 속도 테스트를 해본 결과 실행되는 속도가 다른것에 비해 느립니다.. (당연한결과.. )	*/
	/* 객체화 하여 사용할때만 사용 추천												*/
private:
	BOOL				m_bISObjected;	//< 객체화 하여서 사용하는지 체크
	int				(*m_pFunc)();		//< 함수포인터 위치 ( 객체화 하여서 사용할때 )
public:
	BOOL				GetIsObjected();	//< 객체화 했는지 체크
	int (*GetFunc())();				//< 함수포인터 얻어내기
};