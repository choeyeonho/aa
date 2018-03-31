/*
2018 - 02 - 05 : √÷ø¨»£

this script is queue buffer

When you want to use your data indefinitely, use this script
it provide the pointer space indefinitely
if used in UDP environment , don't use this script , then you'll make a udp queue buffer
i think, When creating an udp buffer, you must store entire data in the <Queue>format

*/
#pragma once

#include <Windows.h>

#define MAX_BUFFER_SIZE	0xfff

//< buf packet return type 
typedef struct BUF_PACKET_TYPE
{
	BYTE*	_pSize;
	BYTE*	_pData;
} PACKETYPE;

class CQueueBuffer
{
private:
	//< Buffer Storege of All
	BYTE*		m_pBuffers;

	//< pos of read for copy data
	DWORD		m_dReadPos;
	//< pos of write for get data
	DWORD		m_dWritePos;

	//< Cout of How many push data 
	DWORD		m_dPushCount;
	//< Cout of How many pop data 
	DWORD		m_dPopCount;

	//< now, this buffer have Data's count 
	DWORD		m_dNowPacketCount;	

	//< now, have buffer size
	DWORD		m_dNowBufferSize;

	//< buffer Size variable	
	DWORD		m_dBufferSize;

	//< read, write Point variable
	BYTE*		m_pReadPoint;
	BYTE*		m_pWritePoint;

	//< 
	BYTE			m_bTempPacket[500];

public:
	
	//< Initializing the buffer store
	HRESULT			Initializing(const int _nBufSize);

	//< push data into the buffer store
	void				PushData(BYTE* _pData, const int _nLength);

	//< pop data into the buffer store 
	BUF_PACKET_TYPE	Popdata();

	//< Get Read,Write point
	BYTE*			GetReadPoint();
	BYTE*			GetWirtePoint();

	//< Get packet pointer from this function
	BUF_PACKET_TYPE	GetPacket(const int _nPacketSize);


	DWORD			GetBufferSize();
	DWORD			GetPacketCount();
	DWORD			GetPushCount();
	DWORD			GetPopCount();
	DWORD			GetNowBufferSize();
	//< give to recv's function to total allocate memory size 
	DWORD			GetRecvBytes(); 

	//< for winsock function
	char*			GetRecvPointer();
	//< psuh data and lengh
	VOID				Increasepacket(const int _nPacketSize);


	CQueueBuffer(void);
	~CQueueBuffer(void);
};

