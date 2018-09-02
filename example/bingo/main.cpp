//
//  main.cpp
//  bingo
//
//  Created by Cory on 2018. 8. 23..
//  Copyright © 2018년 Cory. All rights reserved.
//

#include <iostream>
#include <time.h>

using namespace std;

enum AI_MODE {
    AM_EASY = 1,
    AM_HARD
};

// 빙고 가능성이 가까운 줄 번호를 만든다.
enum LINE_NUMBER {
    LN_H1, LN_H2, LN_H3, LN_H4, LN_H5,
    LN_V1, LN_V2, LN_V3, LN_V4, LN_V5,
    LN_LT, LN_RT
};
void setNumber(int *pArray);
void shuffleBingo(int *pArray); // 포인터를 넘겨서 값을 변경한다.
AI_MODE selectMode();
void printBingo(int *pArray, int bingoLine);
int countBingo(int *pArray);
bool changeNumber(int *pArray, int iInput);

int main(int argc, const char * argv[]) {
    srand((unsigned int)time(0));
    
    int iNumber[25] = {};
    int iAINumber[25] = {}; // ai 버전
    
    // 숫자 넣기
    setNumber(iNumber);
    setNumber(iAINumber);
    
    // 빙고판 섞기
    shuffleBingo(iNumber);
    shuffleBingo(iAINumber);
    
    // AI 난이도를 선택한다.
    int iAIMode = selectMode();
    
    // Easy 모드는 * 로 바뀌지 않는 숫자 목록을 만들어서 그 목록중 하나를 선택
    int iNoneSelect[25] = {}; // 선택 안된 목록
    int iNoneSelectCount = 0; // 선택 안된 갯수
    
    while (true) {
        system("cls");
        
        int iBingo = countBingo(iNumber); // 빙고 갯수
        // 빙고 판 숫자를 5 x 5 로 출력한다.
        cout << "========== Player ==========" << endl;
        printBingo(iNumber, iBingo);
        
        // AI 5 x 5 로 출력한다.
        cout << "========== AI ==========" << endl;
        switch (iAIMode) {
            case AM_EASY:
                cout << "AI MODE: Easy" << endl;
                break;
            case AM_HARD:
                cout << "AI MODE: Hard" << endl;
                break;
        }
        int iAIBingo = countBingo(iAINumber);
        printBingo(iAINumber, iAIBingo);
        
        // 갯수가 5 이상이면 게임 종료
        if(iBingo >= 5) {
            cout << "Player 승리" << endl;
            break;
        } else if(iAIBingo >= 5) {
            cout << "Ai 승리" << endl;
            break;
        }
        
        cout << "숫자를 입력하세요 (0: 종료): ";
        int iInput;
        cin >> iInput;
        
        if(iInput ==0) {
            break;
        }
        
        // 예외처리
        if (iInput <1 || iInput > 25) {
            cout <<"잘못된 입력입니다. 다시 입력해주세요" << endl;
            continue;
        }
        
        // 변화하거나 같은 번호면 true 를 리턴
        bool bAcc = changeNumber(iNumber, iInput);
        // bACC 변수가 true 일 경우 다시 입력하도록 설정
        if(bAcc) {
            cout << "숫자를 다시 입력해주세요" << endl;
            continue;
        }
        
        changeNumber(iAINumber, iInput); // AI 도 변경
        
        
        // AI 가 선택
        switch (iAIMode) {
            case AM_EASY:
                iNoneSelectCount = 0;
                // 선택 안된 숫자 목록을 만든다. (최대 25개)
                for(int i=0; i<25; i++) {
                    // 현재 숫자가 * 가 아닌 경우
                    if(iAINumber[i] != INT_MAX) {
                        iNoneSelect[iNoneSelectCount] = iAINumber[i];
                        iNoneSelectCount++;
                    }
                }
                iInput = iNoneSelect[rand() % iNoneSelectCount]; // 랜덤하게 구할것 (숫자 카운트 내에서 정한다)
                cout << "AI Select: " << iInput << endl << endl;;
                break;
            case AM_HARD:
                // 빙고 가능성이 가장 높은 줄을 찾아서 그 숫자중 하나를 * 로 만든다.
                int iLine = 0;
                int iStarCount = 0;
                int iSaveCount = 0;
                
                // 가로 라인 체크
                for (int i=0; i<5; i++) {
                    iStarCount = 0;
                    for(int j=0; j<5; j++) {
                        if(iAINumber[i*5 + j] == INT_MAX) {
                            iStarCount++;
                        }
                    }
                    // 5 보다 작어여 빙고 줄이 아니다.
                    // 기존에 가장 많은 라인의 별보다 커야 가장 별이 많은 라인
                    // 위 경우에만 라인을 교체하고, 저장된 별 수를 교체
                    if(iStarCount < 5 && iSaveCount < iStarCount) {
                        iLine = i;
                        iSaveCount = iStarCount;
                    }
                }
                
                // 세로 라인 체크 (가로와도 비교)
                for(int i=0; i<5; i++) {
                    iStarCount = 0;
                    for(int j=0; j<5; j++) {
                        if(iAINumber[j*5 + i] == INT_MAX) {
                            iStarCount++;
                        }
                    }
                    
                    if(iStarCount < 5 && iSaveCount < iStarCount) {
                        iLine = i +5; // 새로 라인은 5~9 이기 때문
                        iSaveCount = iStarCount;
                    }
                }
                
                // 대각선 체크
                iStarCount = 0;
                for(int i=0; i<25; i+=6) {
                    if(iAINumber[i] == INT_MAX) {
                        iStarCount++;
                    }
                }
                if(iStarCount<5 && iSaveCount<iStarCount) {
                    iLine = LN_LT;
                    iSaveCount = iStarCount;
                }
                
                iStarCount = 0;
                for(int i=4; i<=20; i+=4) {
                    if(iAINumber[i] == INT_MAX) {
                        iStarCount++;
                    }
                }
                if(iStarCount<5 && iSaveCount<iStarCount) {
                    iLine = LN_RT;
                    iSaveCount = iStarCount;
                }
                
                // 모든 라인을 검사한 후 그 줄에 있는 숫자중 하나(* 제외)를 선택
                if(iLine <= LN_H5) {
                    // 가로줄인 경우
                    for(int i=0; i<5; i++) {
                        if (iAINumber[iLine*5 +i] != INT_MAX) {
                            iInput = iAINumber[iLine*5 + i];
                            break;
                        }
                    }
                } else if(iLine <= LN_V5) {
                    // 세로줄인 경우
                    for(int i=0; i<5; i++) {
                        if (iAINumber[i*5 + iLine-5] != INT_MAX) {
                            iInput = iAINumber[i*5 + iLine-5];
                            break;
                        }
                    }
                } else if(iLine == LN_LT) {
                    // 대각선인 경우
                    for(int i=0; i<25; i+=6) {
                        if(iAINumber[i] == INT_MAX) {
                            iInput = iAINumber[i];
                            break;
                        }
                    }
                } else if(iLine == LN_RT) {
                    // 대각선인 경우
                    for(int i=4; i<=20; i+=4) {
                        if(iAINumber[i] == INT_MAX) {
                            iInput = iAINumber[i];
                            break;
                        }
                    }
                }
                break;
        }
        
        // AI 가 선택한 숫자를 * 로 바꾼다.
        changeNumber(iNumber, iInput);
        changeNumber(iAINumber, iInput);
        
    }
    return 0;
}


