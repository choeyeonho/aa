#pragma once
/*
������ : �ֿ�ȣ
�ۼ��� : 2018-03-26
��  �� : �ϳ��� �ھ ������ ��������� ������ ������ ��Ʈ�� �ϴ� Ŭ����
*/

#include <Windows.h>
#include <vector>
#include <process.h>

class CCore
{
private:
	//< �� �ھ �ִ� ��������� �ڵ��� �����ϰ� �ֽ��ϴ�.
	std::vector<HANDLE>		m_vHandleList;

	int						m_nCoreCount;
	int						m_nCoreNumber;	//< �� �ھ��� �ѹ� ��
public:

	//< �ش� �ھ �����带 �߰� �մϴ�.
	void						AddThread(HANDLE _handle);

	//< �ش� �ھ �����带 ���� �մϴ�.
	void						DelThread(HANDLE _handle);
	
	//< ��� Thread ���� 
	void						EndThread();

	//< ��� Thread �Ͻ� ����
	void						StopThread();
	
	//< ��� Thread �����
	void						ActiveThread();

	
	//< Get �Լ�
	std::vector<HANDLE>		GetHandleList();
	int						GetHandleCount();

	//< Set�Լ�
	void						SetCoreNumber(const int _nCoreNumber);

	CCore();
	~CCore(void);
};

