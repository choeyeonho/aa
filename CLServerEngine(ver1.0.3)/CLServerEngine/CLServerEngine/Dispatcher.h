/*
�ۼ��� : �̽���
��  ¥ : 2018-03-25
��  �� : ��Ŷ ó�� Ŭ���� �����带 ����Ͽ� ������ ���ư���.
*/
/*
������ : �ֿ�ȣ
��  ¥ : 2018-03-28
��  �� : ���������� ó���ϵ� �����带 ������ ���� ó���ϰ� �����.
		���� �� ���� �����Ĵ� �� ������ �ϳ��� �����带 ���������
		�� �����ĸ� ������ ���� ó��

		�ι�°�δ� �� ���� Ŭ������ ������ ���ڸ� �޾ƾ� ������
		�ܺο��� �ڽ��� ���ϴ� Ŭ������� ���� ���ؼ��� ������ �ʿ�
		( ��, �⺻�� ���̽��� ������ �ڽ��� ���ϴ� ������ ������ �ְ� �ϱ� ���� )

		����°�� ���ϰ� �� ť�� �ᵵ ������ ���������� �ȵǴ� ������ �ְ�
		���������� push,pop�� �Ͼ�� �ϸ� �������� �߰��������� ���ٰ� �����ؼ�
		vector�� ����
				
		http://www.tipssoft.com/bulletin/board.php?bo_table=story&wr_id=197
*/
#pragma once

#define		DEF_CYH_IMPROVE_DISPATCHER		//< �ֿ�ȣ, ����ó ���� ( 4�� 6�� ������ ���� ���� )

#include <functional>
#include <map>
#include <vector>
#include "User.h"
#include "Thread.h"
#include "CriticalSection.h"


//��Ŷ �������� �Լ�������
typedef std::function< void(BUF_PACKET_TYPE,CUser*)>		PROTOCOL_TYPE;


class CDispatcher : public CThread
{
private:
	//< Ŀ�ǵ� ����Ʈ ( ���, ������, ���� ������ )
	std::map<DWORD,PROTOCOL_TYPE>	m_commandList;
	std::map<DWORD,PROTOCOL_TYPE>::iterator		m_mapiter;
	//< üũ�� ���� ����Ʈ
	std::vector<CUser*>			m_vUserList;	

	//< ũ��Ƽī�� ���Ÿ�
	CriticalSection				m_cs;
	
	//< ������ �����ĵ鰣�� ������ ���Կ�����
	CDispatcher& operator = (CDispatcher& _p)
	{
		//< ���� ������ ����
		m_vUserList		= _p.GetvUserList();
		
		//< Ŀ�ǵ� ������ ����
		m_commandList		= _p.GetCommandList();
	}

public:
	std::vector<CUser*>			GetvUserList();
	std::map<DWORD,PROTOCOL_TYPE>	GetCommandList();

	//< ������ �־��ָ� ����Ʈ�� ����
	void PushUser(CUser* _user);	

public:
	CDispatcher(const int _maxUser);	
	virtual ~CDispatcher(void);	

	virtual int Run() override;

};

//���������� �߰����ִ� ��ũ��
#define ADD_PROTOCOL(key, func) AddProtocol(key, std::bind(func, this, std::placeholders::_1, std::placeholders::_2))