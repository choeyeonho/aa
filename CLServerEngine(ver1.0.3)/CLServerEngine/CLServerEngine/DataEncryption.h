
/*
2018-03-18-최연호

데이터의 안정성을 위하여 2개의 키를 가진다.
비밀키, 공개키

공개키는 클라도 서버도 가지고 있고
공개키를 얻는 방법은 비밀키를 이용하여 얻는다.
즉, 복호화, 암호화에 쓰는건 공개키이며
공개키를 만들어내는 것은 비밀키입니다.
( 공개키, 비밀키는 SecuritCode.h 에 저장 )

직접적으로 매번 변하는건 비밀키 이며 공개키는 고정이다.
필요에따라 공개키도 변경해주면 데이터가 매번 변하고 
해킹속도가 느려질것입니다.

거꾸로 비밀키와 공개키 즉 공개키를 256으로 하고 비밀키를 16으로 하여
256byte씩 사용할수 있다면 좋겠지만 16으로 왕복하여 사용하는것도 괜찮다고 생각

*/
#pragma once

#include <Windows.h>
#include <malloc.h>
#include "SecurityCode.h"

//< 최대 한번에 MAX_CRYPTION_SIZE만큼 가능합니다.
//< 만약 더 추가로 하려면 아래의 define을 늘리면 됩니다.
#define MAX_CRYPTION_SIZE	256

class CDataEncryption
{
private:			
	ULONG		m_publicKey[USE_KEYCOUNT];
public:

	//< 공개키를 얻어냅니다.
	void			GetPublicKey();	

	//< 데이터를 암호화 합니다.
	void			Encryption( char* _data , const int _nSize );

	//< 데이터를 복호화 합니다.
	void			Decryption( char* _data, int _startPublicPos ,const int _nSize );

	//< 문자열 형태로 암호화 하여 리턴합니다.
	//< 1 : 저장할 포인터, 2 : 읽을 포인터, 3 : 사이즈
	void			EncryptBuffer(char* _targetBuffer, char* _data, const int _nSize);

	//< 문자열 형태로 복호화 하여 리턴합니다.
	//<1 : 저장할 포인터, 2 : 읽을 포인터 , 3 : 몇번째 암호화부터 사용할건지 , 4 : 사이즈
	void			DecryptBuffer(char* _targetBuffer, char* _data,	int _startPublicPos, const int _nSize);

	CDataEncryption(void);
	~CDataEncryption(void);
};