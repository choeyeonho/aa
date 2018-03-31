/*
�ۼ��� : �ֿ�ȣ
��  ¥ : 2018-03-26
��  �� : �����带 �����ϴ� Ŭ����
��  �� : < �ֿ�ȣ , 2018-03-26 >
		�����尡 ������ �� �����忡 ���� �ھ� ������ ���ݴϴ�. 
		�ھ� ������ cpu������ �ް� ���� ������ �Ѱ��� �ø��� ������ ���ϴ�
		�̷��� �ϴ� ������ window10�� �������� cpu���� �������ִ� �ɼ��� ����
		��� ȯ�濡���� cpu�� �����带 �յ��� ����ϱ� ���ؼ� �Դϴ�.
*/

#pragma once

#include "CommonHeader.h"
#include "Thread.h"
#include "Core.h"
#include <map>
#include <process.h>

class CThread;

class CThreadManager
{
private:
	CCore*						m_Cores;			//< Core�ɼ� ���� ����
	int							m_processerCount; //< cpu ����
	int							m_nNowCore;		//< �� ��ġ�� �ھ� ��	
	int							m_nMaxCore;		//< �ִ� ��
private:	
	CThreadManager();
	~CThreadManager();
	//< Thread Single ton
	static CThreadManager*			m_pInstance;
public:	
	static CThreadManager*			GetInstance();

private:
	std::map<HANDLE, CThread*>		m_mThreadList;

public:
	int							AddThread(HANDLE _handle, CThread* _thread);	
	HRESULT						DeleteThread(HANDLE _handle,int _nCoreNumber);
	
	//< ��� ������ ����
	HRESULT						AllSuspend();

	//< �����带 ��´�.
	CThread*						GetThread(HANDLE _handle);	

	//< ���� �۵����� ������ ����
	DWORD						GetThreadCount();

	//< ��� �ھ ���� ����
	void							SetCore(HANDLE _handle);

	//------------------------ �Ʒ��� �Լ����� 0~ProcessCount-1 ���� ����

	//< �ش� �ھ �ִ� ��� Thread ���� 
	void							EndThreadInCore(const int _nCoreNumber);

	//< �ش� �ھ �ִ� ��� Thread �Ͻ� ����
	void							SuspendThreadInCore(const int _nCoreNumber);
	
	//< �ش� �ھ �ִ� ��� Thread �����
	void							ActiveThreadInCore(const int _nCoreNumber);
	

	//< ������ �Ŵ��� �ʱ�ȭ
	void							Initializing();
	
};

//< ���ڸ� �빮�������� ��� �����ΰ� �ް����� ������ �տ� S���̰� ���̹�
//< �ڵ� ������ ������ �پ� ������ class�б����� �����̴� �ǹؿ�
//< ������ ġȯ�̶�� �Ҽ� ������ ���� ���ü� �ִٰ� �� ����
#define SThreadManager CThreadManager::GetInstance()