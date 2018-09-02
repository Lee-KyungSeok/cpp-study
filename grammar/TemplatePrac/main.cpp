#include <iostream>
using  namespace std;

/*
 템플릿: 컴파일 단계에서 타입을 결정짓는 기능.
       타입이 다양하게 바뀔 수 있다.
       template <typename 원하는 이름> 형태로 사용 가능
       template <class 원하는 이름> 형태로 사용 가능

 - ex> template <typename T>
 void output() {
    cout << typeid(T).name() << endl;
 }

 위처럼 함수를 만들고 호출 시
 output<int>();
 output<float>();
 과 같이 해주면 int, float 으로 타입이 정해진다. 상황에 따라 넣어주는 타입이므로 타입이 가변적으로 바뀐다.

 가변 타입은 여러개를 지정해 줄 수 있다.
 - ex> template<typename T, typename T1>
 */

template <typename T>
void outputType() {
    cout << "===== Output Type ======" << endl;
    cout << typeid(T).name() << endl;
}

template <typename T>
void outputData(T data) {
    cout << "===== Output Data ======" << endl;
    cout << typeid(T).name() << endl;
    cout << data << endl;
}

typedef struct _tagStudent {

}STUDENT, *PSTUDENT;

class CCar {
public:
    CCar() {

    }
    ~CCar() {

    }
};

enum ETEST {

};

class CTemplate {
public:
    CTemplate() {

    }
    ~CTemplate() {

    }

public:
    template <class T, class T1>
    void output(T a, T1 b) {
        cout << a << endl;
        cout << b << endl;
    }
};

template <typename T>
class CTemplate1 {
public:
    CTemplate1() {
        cout << "Template1 class Type: " << typeid(T).name() << endl;
    }
    ~CTemplate1() {

    }

private:
    T m_Data;

public:
    void output() {
        cout << typeid(T).name() << endl;
        cout << m_Data << endl;
    }
};

int main() {

    outputType<int>();
    outputType<float>();
    outputType<STUDENT>();
    outputType<CCar>();
    outputType<ETEST>();


    outputData(10);
    outputData(3.14);
    outputData(3232.12f);
    outputData('a');
    outputData("flow");

    cout << endl;


    CTemplate tem;
    tem.output(10, 3.14);

    CTemplate1<int> tem1;
    tem1.output();
    CTemplate1<CTemplate> tem2;

    return 0;
}