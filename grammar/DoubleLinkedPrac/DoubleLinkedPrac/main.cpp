//
//  main.cpp
//  DoubleLinkedPrac
//
//  Created by Cory on 2018. 8. 28..
//  Copyright © 2018년 Cory. All rights reserved.
//

// 사용자가 만든 헤더파일을 포함시킬 때는 "" 안에 적어준다.
#include "List.h"

int outputMenu() {
    system("cls");
    cout << "1. 학생 추가" << endl;
    cout << "2. 학생 삭제" << endl;
    cout << "3. 학생 탐색" << endl;
    cout << "4. 학생 출력" << endl;
    cout << "5. 학생 출력" << endl;
    cout << "6. 종료" << endl;
    cout << "메뉴를 선택하세요: ";
    int iInput = inputInt();
    
    if(iInput <= MM_NONE || iInput > MM_EXIT) {
        return MM_NONE;
    }
    return iInput;
}

int main(int argc, const char * argv[]) {
    LIST tList;
    
    initList(&tList);
    
    while (true) {
        int iMenu = outputMenu();
        if(iMenu == MM_EXIT) {
            break;
        }
        
        switch (iMenu) {
            case MM_INSERT:
                pushBack(&tList);
                break;
            case MM_DELETE:
                deleteList(&tList);
                break;
            case MM_SEARCH:
                searchList(&tList);
                break;
            case MM_OUTPUT:
                outputList(&tList);
                break;
            case MM_SORT:
                sortList(&tList);
                break;
        }
    }
    
    destroyList(&tList);
    
    return 0;
}



















