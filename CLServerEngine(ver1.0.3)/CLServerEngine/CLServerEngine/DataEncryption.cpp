#include "DataEncryption.h"


CDataEncryption::CDataEncryption(void)
{
}


CDataEncryption::~CDataEncryption(void)
{
}

//< 공개키를 얻어냅니다.
void CDataEncryption::GetPublicKey()
{
	//< 사용할 비밀키 위치 ( 현재 총 (USE_PRIVATE_G_COUNT)개 )
	int nSecurityPos = 0;

	for( int i = 0 ; i < USE_KEYCOUNT; i++ )
	{
		//< 계산
		for( int j = 0; j < USE_PRIVATE_COUNT; j++ )
			m_publicKey[i] = PUBLIC_KEY[i] ^ PRIVATE_KEY[nSecurityPos][j];


		//< 위치 증가
		nSecurityPos++;

		//< 최대가 넘어갔을 경우
		if( nSecurityPos >= USE_PRIVATE_G_COUNT )
			nSecurityPos = 0;
	}
}

//< 데이터를 암호화 합니다.
void CDataEncryption::Encryption( char* _data , const int _nSize )
{
	//< 사용할 공개키 위치 ( 현재 총 (USE_PRIVATE_G_COUNT)개 )
	int nPublicPos = 0;

	for( int i = 0 ; i  < _nSize; i++ )
	{
		*(_data+i) = static_cast<char>(*(_data+i) ^ m_publicKey[nPublicPos]);

		nPublicPos++;
		if(nPublicPos >= USE_KEYCOUNT)
			nPublicPos = 0;
	}
}
//< 데이터를 복호화 합니다.
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
//< 문자열 형태로 암호화 하여 리턴합니다.
void CDataEncryption::EncryptBuffer(char* _targetBuffer, char* _data, const int _nSize)
{
	//< 기존의 데이터는 변경하지 않고 내부에서 처리하기 위해서 미리 만들어두고 사용	
	char localData[MAX_CRYPTION_SIZE];

	//< 데이터 복사
	for( int i = 0 ; i < _nSize; i++ )
		localData[i] = *(_data+i);
	
	//< 복사된 데이터로 암호화 시작
	Encryption(localData,_nSize);

	//< 암호화된 데이터를 targetBuffer에 채웁니다.
	for( int i = 0; i < _nSize; i++ )
		*( _targetBuffer + i ) = localData[i];
}

//< 문자열 형태로 복호화 하여 리턴합니다.
void CDataEncryption::DecryptBuffer(char* _targetBuffer, char* _data,	int _startPublicPos, const int _nSize)
{
	//< 기존의 데이터는 변경하지 않고 내부에서 처리하기 위해서 미리 만들어두고 사용	
	char localData[MAX_CRYPTION_SIZE];

	//< 데이터 복사
	for( int i = 0 ; i < _nSize; i++ )
		localData[i] = *(_data+i);
	
	//< 복사된 데이터로 암호화 시작
	Decryption(localData,_startPublicPos,_nSize);

	//< 암호화된 데이터를 targetBuffer에 채웁니다.
	for( int i = 0; i < _nSize; i++ )
		*( _targetBuffer + i ) = localData[i];
}