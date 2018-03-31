
/*
2018-03-18-�ֿ�ȣ

�������� �������� ���Ͽ� 2���� Ű�� ������.
���Ű, ����Ű

����Ű�� Ŭ�� ������ ������ �ְ�
����Ű�� ��� ����� ���Ű�� �̿��Ͽ� ��´�.
��, ��ȣȭ, ��ȣȭ�� ���°� ����Ű�̸�
����Ű�� ������ ���� ���Ű�Դϴ�.
( ����Ű, ���Ű�� SecuritCode.h �� ���� )

���������� �Ź� ���ϴ°� ���Ű �̸� ����Ű�� �����̴�.
�ʿ信���� ����Ű�� �������ָ� �����Ͱ� �Ź� ���ϰ� 
��ŷ�ӵ��� ���������Դϴ�.

�Ųٷ� ���Ű�� ����Ű �� ����Ű�� 256���� �ϰ� ���Ű�� 16���� �Ͽ�
256byte�� ����Ҽ� �ִٸ� �������� 16���� �պ��Ͽ� ����ϴ°͵� �����ٰ� ����

*/
#pragma once

#include <Windows.h>
#include <malloc.h>
#include "SecurityCode.h"

//< �ִ� �ѹ��� MAX_CRYPTION_SIZE��ŭ �����մϴ�.
//< ���� �� �߰��� �Ϸ��� �Ʒ��� define�� �ø��� �˴ϴ�.
#define MAX_CRYPTION_SIZE	256

class CDataEncryption
{
private:			
	ULONG		m_publicKey[USE_KEYCOUNT];
public:

	//< ����Ű�� �����ϴ�.
	void			GetPublicKey();	

	//< �����͸� ��ȣȭ �մϴ�.
	void			Encryption( char* _data , const int _nSize );

	//< �����͸� ��ȣȭ �մϴ�.
	void			Decryption( char* _data, int _startPublicPos ,const int _nSize );

	//< ���ڿ� ���·� ��ȣȭ �Ͽ� �����մϴ�.
	//< 1 : ������ ������, 2 : ���� ������, 3 : ������
	void			EncryptBuffer(char* _targetBuffer, char* _data, const int _nSize);

	//< ���ڿ� ���·� ��ȣȭ �Ͽ� �����մϴ�.
	//<1 : ������ ������, 2 : ���� ������ , 3 : ���° ��ȣȭ���� ����Ұ��� , 4 : ������
	void			DecryptBuffer(char* _targetBuffer, char* _data,	int _startPublicPos, const int _nSize);

	CDataEncryption(void);
	~CDataEncryption(void);
};