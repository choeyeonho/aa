#ifndef _COMMONHEADER_H__
#define _COMMONHEADER_H__


#include <list>
#include <vector>
#include <tchar.h>


#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"mswsock.lib")


////////////////////////////////////////////////////////
//////////////// �޸� ���� ��ũ�� ��� ///////////////
////////////////////////////////////////////////////////
#define DEF_SHARED_MEMORY_NAME		_T("CL_ShareMemory")
//< 200MB
#define DEF_SIZE					205120



////////////////////////////////////////////////////////
//////////////// ���� ��ũ�� ��� //////////////////////
////////////////////////////////////////////////////////
#define SAFE_DELETE(p)			{ if(p) { delete (p);		(p)=NULL; }		}
#define SAFE_RELEASE(p)			{ if(p) { (p)->Release();	(p)=NULL; }		}
#define SAFE_DELETE_ARRAY(p)	{ if(p) { delete[] (p);		(p)=NULL; }		}
#define SAFE_CLOSE_HANDLE(p)	{ if(p) { CloseHandle(p);	(p) = NULL; }	}

// �ִ밪 ��ũ��
#define MAX(a, b)		( ((a) > (b)) ? (a) : (b) ) 
// �ּҰ� ��ũ��
#define MIN(a, b)		( ((a) < (b)) ? (a) : (b) ) 
// �ݿø� ��ũ��
#define ROUND(x, digit) (floor((x) * pow(static_cast<float>(10), digit) + 0.5f) / pow(static_cast<float>(10), digit))
// ���� ��ũ��
#define	FLOOR(x)		( static_cast<int>(x) )
// �ø� ��ũ��
#define CEIL(x)			( static_cast<int>(x + 1) )

////////////////////////////////////////////////////////
//////////////// �ڷ�        ��� //////////////////////
////////////////////////////////////////////////////////


#endif // _COMMONHEADER_H__