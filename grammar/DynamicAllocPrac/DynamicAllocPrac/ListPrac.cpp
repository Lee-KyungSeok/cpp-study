//
//  List.cpp
//  DynamicAllocPrac
//
//  Created by Cory on 2018. 8. 28..
//  Copyright © 2018년 Cory. All rights reserved.
//

#include <iostream>

using namespace std;

enum MAIN_MENU {
    MM_NONE,
    MM_INSERT,
    MM_DELETE,
    MM_SEARCH,
    MM_OUTPUT,
    MM_EXIT
};

#define NAME_SIZE 32

typedef struct _tagStudent{
    char strName[NAME_SIZE];
    int iNumber;
    int iKor;
    int iEng;
    int iMath;
    int iTotal;
    float fAvg;
}STUDENT, *PSTUDENT;

/*
 링크드리스트 : 자료구조의 한 종류. 자료구조란 데이터를 관리하는 방법을 의미
 링크드리스트는 데이터 목록을 연결시켜서 접근할 수 있는 구조를 제공
 링크드리스트는 데이터를 저장하기 위한 노드라는 것이 존재한다.
 각 노드의 특징은 다음 노드를 안다는 것(다음 노드의 메모리 주소를 저장한다는 의미)
 
 리스트는 선형구조로 되어 있다. 따라서 배열처럼 특정 요소에 바로 접근이 불가능하다 무조건 앞에서부터 차례대로 타고 들어간다.
 노드를 새로 추가할 때는 노드를 생성하고 마지막 노드에 연결만 해주면 되기 때문에 개수의 제한이 없다.
 */

// 리스트 노드를 만든다.
typedef struct _tagNode {
    STUDENT tStudent;
    _tagNode* pNext;
}NODE, *PNODE;

// 리스트 구조체를 만들어준다.
typedef struct _tagList{
    PNODE pBegin;
    PNODE pEnd;
    int iSize;
}LIST, *PLIST;

int inputInt() {
    int iInput;
    cin >> iInput;
    
    if(cin.fail()) {
        cin.clear();
        cin.ignore(1024, '\n');
        return INT_MAX;
    }
    return iInput;
}

void initList(PLIST pList) {
    // 포인터는 가급적이면 초기화할때 NULL(0) 으로 초기화하는 것이 좋다. (0은 false 0 이 아닌 모든 수는 true 이기 때문이다.)
    // 초기화하지 않을 경우 쓰레기값이 들어가 있는데 이 쓰레기값도 true 이다.
    pList->pBegin = NULL;
    pList->pEnd = NULL;
    pList->iSize = 0;
}

int outputMenu() {
    system("cls");
    cout << "1. 학생 추가" << endl;
    cout << "2. 학생 삭제" << endl;
    cout << "3. 학생 탐색" << endl;
    cout << "4. 학생 출력" << endl;
    cout << "5. 종료" << endl;
    cout << "메뉴를 선택하세요: ";
    int iInput = inputInt();
    
    if(iInput <= MM_NONE || iInput > MM_EXIT) {
        return MM_NONE;
    }
    return iInput;
}

void inputString(char* pString, int iSize) {
    cin.clear(); // 뭔가 있으면 지운다.
    cin.ignore(1024, '\n');
    cin.getline(pString, iSize - 1);
    
}

void insertStudent(PLIST pList) {
    system("cls");
    STUDENT tStudent = {};
    cout << "========== 학생추가 ==========" << endl;
    cout << "이름: ";
    inputString(tStudent.strName, NAME_SIZE);
    cout << "학번: ";
    tStudent.iNumber = inputInt();
    cout << "국어: ";
    tStudent.iKor = inputInt();
    cout << "영어: ";
    tStudent.iEng = inputInt();
    cout << "수학: ";
    tStudent.iMath = inputInt();
    
    tStudent.iTotal = tStudent.iKor + tStudent.iEng + tStudent.iMath;
    tStudent.fAvg = tStudent.iTotal / 3.f;
    
    // 추가할 리스트 노드를 생성한다.
    PNODE pNode = new NODE;
    pNode->pNext = NULL; // 현재 추가하는 노드는 마지막 노드 이므로 다음 노드는 NULL 로 추가
    pNode->tStudent = tStudent; // 헉생정보는 위에서 만든 것을 준다.
    
    // 시작이 없다면 시작으로 설정
    if(pList->pBegin == NULL) {
        pList->pBegin = pNode;
    } else {
        // 시작이 있다면 마지막 노드의 next 에 설정
        pList->pEnd->pNext = pNode;
    }
    // 마지막 노드로 방금 만든 노드를 설정
    pList->pEnd = pNode;
    
    // 크기를 늘린다.
    pList->iSize += 1;
}

