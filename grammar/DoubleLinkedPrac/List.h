//
//  List.h
//  DoubleLinkedPrac
//
//  Created by Cory on 2018. 8. 28..
//  Copyright © 2018년 Cory. All rights reserved.
//

//#ifndef List_h
//#define List_h

#pragma once // 이 헤더파일을 딱 1번만 포함시키겠다라는 의미

#include <iostream>

using namespace std;

// 헤더파일에는 보통 함수 선언부분을 만들어 준다.
enum MAIN_MENU {
    MM_NONE,
    MM_INSERT,
    MM_DELETE,
    MM_SEARCH,
    MM_OUTPUT,
    MM_SORT,
    MM_EXIT
};

enum OUTPUT_TYPE {
    OT_NONE,
    OT_OUTPUT,
    OT_INVERSE
};

enum SORT_TYPE {
    ST_NONE,
    ST_NUMBER,
    ST_AVG
};

enum SORT_OPTION {
    SO_NONE,
    SO_CRIVE,
    SO_DESCRIVE
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

typedef struct _tagNode {
    STUDENT tStudent;
    _tagNode* pNext;
    _tagNode* pPrev;
}NODE, *PNODE;

typedef struct _tagList{
    // pBegin 과 pEnd 는 명시적으로 처음과 끝을 의미하도록 만든다. 실제 데이터를 저장하는 노드는 X
    // 실제 데이터를 저장하는 노드는 pBegin 과 pEnd 사이에 존재하게 만든다.
    PNODE pBegin;
    PNODE pEnd;
    int iSize;
}LIST, *PLIST;

static int inputInt() {
    int iInput;
    cin >> iInput;
    
    if(cin.fail()) {
        cin.clear();
        cin.ignore(1024, '\n');
        return INT_MAX;
    }
    return iInput;
}

static void inputString(char* pString, int iSize) {
    cin.clear(); // 뭔가 있으면 지운다.
    cin.ignore(1024, '\n');
    cin.getline(pString, iSize - 1);
    
}

void initList(PLIST pList);
void destroyList(PLIST pList);
void pushBack(PLIST pList);
void pushFront(PLIST pList);
void outputStudent(const PSTUDENT pStudent);
void outputList(PLIST pList);
void searchList(PLIST pList);
void deleteList(PLIST pList);
void sortList(PLIST pList);


//#endif /* List_h */









