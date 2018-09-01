//
//  List.cpp
//  DoubleLinkedPrac
//
//  Created by Cory on 2018. 8. 28..
//  Copyright © 2018년 Cory. All rights reserved.
//

#include "List.h"

void initList(PLIST pList) {
    pList->iSize = 0;
    pList->pBegin = new NODE;
    pList->pEnd = new NODE;
    
    // 서로를 참조하게 한다.
    pList->pBegin->pNext = pList->pEnd; // 시작노드의 다음노드는 마지막 노드
    pList->pEnd->pPrev = pList->pBegin; // 마지막 노드의 이전 노드는 시작 노드
    
    pList->pBegin->pPrev = NULL; // 시작노드의 이전노드는 NULL
    pList->pEnd->pNext = NULL; // 마지막노드의 다음노드는 NULL
}

void destroyList(PLIST pList) {
    PNODE pNode = pList->pBegin;
    
    while (pNode != NULL) {
        PNODE pNext = pNode->pNext;
        delete pNode;
        pNode = pNext;
    }
    
    pList->iSize = 0;
    pList->pBegin = NULL;
    pList->pEnd = NULL;
}

void pushBack(PLIST pList) {
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
    
    PNODE pNode = new NODE;
    pNode->tStudent = tStudent;
    
    // 새로 추가된 노드는 end 노드의 이전노드와 end노드 사이에 추가해야 한다.
    PNODE pPrev = pList->pEnd->pPrev; // 이전 노드 구하기
    pPrev->pNext = pNode; // 이전노드의 다음노드는 생성한 노드
    pNode->pPrev = pPrev; // 생성한노드의 이전 노드 지정
    pNode->pNext = pList->pEnd; // 생성한노드의 다음노드는 마지막 노드
    pList->pEnd->pPrev = pNode; // 마지막노드의 이전노드는 생성한 노드
    
    pList->iSize += 1;
}

