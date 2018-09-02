#include <iostream>

using namespace std;

/*
 상속: 클래스는 서로간의 부모의 자식관계를 형성할 수 있다.
      자식 클래스는 부모 클래스의 멤버 사용 가능
      단, public 이나 protected 로 되어 있는 메버들만 사용 가능 (private 은 부모에서만 사용 가능)
 상속의 형태: public, private 상속이 있다.

 다형성: 상속관계에 있는 클래스간에 서로 형변환이 가능한 성질

 가상함수: 함수 오버라이딩, 즉, 함수를 재정의하는 기능
        부모 클래스의 멤버함수 앞에 virtual 키워드를 붙이면 해당 함수는 가상함수가 된다.
        가상함수를 가지고 있는 클래스는 내부적으로 가상함수 테이블(가상함수들의 메모리 주소를 저장하는 테이블)이라는 것을 생성한다.
        소멸자도 가상함수로 사용할 수 있다.(즉, 부모의 소멸자는 가상함수로 만들면 좋다.)
        <참고>
        - CParent 의 output 이 가상함수이고  CChild 클래스의 output 을 재정의한뒤 CChild 객체를 생성하면 가상함수 테이블에는 CChild 클래스의 output 주소가 올라가게 된다.
        - CParent 객체를 생성한다면 CParent 의 output 주소가 올라가게 된다.
        - 따라서 output 함수(가상함수)를 호출하게 되면 먼저 가상함수 테이블을 참조해서 메모리 주소를 확인한다.
 */

class CParent {
public:
    CParent() {
        cout << "CParent 생성자 출력" << endl;
    }
    virtual ~CParent() {
        cout << "CParent 소멸 출력" << endl;
    }

public:
    int m_iA;

protected:
    int m_iB;

private:
    int m_iC;

public:
    virtual void output() {
        cout << "Parent Output Function" << endl;
    }

    // 순수가상함수
    // - 가상함수 뒤에 =0 을 붙여주면 해당 가상함수는 순수가상함수가 된다.
    // - 순수가상함수는 구현부분이 존재하지 않는다.
    // - 순수가상함수를 가지고 있는 클래스를 추상클래스라고 부른다.
    // - 추상 클래스는 인스턴스(객체) 생성이 불가능하다.
    // - 순수가상함수는 정의부분이 없기 때문에 자식에서 반드시 재정의 해야 한다. 즉, 자식에서 재정의해서 사용할 목적으로 만들어주는 함수이다.
    virtual void outputPure() = 0;
};

class CChild: public CParent {
public:
    CChild() {
        m_iB = 200;
//        m_iC = 300; // private 멤버 변수에는 접근 불
        cout << "CChild 생성자 출력" << endl;
    }
    virtual ~CChild() {
        cout << "CChild 소멸 출력" << endl;
    }

protected:
    int m_iD;

public:
    void outputChild() {
        cout << "Child Output Function" << endl;
    }
    virtual void output() {
        CParent::output(); // 부모의 함수를 사용할 수 있다.
        cout << "Child Output Function" << endl;
    }


    virtual void outputPure() {

    }
};

class CChild1: private CParent {
public:
    CChild1() {
        m_iA = 100; // private 으로 상속받으면 안에서만 접근이 가능하다.
        m_iB = 200;
        cout << "CChild1 생성자 출력" << endl;
    }
    ~CChild1() {
        cout << "CChild1 소멸 출력" << endl;
    }

private:
    int m_iD;

public:
    virtual void outputPure() {

    }
};

class CChildChild: public CChild {
public:
    CChildChild() {
        m_iD = 500;
        cout << "CChildChild 생성자 출력" << endl;
    }
    ~CChildChild() {
        cout << "CChildChild 소멸 출력" << endl;
    }

private:
    int m_iE;
};

int main() {

    /*
     * 상속관계에서의 생성자 호출 순서: 부모 -> 자식 순서로 호출
     * 상속관계에서의 소멸자 호출 순서: 자식 -> 부모 순서로 호출
     * */
//    CParent parent; // 추상 클래스이므로 객체 생성 불가
    CChild child;
    CChild1 child1;
    CChildChild childchild;

    child.m_iA = 200;

    // private 으로 상속받으면 parent 에서 public 으로 설정되어 있는 멤버들도 외부에서 접근이 불가능하다.
//    child1.m_iA = 300;


    // <다형성>
    // CChild 클래스는 CParent 클래스를 상속받고 있다.
    // 따라서 new CChild 를 하면 CChild 객체 하나를 생성해주고 그 메모리 주소를 반환한다.
    // 상속관계에 있으므로 아래처럼 CParent* 타입 변수에 이 반환된 주소를 대입해줄 수 있다.
    // 이렇게 자식 메모리 주소를 부모포인터 타입으로 형변환 하는 것을 "업캐스팅" 이라고 한다.
    // - 자식->부모 타입 형변환: 업캐스팅
    // - 부모->자식 타입 형변환: 다운캐스팅
    CParent* pParent = new CChild;

    // 업캐스팅인 경우 자식 클래스 함수에 접근할 수 없다. => pParent는 CParent 포인터 타입이기 때문에 자식 멤버에 접근이 불가능하다.
    // 만약 접근하고 싶다면 형변환 필요
//    pParent->outputChild() // 불가능
    ((CChild*)pParent)->outputChild(); // 가능

    // 다운 캐스팅
    // 그런데 아래에서 CChild1 타입으로 다운캐스팅하여 넣어주게 되면 이 객체를 사용할 때 문제가 될 수 있다.
    // 왜냐하면 위에서 new 로 생성한 객체는 CChild 타입이기 때문(다른 타입으로 형변환이 되어 버렸음에 주의)
    CChild* pChild = (CChild*)pParent;
    CChild1* pChild1 = (CChild1*)pParent;


//    CParent* pParent1 = new CChild1; // private 이라서 사용할 수 없다.
    CParent* pParent2 = new CChildChild;

    // 배열로도 사용 가능
    CParent* pParentArr[2] = {};
    pParentArr[0] = new CChild;
    pParentArr[1] = new CChildChild;

    // 가상함수 호출
    pParent->output(); // 재정의한 함수가 호출된다.
    pParent->CParent::output(); // 부모의 output 함수 호출

    // 만약 가상함수 없이 delete 를 하게 되면 CParent 소멸자만 호출됨에 주의해야 한다.
    // => 근본적으로 pParent 는 cParent 포인터 타입. CParent 포인터 타입이기 때문에 CChild 소멸자가 호출될 수 없다.
    // 가상함수를 사용하면 자식 클래스의 소멸자도 호출된다.
    delete pParent;
    delete pParent2;
//    delete pChild; // 캐스팅 된 것을 delete 하면 CChild 소멸자도 호출된다.

    for(int i=0; i<2; i++) {
        delete pParentArr[i];
    }


    return 0;
}