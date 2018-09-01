#include <iostream>

using namespace std;

//int main() {
//    /*
//     레퍼런스: 다른 대상을 참조하게 만들어주는 기능
//     참조를 하게 되면 그 대상에 접근하여 값을 변경할 수 있다.
//     단, 레퍼런스는 처음 레퍼런스 변수 생성시 참조하는 대상을 지정해 주어야 한다.
//
//     변수타임 &레퍼런스명 = 참조할 변수명;
//     */
//    int iNumber = 100;
//    int iNumber1 = 9999;
//
//    int &iRefNum = iNumber;
//    int* pNum = &iNumber;
//
//    iRefNum = 1234;
//    iRefNum = iNumber1;
//
//    cout << iNumber << endl;
//    cout << sizeof(iRefNum) << endl;
//
//    return 0;
//}

/*
 객체(object): C++ 에서는 각 변수도 객체로 취급할 수 있다. 하지만 객체지향 프로그래밍을 지원하기 위해 제공되는 수단은 class
              class 는 객체를 만들기 위한 틀

 객체지향 프로그래밍(OOP): 객체들의 관계를 설정해주어서 부품을 조립하듯이 객체들을 조립하여 완성된 프로그램을 만들어 나가는 방식.

 클래스 선언방법: class 클래스명 {}; 의 형태로 선언한다.
 코드블럭안에 멤버변수를 넣어줄 수 있다. 단, 함수도 멤버로 만들 수 있다.

 <클래스의 4가지 속성>
 캡슐화: 클래스 안에 속하는 여러 변수 혹은 함수를 하나의 클래스로 묶어주는 기능
 은닉화: 클래스 안에 속하는 변수 혹은 함수를 내가 원하는 부분만 외부에 공개, 나머지는 공개X
       - public:    클래스 내부와 외부에서 모두 접근 가능한 방법
       - protected: 클래스 외부에서는 접근이 불가능하고 자기자신 내부나 자식 클래스 내부에서는 접근이 가능
       - private:   자기자신 내부에서만 접근이 가능하고 외부나 자식 내부에서는 접근이 불가
 상속성: 클래스는 클래스와 클래스간의 부모, 자식 관계를 형성할 수 있다.
       - 자식 클래스는 부모 클래스의 멤버를 물려받아 자신의 것처럼 사용할 수 있다.(단, private 은 불가능)
 다형성: 부모 자식 관계로 상속관계가 형성되어 있는 클래스간에 서로 형변환이 가능한 성질

 <생성자와 소멸자> => 이는 public 으로 선언되어야 한다.
 생성자: 어떤 클래스를 이용해서 객체를 생성할때 자동으로 호출되는 함수. 객체 생성시에 호출되는 함수이기 때문에 멤버변수를 초기화할때 자주 사용
       생성자를 만들어주지 않을 경우 내부적으로 기본 생성자가 제공되어 기본 생성자를 자동으로 호출하게 된다.
       - class명() {} 으로 선언
 소멸자: 어떤 클래스를 이용해서 생성산 객체가 메모리에서 해제될 때, 자동으로 호출되는 함수. 객체를 사용하고 난 뒤 마무리 작업을 해줄때 자주 사용
       - ~클래스명() {} 의 형태로 선
 */

class CTracer {

public:
    // 생성자
    CTracer() {
        cout << "Tracer 생성자" << endl;
        strcpy(m_strName, "트레이서");
    }

    CTracer(char* pName) {
        cout << "Name 생성자" << endl;
        strcpy(m_strName, pName);
    }

    CTracer(char* pName, int iFlash) {
        cout << "Name, iFlash 생성자" << endl;
        strcpy(m_strName, pName);
        m_iFlash = iFlash;
        /* 위는 아래와 동일
         * int a;
         * a = 10;
         */
    }

    // Initializer (초기값을 : 뒤에 넣는다.)
    CTracer(char *pName, int iFlash, int iBack):
    m_iFlash(iFlash),
    m_iBack(iBack)
    {
        cout << "Name, iFlash, iBack 생성자" << endl;
        strcpy(m_strName, pName);
        // 위는 아래와 동일
        // int b = 10;
    }

    // 소멸자
    ~CTracer() {
        cout << "Tracer 소멸자" << endl;
    }

    // 클래스의 멤버변수를 선언할 때는 m_를 붙여준다.(?그냥 스타일) - 기본은 private
    char m_strName[32];

public: // public 키워드 아래에 있는 멤버는 모두 외부에서 접근이 가능하다.
    int m_iAttack;
    int m_iHP;

private: //
    int m_iFlash;

private:
    int m_iBack;

public:
    void output() {
        cout << "Tracer Output" << endl;
        cout << "Name: " << m_strName << endl;
    }
};

int main() {

    // 생성자에 값을 넣을 수 있다.
    CTracer tr1("한조", 3, 1);

    // main() 함수 안은 클래스 외부이기 때문에 public 으로 설정되어 있는 멤버에만 접근이 가능하다.
    tr1.output();

   return 0;
}






