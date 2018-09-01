//
//  main.cpp
//  PointerPrac
//
//  Created by Cory on 2018. 8. 24..
//  Copyright © 2018년 Cory. All rights reserved.
//

#include <iostream>

using namespace std;

struct _tagStudent {
    int iKor;
    int iEng;
    int iMath;
    int iTotal;
    float fAvg;
};

int main(int argc, const char * argv[]) {
    
    /*
     포인터: 가리키다. 일반 변수는 일반적인 값을 저장하지만 포인터는 메모리 주소를 저장한다. 모든 변수 타입은 포인터 타입을 선언하 수 있다.
     int 변수의 주소는 int 포인터 변수에 저장을 해야 한다.
     포인터는 메모리 주소를 담아놓는 변수이기 때문에 x86 으로 개발할때는 무조건 4byte 가 나온다. x64 일때는 8byte 가 나온다.
     
     따라서 포인터는 반드시 다른 변수의 메모리 주소를 가지고 있어야 일을 할 수 있는데 가지고 있는 그 메모리 주소에 접근해서 값을 제어할 수 있다.
     
     형태: 변수타입 *변수명; 의 형태로 선언
     */
    int iNubmer = 100;
    // 변수 선언시 *을 붙여주면 해당 타입의 포인터 변수가 선언된다.
    // 변수 앞에 &를 붙여주면 해당 변수의 메모리 주소가 된다.
    // pNum 은 iNumber 변수의 메모리 주소를 값으로 갖게 된다. 따라서 PNum 을 이용해서 iNumber 의 값을 제어할 수 있게 된다.
    int *pNum = &iNubmer;
    
    // 아래는 모두 8바이트가 나옴
    cout << sizeof(int*) << endl;
    cout << sizeof(char*) << endl;
    cout << sizeof(double*) << endl;
    
    cout << "INumber Value: " << iNubmer << endl;
    cout << "INumber Address: " << &iNubmer << endl;
    cout << "pNum Value: " << pNum << endl;
    cout << "pNum Address: " << &pNum << endl;
    
    // pNum 을 이용해서 iNumber 의 값을 제어
    // 역참조를 이용해서 값을 얻어오거나 변경할 수 있다.
    // 역참조는 포인터 변수 앞에 *을 붙이게 되면 역참조가 된다.
    cout << *pNum << endl;
    *pNum = 1234;
    cout << "INumber Value(edited): " << iNubmer << endl;
    
    
    /*
     포인터와 배열의 관계: 배열명은 포인터다. 배열명 자체가 해당 배열의 메모리에서의 시작점 주소를 의미한다.
     */
    int iArray[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << "Array Address: " << iArray << endl;
    cout << "Array Address: " << &iArray[0] << endl;
    
    // 포인터, 배열로 접근이 가능
    int *pArray = iArray;
    cout << pArray[2] << endl;
    
    /*
     포인터 연산
     : +, - 연산을 제공, ++, -- 도 가능한데 1을 증가하게되면 단순히 메모리 주소값이 1증가하는 것 X.
      int 포인터의 경우 int 타입의 메모리 주소를 갖게 되는데 메모리 주소에 1을 더해주면 1 증가가 아닌
      가리키는 해당 포인터 타입의 변수타입 크기만큼 증가한다.
      즉, int 포인터이므로 int의 크기인 4만큼 값이 증가하게 된다.
     */
    cout << pArray << endl; // 주소값
    cout << pArray + 2 << endl; // 8만큼 주소값이 증가하게 된다.
    cout << *pArray << endl; // 1 (배열의 첫번째)
    cout << *(pArray + 2) << endl; //3 (배열의 세번째)
    cout << *pArray + 100 << endl; // 101 (포인터로 가리킨 변수에 100 을 더하기 때문)
    
    /*
     char 포인터
     */
    char *pText = "테스트 문자열";
    cout << pText << endl;
    cout << (int*)pText << endl; // 주소값
    
    pText = "abcd";
    cout << pText << endl;
    cout << (int*)pText << endl; // 주소값이 변화한다.
    
    pText = "abcd";
    cout << pText << endl;
    cout << (int*)pText << endl; // 같은 값을 넣으면 주소값이 변하지 않는다.
    
    
    char str[8] = "abcdefg";
    cout << str << endl;
    // 아래는 동일한 값을 가지게 된다 (배열이기 때문)
    cout << (int*)str << endl;
    cout << (int*)&str[0] << endl;
    
    
    /*
     구조체 포인터
     */
    _tagStudent tStudent = {};
    tStudent.iKor = 100;
    _tagStudent *pStudent = &tStudent;
    
    // 연산자 우선순위 때문에 . 을 먼저 인식하게 된다. 메모리 주소 . 은 잘못된 문법이다. 그러므로 *pStudent 를 괄호로 감싸준 후에 . 을 이용해서
    
    // 가리키는 대상의 멤버변수에 접근해야 한다.
    (*pStudent).iKor = 50;
    cout << tStudent.iKor << endl;
    
    // 메모리주소 -> 를 이용해서 가리키는 대상의 멤버에 접근할 수 있다. (위와 같은 형태이다)
    pStudent -> iKor = 80;
    cout << tStudent.iKor << endl;
    
    
    /*
     Void 포인터
     : void* 변수를 선언하게 되면 이 변수는 어떤 타입의 메모리 주소든 모두 저장 가능하다.
       단, 역참조가 불가능하고 메모리 주소만 저장 가능하다.
     */
    void* pVoid = &iNubmer;
    cout << "iNumber Address: " << pVoid << endl;
//    *pVoid = 10 ; 과 같은건 불가능하다.
    // 형변환은 사용 가능
    int* pConvert = (int*)pVoid;
    *pConvert = 3000;
    cout << "iNumber Address: " << pVoid << endl;
    cout << "iNumber Address: " << pConvert << endl;
    cout << "iNumber Value: " << *pConvert << endl;
    // 아래와 같이도 가능
    *((int*)pVoid) = 999;
    cout << "iNumber Value: " << *pConvert << endl; // 999 로 변경됨
    
    // void 변수에는 어떤 메모리 주소던지 다시 적용 가능
    pVoid = &tStudent;
    cout << "tStudent Address: " << pVoid << endl;
    
    /*
     이중 포인터
     : *을 두개 붙인다. 일반 포인터 변수가 일반 변수의 메모리 주소를 저장하는 벼수라면
       이중 포인터는 포인터의 포인터. 즉, 이중 포인터는 포인터 변수의 메모리 주소를 저장하는 포인터이다.
     */
    int iNumber1 = 1111;
    int iNumber2 = 2222;
    pNum = &iNumber1;
    
    int **ppNum = &pNum;
    *ppNum = &iNumber2; // 주소값을 변경시킴
    *pNum = 3333; // 값을 변경시킴
    
    cout << system("cls") << endl;
    cout << "iNumber1: " << iNumber1 << endl;
    cout << "iNumber1 Addr: " << &iNumber1 << endl;
    cout << "iNumber2: " << iNumber2 << endl;
    cout << "iNumber2 Addr: " << &iNumber2 << endl;
    cout << "*pNum:" << *pNum << endl;
    cout << "pNum Value: " << pNum <<endl;
    cout << "pNum Addr: " << &pNum << endl;
    cout << "*ppNum: " << *ppNum << endl; // pNum Value 와 동일
    cout << "**ppNum: " << **ppNum << endl; // 값을 내보냄 (*pNum 과 동일)
    cout << "ppNum Value: " << ppNum << endl; // pNum Addr 과 동일
    cout << "ppNum Addr: " << &ppNum << endl;
    
    return 0;
}






