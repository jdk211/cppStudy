// test2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <cassert>

class A
{
public:
    A() { printf("default constructor \n"); };
    A(int a) { printf("int constructor \n"); };
    A(const A& other) { printf("copy constructor \n"); };
    A& operator = (const A& other) { printf("copy operator \n");  return *this; };
    A(A&& other) { printf("move constructor \n"); };
    A& operator = (A&& other) { printf("move operator \n"); return *this; };

    ~A() { printf("default destructor \n"); };

    char* p = nullptr; 

    void Test() const
    {
        printf("A Test \n");
    }
};

class B
{
public:
    B(int b) {};
};

template<typename T> void Test(const T& t)
{

}

void TestA(const A& a)
{
    a.Test();
}


void TestA1(A&& a)
{
    a.Test();
}

A TestA2()
{
    A a;

    return a;
}

A TestA3()
{
    return A();
}

void TestB(const B& b)
{

}

int main()
{
    {
        int one = 1;
        int two = 2;
        int three = (one = two); // 대입 연산이다... 
    }

    {
        A a;
        std::cout << std::endl;

        {
            TestA(A());
        }
        std::cout << std::endl;

        {
            TestA(a);
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    {
        A a1;
        A a2;
        A a3 = (a1 = a2);
    }
    std::cout << std::endl;

    {
        A a;
        A a1 = a;
    }
    std::cout << std::endl;

    {
        A a1;
        A a2;
        a1 = a2;
    }
    std::cout << std::endl;

    {
        A a1 = TestA3();
    }
    std::cout << std::endl;

    {
        A a2 = TestA2();
    }
    std::cout << std::endl;

    //전부 다른 생성자가 나옴
    //debug모드랑 release모드랑은 또 다름, 컴파일러에서 최적화 하기 떄문에 발생하는 문제들이 있음
}