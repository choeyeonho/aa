#pragma once
/*
�ۼ��� : �ֿ�ȣ
��  ¥ : 2018-03-20
��  �� : ���� ���μ������� �ϳ��� �޸𸮿� �����Ͽ� ����Ҷ�
CSharedMemory���� ���� �޾ƿ� �� ���� ���������� ����Ҷ� ���

�����͸� �״�� SharedMemory�� ������ ������ �ȵ�
�� Ŭ������ ����ؼ� ����ϱ� ����
*/

class CSharedObject
{
private:

	char*		m_pMemory;
	int			m_nMemorySize;

public:
	CSharedObject(void);
	CSharedObject(char* _pMemory, int _nMemorySize);
	~CSharedObject(void);

	char*		GetMemoryPointer();
	int			GetMemorySize();
};