void deleteStudent(PLIST pList) {
    system("cls");
    cout << "========== 학생 삭제 ==========" << endl;
    
    cout << "삭제할 이름을 입력하세요";
    char strName[NAME_SIZE] = {};
    inputString(strName, NAME_SIZE);
    
    PNODE pNode = pList->pBegin;
    PNODE pPrev = NULL; // 제일 처음은 이전 노드가 존재하지 않으므로 null 로 처리
    while (pNode != NULL) {
        if(strcmp(pNode->tStudent.strName, strName)) {
            cout << strName << "학생 삭제" << endl;
            // 지울 노드의 다음 노드를 얻어온다.
            PNODE pNext = pNode->pNext;
            // 만약 이전 노드가 NULL 이라면 제일 첫번째 노드가 지워짐
            if(pPrev == NULL) {
                delete pNode;
                pList->pBegin = pNext;
                // 그런데 다음 노드가 없다면 모두 NULL 로 설정
                if(pNext == NULL) {
                    pList->pEnd = NULL;
                }
            }
            
            // 이전 노드가 있을 경우에는 다음 노드로 연결
            else {
                delete pNode;
                pPrev->pNext = pNext;
                
                // 마지막 노드를 지우는 거라면 이전 노드를 마지막 노드로 설정함
                if(pNext==NULL) {
                    pList->pEnd = pPrev;
                }
            }
            
            cout << strName << "학생 삭제 완료" << endl;
            
            pList->iSize -= 1;
            system("pause");
            return;
        }
        
        // 해당 학생이 아니라면 현재 노드가 이전노드가 된다.
        pPrev = pNode;
        pNode = pNode->pNext;
    }
    
    cout << "삭제할 학생을 찾을 수 없습니다." << endl;
    system("pause");
}

void outputStudent(const PSTUDENT pStudent) {
    cout << "이름: " << pStudent->strName << "\t";
    cout << "학번: " << pStudent->iNumber << endl;
    
    cout << "국어: " << pStudent->iKor << "\t";
    cout << "영어: " << pStudent->iEng << "\t";
    cout << "수학: " << pStudent->iMath << endl;
    
    cout << "총점: " << pStudent->iTotal << "\t";
    cout << "평균: " << pStudent->fAvg << endl << endl;
}

void searchStudent(PLIST pList) {
    system("cls");
    cout << "========== 학생 탐색 ==========" << endl;
    cout << "탐색할 이름을 입력하세요: ";
    char strName[NAME_SIZE] = {};
    inputString(strName, NAME_SIZE);
    
    PNODE pNode = pList->pBegin;
    while (pNode != NULL) {
        if(strcmp(pNode->tStudent.strName, strName) == 0) {
            outputStudent(&pNode->tStudent);
            system("pause");
            return;
        }
        
        pNode = pNode->pNext;
    }
    
    cout << "학생을 찾을 수 없습니다." << endl;
    system("pause");
}

void outputStudents(PLIST pList) {
    system("cls");
    cout << "========== 학생 출력 ==========" << endl;
    PNODE pNode = pList->pBegin;
    
    while (pNode != NULL) {
        outputStudent(&pNode->tStudent);
        pNode = pNode->pNext;
    }
    
    cout << "학생수: " << pList->iSize << endl;
}

void clearList(PLIST pList) {
    PNODE pNode = pList->pBegin;
    while (pNode != NULL) {
        PNODE pNext = pNode->pNext;
        delete pNode;
        pNode = pNext;
    }
    
    pList->pBegin = NULL;
    pList->pEnd = NULL;
    pList->iSize = 0;
}

int main() {
    
    LIST tList;
    initList(&tList);
    
    while (true) {
        int iMenu = outputMenu();
        if(iMenu == MM_EXIT) {
            break;
        }
        
        switch (iMenu) {
            case MM_INSERT:
                insertStudent(&tList);
                break;
            case MM_DELETE:
                deleteStudent(&tList);
                break;
            case MM_SEARCH:
                searchStudent(&tList);
                break;
            case MM_OUTPUT:
                outputStudents(&tList);
                break;
        }
    }
    
    // 프로그램 종료시 clear
    clearList(&tList);
    
    return 0;
}







