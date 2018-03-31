#include "DataEncryption.h"


CDataEncryption::CDataEncryption(void)
{
}


CDataEncryption::~CDataEncryption(void)
{
}

//< ����Ű�� �����ϴ�.
void CDataEncryption::GetPublicKey()
{
	//< ����� ���Ű ��ġ ( ���� �� (USE_PRIVATE_G_COUNT)�� )
	int nSecurityPos = 0;

	for( int i = 0 ; i < USE_KEYCOUNT; i++ )
	{
		//< ���
		for( int j = 0; j < USE_PRIVATE_COUNT; j++ )
			m_publicKey[i] = PUBLIC_KEY[i] ^ PRIVATE_KEY[nSecurityPos][j];


		//< ��ġ ����
		nSecurityPos++;

		//< �ִ밡 �Ѿ�� ���
		if( nSecurityPos >= USE_PRIVATE_G_COUNT )
			nSecurityPos = 0;
	}
}

//< �����͸� ��ȣȭ �մϴ�.
void CDataEncryption::Encryption( char* _data , const int _nSize )
{
	//< ����� ����Ű ��ġ ( ���� �� (USE_PRIVATE_G_COUNT)�� )
	int nPublicPos = 0;

	for( int i = 0 ; i  < _nSize; i++ )
	{
		*(_data+i) = static_cast<char>(*(_data+i) ^ m_publicKey[nPublicPos]);

		nPublicPos++;
		if(nPublicPos >= USE_KEYCOUNT)
			nPublicPos = 0;
	}
}
//< �����͸� ��ȣȭ �մϴ�.
void CDataEncryption::Decryption( char* _data, int _startPublicPos ,const int _nSize )
{
	for( int i = 0 ; i  < _nSize; i++ )
	{
		*(_data+i) = static_cast<char>(*(_data+i) ^ m_publicKey[_startPublicPos]);

		_startPublicPos++;
		if(_startPublicPos >= USE_KEYCOUNT)
			_startPublicPos = 0;
	}
}
//< ���ڿ� ���·� ��ȣȭ �Ͽ� �����մϴ�.
void CDataEncryption::EncryptBuffer(char* _targetBuffer, char* _data, const int _nSize)
{
	//< ������ �����ʹ� �������� �ʰ� ���ο��� ó���ϱ� ���ؼ� �̸� �����ΰ� ���	
	char localData[MAX_CRYPTION_SIZE];

	//< ������ ����
	for( int i = 0 ; i < _nSize; i++ )
		localData[i] = *(_data+i);
	
	//< ����� �����ͷ� ��ȣȭ ����
	Encryption(localData,_nSize);

	//< ��ȣȭ�� �����͸� targetBuffer�� ä��ϴ�.
	for( int i = 0; i < _nSize; i++ )
		*( _targetBuffer + i ) = localData[i];
}

//< ���ڿ� ���·� ��ȣȭ �Ͽ� �����մϴ�.
void CDataEncryption::DecryptBuffer(char* _targetBuffer, char* _data,	int _startPublicPos, const int _nSize)
{
	//< ������ �����ʹ� �������� �ʰ� ���ο��� ó���ϱ� ���ؼ� �̸� �����ΰ� ���	
	char localData[MAX_CRYPTION_SIZE];

	//< ������ ����
	for( int i = 0 ; i < _nSize; i++ )
		localData[i] = *(_data+i);
	
	//< ����� �����ͷ� ��ȣȭ ����
	Decryption(localData,_startPublicPos,_nSize);

	//< ��ȣȭ�� �����͸� targetBuffer�� ä��ϴ�.
	for( int i = 0; i < _nSize; i++ )
		*( _targetBuffer + i ) = localData[i];
}