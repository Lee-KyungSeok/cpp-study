//
//  main.cpp
//  structEx
//
//  Created by Cory on 2018. 8. 23..
//  Copyright © 2018년 Cory. All rights reserved.
//

// 구조체 : 관련있는 변수들을 모아서 하나의 새로운 타입ㅇㄹ 만들어주는 기능
// 형태 : struct 구조체명 {}; 형태

// 배열과 구조체의 공통점
// - 데이터의 집합
// - 연속된 메모리 블럭에 할당

// 참고 : cin.ignore(1024, '\n') 과 같이 하여 다시 특정 범위 안에서 특정 문자를 찾아 지울 수 있다.

#include <iostream>
using namespace std;

#define NAME_SIZE 32 // 상수

struct _tagStudent {
    char strName[NAME_SIZE];
    int iKor;
    int iEng;
    int iMath;
    int iTotal;
    float fAvg;
};

int main(int argc, const char * argv[]) {
    
    _tagStudent tStudent = {}; // 구조체 전체를 0으로 초기화 초기화하지 않으면 내부 변수가 쓰레기값이 들어감, 특히 문자열의 경우 안해주면 안넣은데에 모두 쓰레기!
    _tagStudent tStudentAr[100] = {};
    
    // 구조체 멤버에 접근할 때는 . 을 이용하여 접근
    tStudent.iKor = 100;
    // 문자열을 배열에 넣어줄 때는 문자열을 복사해서 넣어주어야 한다. 단순대입으로는 불가
    strcpy(tStudent.strName, "가나다라");
    cout << "이름길이: " << strlen(tStudent.strName) << endl;
    
    // strcat 은 문자열을 붙임
    strcat(tStudent.strName, "ghkrdls");
    cout << "이름: " << tStudent.strName << endl;
    
    // strcmp 는 두 문자열을 비교
    
    return 0;
}
