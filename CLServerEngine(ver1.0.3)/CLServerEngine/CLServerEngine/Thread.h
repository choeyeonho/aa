/*
�ۼ���		: �ֿ�ȣ
������¥		: 2018-03-26
����			: Sleep(%d)�� ����Ͽ� ���� �ð�, Ȥ�� �� ������ �ٷ�
			  ���ý�Ʈ�� �����ߴµ� win10���ʹ� ������ ������ �����ִ� �����忡 ����
			  �߾��ٸ� win10���ʹ� �����ھ�� ������ �����忡 �켱������ ����ϰ�
			  �� �Ŀ� SMT�� ������ �����忡 ����ϰ� �Ǹ鼭 cpu�� ������� �ʴ� �κе�
			  ������ϴ�.

			  �׽�Ʈ ��� : ���� ������ �����带 ������ �������� ���������� ��������
			  255���� �����带 ���������� ��� CPU�� ��� ���
			  �ᱹ���� �켱������ ������ ��
			  
			  ��ó ��		: �ϳ��� �ھ �ϳ��� �����带 ����ϰ� ����ϴ�.
						  �ϳ��� �� �����尡 ������ ��쿡
						  �Ʒ��� �׿� �ش�Ǵ� ��ũ
			  (http://grandstayner.tistory.com/entry/Thread-Thread%EB%A5%BC-Core%EC%97%90-%ED%95%A0%EB%8B%B9%ED%95%98%EA%B8%B0)

			  
����			: http://colomy.tistory.com/120
			  http://www.hwbattle.com/bbs/board.php?bo_table=news&wr_id=70307

*/

#pragma once
#include <WinSock2.h>
#include <Windows.h>

//< �� ������� priority�� ���� ������ ���� �ʽ��ϴ�. �ھ �ش�Ǳ� ����
//< ���߿� �ʿ��ϰ� �Ǹ� �߰��� ��
class CThread
{
private:
	//< ������ �ڵ� �ѹ���
	HANDLE	m_hThreadHandle;	
	

	DWORD	m_dwCurTime;
	DWORD	m_dwLastTime;
	DWORD	m_dwDelayTime;
public:
	CThread();
	~CThread();

	//< CPU�� �����·� �ٲٴ� �۾�
	//< context������ ���� Run���� �� �ҷ��ֵ��� �Ѵ�.
	void			SetSwitchingTime(DWORD	_dwDelayTime);
	void			ContextSwitching();

	//< �������� Run�� ���� �Լ��� ����� ��
	virtual int	Run();
	
	//< �⺻���
	HRESULT		StartThread(int (*_func)() = nullptr);	
	HRESULT		WaitThread(DWORD dwTimeOut);

	HANDLE		GetHandle();

	//< �����ɶ� �ϰ� �� ��
	virtual HRESULT		Create();

	//< ������ �Լ�
	static unsigned int __stdcall ThreadFunction (void* pv);		

	/* �ӵ� �׽�Ʈ�� �غ� ��� ����Ǵ� �ӵ��� �ٸ��Ϳ� ���� �����ϴ�.. (�翬�Ѱ��.. )	*/
	/* ��üȭ �Ͽ� ����Ҷ��� ��� ��õ												*/
private:
	BOOL				m_bISObjected;	//< ��üȭ �Ͽ��� ����ϴ��� üũ
	int				(*m_pFunc)();		//< �Լ������� ��ġ ( ��üȭ �Ͽ��� ����Ҷ� )
public:
	BOOL				GetIsObjected();	//< ��üȭ �ߴ��� üũ
	int (*GetFunc())();				//< �Լ������� ����
};