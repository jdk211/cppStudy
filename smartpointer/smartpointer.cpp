// smartpointer.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class A
{
public:
	A() {};
	A(int num)
		: m_nNum(num)
	{
	};
	~A() {};

	int GetNum() { return m_nNum; }
	void SetP1(int* num) { m_nNum = *num; }
	void SetP2(int& num) { m_nNum = num; }

private:
	int m_nNum = 0;
};

class B
{
public:
	B() {};
	~B() {};

	template<typename T, class... _Types> void Create(_Types&&... _Args) 
	{
		
	}
};


int main()
{
	//변수명이 smart pointer인것
	shared_ptr<A> a;
	unique_ptr<B> b;

	//선언을 했으면 생성을 해줘야함
	//smart pointer 생성 방법
	a = make_shared<A>(1);
	b = make_unique<B>();

	cout << a.use_count() << endl;
	cout << a->GetNum() << endl;

	shared_ptr<A> a1(make_shared<A>(2));
	//a = a1;
	a1 = a;

	cout << a.use_count() << endl;
	cout << a->GetNum() << endl;

	int na1 = 0;
	int* pa1 = &na1;

	na1 = *pa1;

	vector<A> vecA;
	vector<A*> vecPA;

	//error 
	/*for (const auto& tempA : vecA)
	{
		tempA.GetNum();
	}*/

	for (auto it = vecA.begin(); it != vecA.end(); ++it)
	{
		it->GetNum();
	}

	//vector<A*>::iterator 
	for (auto it = vecPA.begin(); it != vecPA.end(); ++it)
	{
		(*it)->GetNum();
	}

	for (auto& tempA : vecA)
	{
		tempA.GetNum();
	}

	for (const auto& tempA : vecPA)
	{
		tempA->GetNum();
	}

	for (auto& it : vecA)
	{
		it.GetNum();
	}

	for (const auto& it : vecPA)
	{
		it->GetNum();
	}

	na1 = 0;
	pa1 = &na1;

	A TestAFunc;
	TestAFunc.SetP1(&na1);
	TestAFunc.SetP1(pa1);
	TestAFunc.SetP2(na1);
	TestAFunc.SetP2(*pa1);
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