void pushFront(PLIST pList) {
    
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

void outputList(PLIST pList) {
    int iMenu;
    
    while (true) {
        system("cls");
        cout << "========== 학생 출력 ==========" << endl;
        cout << "1. 정방향 출력" << endl;
        cout << "2. 역방향 출력" << endl;
        cout << "메뉴를 선택하세요: " << endl;
        iMenu = inputInt();
        
        if(iMenu > OT_NONE && iMenu<=OT_INVERSE) {
            break;
        }
    }
    
    PNODE pNode = NULL;
    
    switch (iMenu) {
        case OT_OUTPUT:
            // 추가되는 노드들은 begin 과 end 사이에 배치된다. 그러므로 begin 의 다음 노드를 얻어온다.
            pNode = pList->pBegin->pNext;
            
            while (pNode != pList->pEnd) { // end 노드일때까지 반복
                outputStudent(&pNode->tStudent);
                pNode = pNode->pNext;
            }
            
            cout << "학생수: " << pList->iSize << endl;
            system("pause");
            break;
        case OT_INVERSE:
            pNode = pList->pEnd->pPrev;
            
            while (pNode != pList->pBegin) { // begin 노드일때까지 반복
                outputStudent(&pNode->tStudent);
                pNode = pNode->pPrev;
            }
            
            cout << "학생수: " << pList->iSize << endl;
            system("pause");
            break;
    }
}

void searchList(PLIST pList) {
    system("cls");
    cout << "========== 학생 탐색 ==========" << endl;
    cout << "탐색할 이름을 입력하세요: ";
    char strName[NAME_SIZE] = {};
    inputString(strName, NAME_SIZE);
    
    PNODE pNode = pList->pBegin->pNext;
    
    while (pNode != pList->pEnd) {
        if(strcmp(strName, pNode->tStudent.strName) == 0) {
            outputStudent(&pNode->tStudent);
            system("pause");
            return;
        }
        
        pNode = pNode->pNext;
    }
    
    cout << "학생을 찾을 수 없습니다." << endl;
    system("pause");
}

void deleteList(PLIST pList) {
    system("cls");
    cout << "========== 학생 삭제 ==========" << endl;
    
    cout << "삭제할 이름을 입력하세요";
    char strName[NAME_SIZE] = {};
    inputString(strName, NAME_SIZE);
    
    PNODE pNode = pList->pBegin->pNext;
    
    while (pNode != pList->pEnd) {
        if(strcmp(strName, pNode->tStudent.strName) == 0) {
            cout << strName << "학생 삭제" << endl;
            
            pNode->pPrev->pNext = pNode->pNext;
            pNode->pNext->pPrev = pNode->pPrev;
            
            delete pNode;
            
            (pList->iSize) -= 1;
            
            cout << strName << "학생 삭제 완료" << endl;
            system("pause");
            return;
        }
        
        pNode = pNode->pNext;
    }
    
    cout << "학생을 찾을 수 없습니다." << endl;
    system("pause");
}

void sortList(PLIST pList) {
    system("cls");
    cout << "========== 학생 정렬 ==========" << endl;
    cout << "1. 학점 기준" << endl;
    cout << "2. 평균 기준" << endl;
    cout << "메뉴를 선택하세요: ";
    int iInput = inputInt();
    
    if(iInput <= ST_NONE || iInput > ST_AVG) {
        cout << "잘못 선택하였습니다." << endl;
        system("pause");
        return;
    }
    
    cout << endl;
    cout << "1. 오름 차순" << endl;
    cout << "2. 내림 차순" << endl;
    cout << "메뉴를 선택하세요: ";
    int iOption = inputInt();
    
    if(iOption <= SO_NONE || iInput > SO_DESCRIVE) {
        cout << "잘못 선택하였습니다." << endl;
        system("pause");
        return;
    }
    
    PNODE pFirst = pList->pBegin->pNext;
    PNODE pSecond = pFirst->pNext;
    
    while(pFirst != pList->pEnd->pPrev) {
        
        // second 노드는 first 노드 다음부터 검사 시작
        pSecond = pFirst->pNext;
        while (pSecond != pList->pEnd) {
            bool bSwap = false;
            
            switch (iInput) {
                case ST_NUMBER:
                    switch (iOption) {
                        case SO_CRIVE:
                            if(pFirst->tStudent.iNumber > pSecond->tStudent.iNumber)
                                bSwap = true;
                            break;
                        case SO_DESCRIVE:
                            if(pFirst->tStudent.iNumber < pSecond->tStudent.iNumber)
                                bSwap = true;
                            break;
                    }
                    break;
                case ST_AVG:
                    switch (iOption) {
                        case SO_CRIVE:
                            if(pFirst->tStudent.fAvg > pSecond->tStudent.fAvg)
                                bSwap = true;
                            break;
                        case SO_DESCRIVE:
                            if(pFirst->tStudent.fAvg < pSecond->tStudent.fAvg)
                                bSwap = true;
                            break;
                    }
                    break;
            }
            
            // swap 이 true 이면 두 노드를 바꾼다.
            if(bSwap) {
                PNODE pFirstPrev = pFirst->pPrev;
                PNODE pFirstNext = pFirst->pNext;
                
                PNODE pSecondPrev = pSecond->pPrev;
                PNODE pSecondNext = pSecond->pNext;
                
                pFirstPrev->pNext = pSecond;
                pSecond->pPrev = pFirstPrev;
                
                pFirst->pNext = pSecondNext;
                pSecondNext->pPrev = pFirst;
                
                if(pSecond != pFirstNext) { // 바꾸려는 두 노드가 떨어져 있는 경우
                    pFirstNext->pPrev = pSecond;
                    pSecond->pNext = pFirstNext;
                    
                    pSecondPrev->pNext = pFirst;
                    pFirst->pPrev = pSecondPrev;
                } else { // 붙어 있는 경우
                    pSecond->pNext = pFirst;
                    pFirst->pPrev = pSecond;
                }
                
                // 두 노드를 바꾼다.
                PNODE pTemp = pFirst;
                pFirst = pSecond;
                pSecond = pTemp;
            }
            
            pSecond = pSecond->pNext;
        }
        
        pFirst = pFirst->pNext;
    }
    
    cout << "정렬이 완료되었습니다." << endl;
    system("pause");
}













