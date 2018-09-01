#include <iostream>
#include <functional>

using namespace std;

/*
 함수 포인터: 함수의 메모리 주소를 저장하기 위한 포인터 변수를 선언할 수 있다.
 전역함수의 경우 함수명이 곧 함수의 메모리 주소

 함수포인터 선언: 반환타입(*포인터변수명)(인자타입); 의 형태로 구성
 */

int mSum(int a, int b) {
    return a+b;
}

int mOutSub(int a, int b) {
    cout << a - b << endl;
    return a-b;
}

float TestFunc(float a) {
    cout << a << endl;

    return a;
}

void outputFunction() {
    cout << "Output Function" << endl;
}

class CHanzo {

public:
    CHanzo() {
        m_iTest = 10;
    }
    ~CHanzo() {

    }

public:
    int m_iTest;

public:
    void output() {
        cout << "Hanzo" << endl;
        // this-> 는 생략할 수 있다.
        cout << "Test: " << this->m_iTest << endl;
    }
};

typedef struct _tagPoint {
    int x;
    int y;

    _tagPoint(): x(0), y(0) {

    }

    _tagPoint(int _x, int _y): x(_x), y(_y) {

    }

    _tagPoint(const _tagPoint& pt) {
        // 얕은 복사를 한다. 즉, this 는 자기 자신의 포인터이고 *를 붙여 자기자신을 역참조하여 모든 데이터를 복사하게 된다.
        *this = pt;
    }

    _tagPoint operator + (const _tagPoint& pt) {
        _tagPoint result;
        result.x = x + pt.x;
        result.y = y + pt.y;
        return result;
    }

    // 오버로딩 가능
    _tagPoint operator + (int a) {
        _tagPoint result;
        result.x = x + a;
        result.y = y + a;
        return result;
    }

    void operator += (int a) {
        x += a;
        y += a;
    }

    void operator ++ () {
        x++;
        y++;
    }

    void operator -- () {
        x--;
        y--;
    }

    void operator << (const _tagPoint& pt) {
        x = pt.x;
        y = pt.y;
    }

    void operator >> (_tagPoint& pt) {
        pt.x = x;
        pt.y = y;
    }
}POINT, PPOINT;

int main() {
    int(*pFunc)(int, int) = mSum;

    cout << pFunc(10,20) << endl;

    pFunc = mOutSub;
    pFunc(10, 20);

    void(*pFunc1)() = outputFunction;
    pFunc1();

    CHanzo hanzo1, hanzo2;

    hanzo1.m_iTest = 100;
    hanzo2.m_iTest = 200;

    // this 포인터: 클래스 안에서 this 를 사용할 경우 해당 개게의 메모리 주소가 된다. 즉, 자기 자신의 포인터이다.
    // 멤버함수를 호출할 때 this 를 호출자로 세팅
    hanzo1.output();
    hanzo2.output();

    // 멤버함수 포인터 선언시 포인터 변수 이름 앞에 클래스명:: 을 붙여준다.
    void (CHanzo::*pFunc2)() = &CHanzo::output;
    (hanzo1.*pFunc2)(); // 다음과 같이 사용 가능하다.

    /*
     function 기능은 C++11 부터 지원해주는 기능. 이 기능은 함수포인터를 전역 멤버 가리지 않고 쉽게
     주소를 저장해서 호출해줄 수 있도록 만들어주는 기능

     선언방법: function<반환타입(인자타입)> 변수명; 의 형태로 선언
    */
    cout << "========== Functional ==========" << endl;
    function<void()> func;
    function<void()> func1;
    func = bind(outputFunction);
    func1 = bind(&CHanzo::output, &hanzo1);
    func1 = bind(&CHanzo::output, &hanzo2);

    func();
    func1();

    function<int(int, int)> func3;
    // 함수에 인자가 있을 경우 placeholders 를 이용해서 인자의 순서를 정의할 수 있다.
    // 아래처럼 2,1 로 넣어주면 인자가 서로 바뀌게 된다.
    func3 = bind(mOutSub, placeholders::_2, placeholders::_1);
    // 위에서 2,1 로 바꿨으므로 b=10, a=20 이 된다.
    func3(10, 20);

    function<float(float)> func4;
    func4 = bind(TestFunc, placeholders::_1);
    func4(3.14f);


    cout << "========== Point ==========" << endl;
    POINT pt1(10, 20), pt2(30, 40), pt3;

    // POINT 구조체는 + 연산자가 operator 로 재정의 되어 있다.
    // 그래서 + 연산이 가능하게 되고 pt1 의 + 연산자 함수를 호출해주는 개념이다.
    // pt2  인자로 넘겨준다.
    pt3 = pt1 + pt2;

    cout << "x: " << pt3.x << "\t" << "y: " << pt3.y << endl;

    pt3 << pt1;
    cout << "x: " << pt3.x << "\t" << "y: " << pt3.y << endl;

    pt2 >> pt3;
    cout << "x: " << pt3.x << "\t" << "y: " << pt3.y << endl;

    pt3 = pt1 + 100 + 200;
    cout << "x: " << pt3.x << "\t" << "y: " << pt3.y << endl;

    pt3 += 30;
    cout << "x: " << pt3.x << "\t" << "y: " << pt3.y << endl;

    ++pt3;
    cout << "x: " << pt3.x << "\t" << "y: " << pt3.y << endl;

    --pt3;
    cout << "x: " << pt3.x << "\t" << "y: " << pt3.y << endl;

    return 0;
}