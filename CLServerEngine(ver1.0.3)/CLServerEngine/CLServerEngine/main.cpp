//#include <iostream>
//#include <conio.h>
//#include <Windows.h>
//#include <process.h>
//#include <map>
//#include <functional>
//
//using namespace std;
//
//class A
//{
//private:
//	//std::map<WORD,void(*)(int,char*)>	m_map;
//	std::map<WORD, std::function<void(int,char*)>>		m_map;
//public:
//	A(){}
//	~A(){}
//	void Run()
//	{
//		(*m_map.begin()).second(17,"dd");
//	}
//	void	 AddProtocol(WORD _wCommandNumber,std::function<void(int,char*)> func )
//	{
//		m_map.insert( make_pair( _wCommandNumber,func ) );
//	}
//
//};
//class B : public A
//{
//private:
//
//
//public:
//	B(){}
//	~B(){}
//	
//	void					sss()
//	{	
//		//< std::placeholders_1,_2는 나중에 따로 값을 넣기 위한 설정		
//		AddProtocol(10, std::bind(&B::Sexy, this, std::placeholders::_1, std::placeholders::_2));
//	}	
//
//	void Sexy(int _num, char* data)
//	{
//		cout << "호호호2" << endl;
//		cout << _num << data << endl;
//	}
//};
//
//int main(void)
//{
//	B b;
//	b.sss();
//	b.Run();
//}


////< 테스트 2번
///* --------------------------------------------------------------------------------- */
//#include <iostream>
//#include <process.h>
//#include <Windows.h>
//#include <functional>
//
//using namespace std;
//
//static unsigned int WINAPI ThreadFunction (void* sfp)
//{	
//	void (*fp)(int,int) = ((void (*)(int,int))(sfp));
//
//	fp(0,1);
//
//	return 0;
//}
//
//void sexy(int a,int b)
//{
//	printf(" 아 들어왔다~~~\n");
//	cout << GetTickCount() << endl;
//}
//
//int main(void)
//{
//	cout << GetTickCount() << endl;
//	_beginthreadex(0,0,ThreadFunction, static_cast<void*>(sexy) ,	0,0);
//	while(1)
//	{
//		if( getchar() == 65)
//			break;
//	}
//	return 0;
//}

//< 테스트 3번
/* --------------------------------------------------------------------------------- */
#include <iostream>
#include "Dispatcher.h"

using namespace std;


int sss()
{
	printf(" 아 들어왔다~~~\n");
	cout << GetTickCount() << endl;
	return 0;
}

int main(void)
{
	CThread	a;
	cout << GetTickCount() << endl;

	a.StartThread(sss);

	while(1)
	{
		if( getchar() == 65)
			break;
	}
	return 0;
}