// 1~25 까지 숫자를 넣어준다.
void setNumber(int *pArray) {
    for(int i=0 ; i< 25; i++) {
        pArray[i] = i+1;
    }
}

// 숫자를 섞는다.
void shuffleBingo(int *pArray) {
    int iTemp, idx1, idx2;
    for(int i=0; i<100; i++){
        idx1 = rand() % 25;
        idx2 = rand() % 25;
        
        iTemp = pArray[idx1];
        pArray[idx1] = pArray[idx2];
        pArray[idx2] = iTemp;
    }
}

// AI 모드를 선택
AI_MODE selectMode() {
    int iAIMode;
    while (true) {
        system("cls");
        cout << "1. Easy" << endl;
        cout << "2. HARD" << endl;
        cout << "AI 모드를 선택하세요: " << endl;
        cin >> iAIMode;
        
        if(cin.fail()) {
            cin.clear();
            cin.ignore(1024, '\n');
            continue;
        }
        
        if(iAIMode >= AM_EASY && iAIMode <= AM_HARD)
            break;
    }
    
    return (AI_MODE)iAIMode;
}

// bingo 판 출력
void printBingo(int *pArray, int bingoLine) {
    for(int i=0; i<5; i++) {
        for(int j=0; j<5; j++){
            // INT_MAX 일 경우 * 로 출력
            if(pArray[i*5 +j] == INT_MAX){
                cout << "*\t";
            } else {
                cout << pArray[i*5 + j] << "\t";
            }
        }
        cout << endl;
    }
    cout << "Bingo Line: " << bingoLine << endl << endl;;
}

// 빙고 갯수 확인
int countBingo(int *pArray) {
    int iBingo = 0;
    // 가로, 세로 줄 수를 구해준다.
    int iStar1 =0, iStar2 = 0;
    
    for(int i=0; i<5; i++) {
        iStar1 = iStar2 = 0; // 0으로 초기화
        for(int j=0; j<5; j++) {
            // 가로 별 개수를 구한다.
            if(pArray[i*5 + j] == INT_MAX) {
                iStar1++;
            }
            
            // 세로 별 갯수를 구한다.
            if(pArray[j*5 + i] == INT_MAX) {
                iStar2++;
            }
        }
        
        // j 문을 빠져나오면 별 갯수 체크 가능
        if(iStar1 == 5) iBingo++; // 가로줄
        if(iStar2 == 5) iBingo++; // 세로줄
    }
    
    // 대각선 체크
    iStar1 = 0;
    for(int i=0; i<25; i+=6) {
        if (pArray[i] == INT_MAX) {
            iStar1++;
        }
    }
    if(iStar1 == 5) iBingo++;
    
    iStar1 = 0;
    for(int i=4; i<=20; i+=4) {
        if(pArray[i] == INT_MAX) {
            iStar1++;
        }
    }
    if(iStar1 == 5) iBingo++;
    return iBingo;
}

bool changeNumber(int *pArray, int iInput) {
    for(int i=0; i<25; i++) {
        if(iInput == pArray[i]) {
            // 숫자를 * 로 변경하기 위해 INT_MAX 로 변경
            pArray[i] = INT_MAX;
            // 숫자가 있는 경우 false 로 변경 및 * 로 변경
            return false;
        }
    }
    
    return true;
}








