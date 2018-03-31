#ifndef _COMMONHEADER_H__
#define _COMMONHEADER_H__


#include <list>
#include <vector>
#include <tchar.h>


#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"mswsock.lib")


////////////////////////////////////////////////////////
//////////////// 메모리 관련 매크로 기능 ///////////////
////////////////////////////////////////////////////////
#define DEF_SHARED_MEMORY_NAME		_T("CL_ShareMemory")
//< 200MB
#define DEF_SIZE					205120



////////////////////////////////////////////////////////
//////////////// 고정 매크로 기능 //////////////////////
////////////////////////////////////////////////////////
#define SAFE_DELETE(p)			{ if(p) { delete (p);		(p)=NULL; }		}
#define SAFE_RELEASE(p)			{ if(p) { (p)->Release();	(p)=NULL; }		}
#define SAFE_DELETE_ARRAY(p)	{ if(p) { delete[] (p);		(p)=NULL; }		}
#define SAFE_CLOSE_HANDLE(p)	{ if(p) { CloseHandle(p);	(p) = NULL; }	}

// 최대값 매크로
#define MAX(a, b)		( ((a) > (b)) ? (a) : (b) ) 
// 최소값 매크로
#define MIN(a, b)		( ((a) < (b)) ? (a) : (b) ) 
// 반올림 매크로
#define ROUND(x, digit) (floor((x) * pow(static_cast<float>(10), digit) + 0.5f) / pow(static_cast<float>(10), digit))
// 버림 매크로
#define	FLOOR(x)		( static_cast<int>(x) )
// 올림 매크로
#define CEIL(x)			( static_cast<int>(x + 1) )

////////////////////////////////////////////////////////
//////////////// 자료        기능 //////////////////////
////////////////////////////////////////////////////////


#endif // _COMMONHEADER_H__