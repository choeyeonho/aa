#include "QueueBuffer.h"
#include <stdio.h>

CQueueBuffer::CQueueBuffer(void) : m_pBuffers(nullptr), m_dReadPos(0),
	m_dWritePos(0),m_dPushCount(0),m_dPopCount(0),m_dNowPacketCount(0),
	m_dBufferSize(0),m_pReadPoint(nullptr),m_pWritePoint(nullptr)
{

}

CQueueBuffer::~CQueueBuffer(void)
{
	//< SAFE_DELETE_ARRAY
	if ( m_pBuffers )
		delete[] m_pBuffers;
}
//< Initializing the buffer store
HRESULT	CQueueBuffer::Initializing(const int _nBufSize)
{
	if( _nBufSize <= 0 && _nBufSize >= MAX_BUFFER_SIZE)
	{
		return FALSE;
	}

	//< allocate memory
	m_pBuffers = new BYTE[_nBufSize];

	//< Set memory to zero
	memset(m_pBuffers,0,_nBufSize);

	//< set buffer size
	m_dBufferSize = _nBufSize;

	//< set the pointer location
	m_pWritePoint = m_pReadPoint = m_pBuffers;

	m_dNowBufferSize = 0;

	return TRUE;
}
//< push data into the buffer store
//< The reason this function make here, sometimes you should be push data on its own
void		CQueueBuffer::PushData(BYTE* _pData, const int _nLength)
{
	WORD nSize = 0;
	WORD nTempSize = 0;

	//< Get Size from front packet bytes
	nSize = *reinterpret_cast<WORD*>(_pData+0);

	if (nSize <= 0)
	{
		printf("Don't Processing Packet : Memory(%p) \n",this);
		return;
	}

	//< Get space  from buffer store
	//	nTempSize = m_dBufferSize - m_dReadPos;
	//< The reason compare to 2 , size is 2 front of packet header
	//< for checking size, because if program know size, find all packet 
	if ( m_dBufferSize - m_dWritePos  >=  nSize )
	{
		memcpy_s(m_pWritePoint,nSize,_pData,nSize);
		m_pWritePoint			+= nSize;
		m_dWritePos			+= nSize;
	}
	else
	{
		//< packet store minimum size is 2 ( because if you'll read packet, first need packet size
		if( (m_dBufferSize - m_dWritePos) < 2 )
		{
			m_pWritePoint		= m_pBuffers;
			m_dWritePos		= 0;
			memcpy_s(m_pWritePoint,nSize,_pData,nSize);
			m_pWritePoint			+= nSize;
			m_dWritePos			+= nSize;
		}
		else
		{
			nTempSize = (WORD)(m_dBufferSize - m_dWritePos);

			//< memory copy only partly
			memcpy_s(m_pWritePoint,nTempSize,_pData,nTempSize);

			//< go to first readpos
			m_pWritePoint		= m_pBuffers;
			m_dWritePos		= 0;
			nTempSize			= nSize - nTempSize;

			//< memory copy remaining
			memcpy_s(m_pWritePoint,nTempSize,_pData+(nSize - nTempSize),nTempSize);
			m_pWritePoint			+= nTempSize;
			m_dWritePos			+= nTempSize;
		}

	}

	//< increase writePos amount of nSize
	m_dNowBufferSize		+= nSize;
	m_dNowPacketCount		++;
	m_dPushCount			++;
}
//< pop data into the buffer store 
BUF_PACKET_TYPE	CQueueBuffer::Popdata()
{
	BUF_PACKET_TYPE	pPacket;
	int				nPacketSize = 0;

	//< if buffer have not packet , return nullptr
	if( m_dNowPacketCount <= 0 || m_dNowBufferSize <= 0 )
	{
		pPacket._pSize = nullptr;
		return pPacket;
	}

	if( m_dBufferSize - m_dReadPos <= 1)
	{
		m_dReadPos	= 0;
		m_pReadPoint	= m_pBuffers;
	}

	//< Get size from front packet at readpoint
	nPacketSize = *reinterpret_cast<WORD*>(m_pReadPoint);


	//< [Check size] if size is smaller than 0 , either don't find or wrong size
	if( nPacketSize <= 0 )
	{
		printf("Faile Load to Data Size or wrong size \n");
		pPacket._pSize = nullptr;
		return pPacket;
	}

	//< Get packet
	pPacket = GetPacket(nPacketSize);

	return pPacket;
}
//< Get packet pointer from this function
BUF_PACKET_TYPE	CQueueBuffer::GetPacket(const int _nPacketSize)
{
	BUF_PACKET_TYPE	pPacket;
	int				nTempLoadPacketSize;

	//< save pointer at size location in the pBuffer Store
	pPacket._pSize = m_pReadPoint;
	//< value save
	pPacket._pData = m_bTempPacket;

	//< check size 
	if( (unsigned int)_nPacketSize <= m_dBufferSize - m_dReadPos )
	{
		//< 2 = packet size
		pPacket._pData = m_pReadPoint + 2;

		m_pReadPoint			+= _nPacketSize;
		m_dReadPos			+= _nPacketSize;
	}
	else
	{
		//< memcpy [[ לי׃ר ]] [[ 2 = packet size ]]
		//< @@@@------@@@@@
		memcpy_s(m_bTempPacket, m_dBufferSize - m_dReadPos - 2, m_pReadPoint + 2, m_dBufferSize - m_dReadPos - 2);
		nTempLoadPacketSize = m_dBufferSize - m_dReadPos - 2;
		m_dReadPos = 0;
		m_pReadPoint = m_pBuffers;
		memcpy_s(m_bTempPacket + nTempLoadPacketSize, _nPacketSize - nTempLoadPacketSize - 2 , m_pReadPoint, _nPacketSize - nTempLoadPacketSize - 2 );

		m_pReadPoint			+=	(_nPacketSize - nTempLoadPacketSize - 2);
		m_dReadPos			+=	(_nPacketSize - nTempLoadPacketSize - 2);
	}
	
	
	m_dNowBufferSize		-= _nPacketSize;
	m_dNowPacketCount		--;
	m_dPopCount			++;
	return pPacket;
}

//< Get Read,Write point For Debug
BYTE*	CQueueBuffer::GetReadPoint()
{
	return m_pReadPoint;
}
BYTE*	CQueueBuffer::GetWirtePoint()
{
	return m_pWritePoint;
}
DWORD	CQueueBuffer::GetBufferSize()
{
	return m_dBufferSize;
}
DWORD	CQueueBuffer::GetPacketCount()
{
	return m_dNowPacketCount;
}
DWORD	CQueueBuffer::GetPushCount()
{
	return m_dPushCount;
}
DWORD	CQueueBuffer::GetPopCount()
{
	return m_dPopCount;
}
DWORD	CQueueBuffer::GetNowBufferSize()
{
	return m_dNowBufferSize;
}
char*	CQueueBuffer::GetRecvPointer()
{
	if( m_dBufferSize - m_dWritePos < 2 )
	{
		m_dWritePos		= 0;
		m_pWritePoint		= m_pBuffers;
	}
	return (char*)m_pReadPoint;
}
VOID		CQueueBuffer::Increasepacket(const int _nPacketSize)
{
	m_pWritePoint			+= _nPacketSize;
	m_dWritePos			+= _nPacketSize;
	m_dNowBufferSize		+= _nPacketSize;
	m_dNowPacketCount		++;
	m_dPushCount			++;
}