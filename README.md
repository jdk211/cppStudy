# cppStudy
study

#Cars

포인터 관련 : 이전에는 ref로 넘겨주는게 많았음
shared_ptr : 둘 이상의 소유자가 메모리에 있는 개체에 수명을 관리하는 경우, 참조 횟수를 카운트함
unique_ptr : 포인터를 공유하지 않고 함수에 값으로 전달하거나, 복사본을 만들어야하는 C++ 표준 라이브러리 알고리즘에서 사용할 수 없음.
             이동만 가능하다 std::move()사용

이동, 복사, 참조
A.data B.data가 있을때 
이동 : B = std::move(A) 이동을 하면 A.data는 빈 페이지가 되고 B.data는 A.data의 메모리 소유권을 갖습니다.
      이점은 새로 메모리를 할당하지 않아도 되고 이미 메모리에 할당 된 소유권만 B에 넘겨주기 때문에 동작이 빠르다(*주의* 이동 후 A는 사용을 할 수 없다.)
복사 : B = A는 복사가 발생하고 B.data에 A.data의 값이 들어가고 A.data도 사용이 가능하다.


const std::string& 무조건 쓰고보기 습관들이기

c++ lambda
[my_mod](int v_)->int{return v_ % my_mode;}();
[introducer capture](parameters)->return type{statement}();
[]캡쳐 블록 (사용시 외부 변수를 캡쳐해 람다 몸통에서 사용가능)
()전달 인자
->반환타입 (생략 가능)
{}함수 몸통



시스템 구조 관련 : Entity Component, Data Driven

마지막 파라미터는 pred 프레..? 구조체까지 만들어줘야하는 상황이 발생
std::remove_if(m_vecComponents.begin(), m_vecComponents.end(), ComponentNameEqual(componentName));

vector.push_back( value ) -> 값의 복사가 일어남
vector.push_back(std::unique_ptr<T>Value) -> 값의 복사로인해 오류!
vector.push_back(std::move(std::unique_ptr<T>Value))) -> 이동해야한다.
vector.erase( iterator::begin + index)

이름이 있는 클래스... A a;
이름이 없는 클래스... A();
a = A(); move operator
A a = A(); move constructor

a = 1 + 2 
lvalue = rvalue
