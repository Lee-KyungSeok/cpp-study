//
//  main.cpp
//  maze
//
//  Created by Cory on 2018. 8. 27..
//  Copyright © 2018년 Cory. All rights reserved.
//

/* 규칙
 0: 벽
 1: 길
 2: 시작점
 3: 도착점
 4: 폭탄
 5: 파워 아이템
 6. 벽밀기 아이템
 7. 투명아이템
 8. 웜홀
 */
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <time.h>

using namespace std;

struct _tagPoint {
    int x;
    int y;
};

// 타입을 재정의
typedef _tagPoint POINT;
typedef _tagPoint* PPOINT;

typedef struct _tagPlayer {
    _tagPoint tPos;
    bool bWallPush;
    bool bPushOnOff;
    bool bTransparency;
    int iBombPower;
}PLAYER, *PPLAYER;

int iGetch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}

void setMaze(char Maze[21][21], PPLAYER pPlayer, PPOINT pStartPos, PPOINT pEndPos) {
    
    pStartPos->x = 0;
    pStartPos->y = 0;
    
    pEndPos->x = 20;
    pEndPos->y = 16;
    
    pPlayer->tPos = *pStartPos;
    
    // 하나씩 넣기 힘드므로 주소에 복사하여 넣어준다.
    strcpy(Maze[0],  "211000000000000000010");
    strcpy(Maze[1],  "001111111111000000010");
    strcpy(Maze[2],  "011000100001111111110");
    strcpy(Maze[3],  "011000100000000001010");
    strcpy(Maze[4],  "010000111100011111110");
    strcpy(Maze[5],  "010000000011110000000");
    strcpy(Maze[6],  "011000000010000000000");
    strcpy(Maze[7],  "001000000011111110000");
    strcpy(Maze[8],  "001000000000000011110");
    strcpy(Maze[9],  "011111111100000110000");
    strcpy(Maze[10], "001000000011111100000");
    strcpy(Maze[11], "001001111110000111110");
    strcpy(Maze[12], "011011000000111100000");
    strcpy(Maze[13], "010000011111100000000");
    strcpy(Maze[14], "010111100000111100000");
    strcpy(Maze[15], "011100111000000100000");
    strcpy(Maze[16], "010000001111000011113");
    strcpy(Maze[17], "010001111000001110000");
    strcpy(Maze[18], "011100001111111011110");
    strcpy(Maze[19], "000100001000001000100");
    strcpy(Maze[20], "000000000000000000000");
}

void output(char Maze[21][21], PPLAYER pPlayer) {
    for(int i=0; i<21; i++) {
        for(int j=0; j<21; j++) {
            if(j== pPlayer->tPos.x && i==pPlayer->tPos.y) {
                cout << "✩";
            } else if(Maze[i][j] == '0') {
                cout << "◼︎" ;
            } else if (Maze[i][j] == '1') {
                cout << "▽";
            } else if(Maze[i][j] == '2') {
                cout << "★";
            } else if (Maze[i][j] == '3') {
                cout << " ";
            } else if(Maze[i][j] == '4') {
                cout << "❂";
            } else if(Maze[i][j] == '5') {
                cout << "✡︎";
            } else if(Maze[i][j] == '6') {
                cout << "☞";
            } else if(Maze[i][j] == '7') {
                cout << "❀";
            }
        }
        cout << endl;
    }
    
    cout << "폭탄파워: " << pPlayer->iBombPower << endl;
    
    cout << "벽 통과: ";
    if(pPlayer->bTransparency) cout << "ON" << "\t";
    else cout << "OFF" << "\t";
    
    cout << "벽 밀기: ";
    if(pPlayer->bWallPush) cout << "가능";
    else cout << "불가능";
    if(pPlayer->bPushOnOff) cout << "(ON)" << endl;
    else cout << "(OFF)" << endl;
}

bool addItem(char cItemType, PPLAYER pPlayer) {
    if(cItemType == '5') {
        if(pPlayer->iBombPower < 5) { // 폭탄의 최대치를 5로 설정
            (pPlayer->iBombPower)++;
        }
        return true;
    } else if(cItemType == '6') {
        pPlayer->bWallPush = true;
        pPlayer->bPushOnOff = true;
        return true;
    } else if(cItemType == '7') {
        pPlayer->bTransparency = true;
        return true;
    }
    
    return false;
}

void moveUp(char Maze[21][21], PPLAYER pPlayer) {
    if(pPlayer->tPos.y-1 >=0 ) {
        
        // 벽인지 체크
        if(Maze[pPlayer->tPos.y-1][pPlayer->tPos.x] != '0' &&
           Maze[pPlayer->tPos.y-1][pPlayer->tPos.x] != '4') {
            pPlayer->tPos.y -= 1;
        }
        // 벽 밀기가 가능하면서 on 인 경우 & 바로 윗칸이 벽인 경우
        else if(pPlayer->bWallPush && pPlayer->bPushOnOff && Maze[pPlayer->tPos.y-1][pPlayer->tPos.x] == '0') {
            // 옮겨지는 위치가 맵을 벗어나지 않도록
            if(pPlayer->tPos.y-2 >= 0) {
                // 벽의 윗부분이 이동 가능 경로인 경우
                if(Maze[pPlayer->tPos.y-2][pPlayer->tPos.x] == '1') {
                    Maze[pPlayer->tPos.y-2][pPlayer->tPos.x] = '0';
                    Maze[pPlayer->tPos.y-1][pPlayer->tPos.x] = '1';
                    pPlayer->tPos.y -= 1;
                } else if(pPlayer->bTransparency) {
                    pPlayer->tPos.y -= 1;
                }
            } else if(pPlayer->bTransparency) {
                pPlayer->tPos.y -= 1;
            }
        }
        // 투명아이템이면 그냥 지나칠 수 있음
        else if(pPlayer->bTransparency) {
            pPlayer->tPos.y -= 1;
        }
        
        // 아이템이 추가되면 1로 변경
        if(addItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer)) {
            Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
        }
    }
}

void moveDown(char Maze[21][21], PPLAYER pPlayer) {
    if(pPlayer->tPos.y+1 <= 20 ) {
        // 벽인지 체크
        if(Maze[pPlayer->tPos.y+1][pPlayer->tPos.x] != '0' &&
           Maze[pPlayer->tPos.y+1][pPlayer->tPos.x] != '4') {
            pPlayer->tPos.y += 1;
        }
        
        // 벽 밀기가 on 인 경우
        else if(pPlayer->bWallPush && pPlayer->bPushOnOff && Maze[pPlayer->tPos.y+1][pPlayer->tPos.x] == '0') {
            if(pPlayer->tPos.y+2 <= 20) {
                if(Maze[pPlayer->tPos.y+2][pPlayer->tPos.x] == '1') {
                    Maze[pPlayer->tPos.y+2][pPlayer->tPos.x] = '0';
                    Maze[pPlayer->tPos.y+1][pPlayer->tPos.x] = '1';
                    pPlayer->tPos.y += 1;
                } else if(pPlayer->bTransparency) {
                    pPlayer->tPos.y += 1;
                }
            } else if(pPlayer->bTransparency) {
                pPlayer->tPos.y += 1;
            }
        } 
        
        // 투명아이템이면 그냥 지나칠 수 있음
        else if(pPlayer->bTransparency) {
            pPlayer->tPos.y += 1;
        }
        
        // 아이템이 추가되면 1로 변경
        if(addItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer)) {
            Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
        }
    }
}

void moveLeft(char Maze[21][21], PPLAYER pPlayer) {
    if(pPlayer->tPos.x-1 >=0 ) {
        // 벽인지 체크
        if(Maze[pPlayer->tPos.y][pPlayer->tPos.x-1] != '0' &&
           Maze[pPlayer->tPos.y][pPlayer->tPos.x-1] != '4') {
            pPlayer->tPos.x -= 1;
        }
        
        // 벽 밀기가 on 인 경우
        else if(pPlayer->bWallPush && pPlayer->bPushOnOff && Maze[pPlayer->tPos.y][pPlayer->tPos.x-1] == '0') {
            if(pPlayer->tPos.x-2 >= 0) {
                if(Maze[pPlayer->tPos.y][pPlayer->tPos.x-2] == '1') {
                    Maze[pPlayer->tPos.y][pPlayer->tPos.x-2] = '0';
                    Maze[pPlayer->tPos.y][pPlayer->tPos.x-1] = '1';
                    pPlayer->tPos.x -= 1;
                } else if(pPlayer->bTransparency) {
                    pPlayer->tPos.x -= 1;
                }
            } else if(pPlayer->bTransparency) {
                pPlayer->tPos.x -= 1;
            }
        }
        
        // 투명아이템이면 그냥 지나칠 수 있음
        else if(pPlayer->bTransparency) {
            pPlayer->tPos.x -= 1;
        }
        
        // 아이템이 추가되면 1로 변경
        if(addItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer)) {
            Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
        }
    }
}

void moveRight(char Maze[21][21], PPLAYER pPlayer) {
    if(pPlayer->tPos.x+1 <= 20 ) {
        // 벽인지 체크
        if(Maze[pPlayer->tPos.y][pPlayer->tPos.x+1] != '0' &&
           Maze[pPlayer->tPos.y][pPlayer->tPos.x+1] != '4') {
            pPlayer->tPos.x += 1;
        }
        
        // 벽 밀기가 on 인 경우
        else if(pPlayer->bWallPush && pPlayer->bPushOnOff && Maze[pPlayer->tPos.y][pPlayer->tPos.x+1] == '0') {
            if(pPlayer->tPos.x+2 <=20) {
                if(Maze[pPlayer->tPos.y][pPlayer->tPos.x+2] == '1') {
                    Maze[pPlayer->tPos.y][pPlayer->tPos.x+2] = '0';
                    Maze[pPlayer->tPos.y][pPlayer->tPos.x+1] = '1';
                    pPlayer->tPos.x += 1;
                } else if(pPlayer->bTransparency) {
                    pPlayer->tPos.x += 1;
                }
            } else if(pPlayer->bTransparency) {
                pPlayer->tPos.x += 1;
            }
        }
        
        // 투명아이템이면 그냥 지나칠 수 있음
        else if(pPlayer->bTransparency) {
            pPlayer->tPos.x += 1;
        }
        
        // 아이템이 추가되면 1로 변경
        if(addItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer)) {
            Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
        }
    }
}

void movePlayer(char Maze[21][21], PPLAYER pPlayer, char cInput) {
    
    switch (cInput) {
        case 'w':
        case 'W':
            moveUp(Maze, pPlayer);
            break;
        case 's':
        case 'S':
            moveDown(Maze, pPlayer);
            break;
        case 'a':
        case 'A':
            moveLeft(Maze, pPlayer);
            break;
        case 'd':
        case 'D':
            moveRight(Maze, pPlayer);
            break;
    }
}

void createBomb(char Maze[21][21], const PPLAYER pPlayer, // 포인터 변수를 const 로 생성시 가리키는 대상 값 변경 불가능
                PPOINT pBombArr, int* pBombCount) {
    if(*pBombCount == 5) return;
    
    // player 위치가 벽인 경우 폭탄 설치 불가
    else if(Maze[pPlayer->tPos.y][pPlayer->tPos.x] == '0') {
        return;
    }
    
    // 중복 제거
    for(int i=0; i<*pBombCount; i++) {
        if(pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y) {
            return;
        }
    }
    
    pBombArr[*pBombCount] = pPlayer->tPos;
    (*pBombCount)++;
    
    Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '4';
}

void dropItem(char* position) {
    // 아이템 드랍 확률을 구한다.
    int iPercent = rand() % 100 ;
    if(iPercent < 50) {
        *position = '5';
    } else if(iPercent < 90) {
        *position = '6';
    } else {
        *position = '7';
    }
}

void fireBomb(char Maze[21][21], PPLAYER pPlayer, PPOINT pBombArr, int* pBombCount) {
    for(int i=0; i<*pBombCount; i++) {
        
        // 폭탄 장소를 1로 변경
        Maze[pBombArr[i].y][pBombArr[i].x] = '1';
        
        for(int j=1 ; j<=pPlayer->iBombPower; j++) {
            // 폭탄 주위를 1로 변경
            // 플레이어가 맞으면 시작점으로 변경
            if(pBombArr[i].y-j >= 0) {
                if(Maze[pBombArr[i].y-j][pBombArr[i].x] == '0') {
                    if(rand() % 100 < 20) {
                        dropItem(&Maze[pBombArr[i].y-j][pBombArr[i].x]);\
                    } else {
                        Maze[pBombArr[i].y-j][pBombArr[i].x] = '1';
                    }
                }
                
                if((*pPlayer).tPos.x == pBombArr[i].x && (*pPlayer).tPos.y == pBombArr[i].y-j) {
                    pPlayer->tPos.x = 0;
                    pPlayer->tPos.y = 0;
                }
            }
            
            if(pBombArr[i].y+j <= 20) {
                if(Maze[pBombArr[i].y+j][pBombArr[i].x] == '0') {
                    if(rand()%100 < 20) {
                        dropItem(&Maze[pBombArr[i].y+j][pBombArr[i].x]);
                    } else {
                        Maze[pBombArr[i].y+j][pBombArr[i].x] = '1';
                    }
                }
                
                if((*pPlayer).tPos.x == pBombArr[i].x && (*pPlayer).tPos.y == pBombArr[i].y+j) {
                    pPlayer->tPos.x = 0;
                    pPlayer->tPos.y = 0;
                }
            }
            
            if(pBombArr[i].x-j >= 0) {
                if(Maze[pBombArr[i].y][pBombArr[i].x-j] == '0') {
                    if(rand()%100 < 20) {
                        dropItem(&Maze[pBombArr[i].y][pBombArr[i].x-j]);
                    } else {
                        Maze[pBombArr[i].y][pBombArr[i].x-j] = '1';
                    }
                }
                
                if((*pPlayer).tPos.x == pBombArr[i].x-j && (*pPlayer).tPos.y == pBombArr[i].y) {
                    pPlayer->tPos.x = 0;
                    pPlayer->tPos.y = 0;
                }
            }
            
            if(pBombArr[i].x+j <= 20) {
                if(Maze[pBombArr[i].y][pBombArr[i].x+j] == '0') {
                    if(rand()%100 < 20) {
                        dropItem(&Maze[pBombArr[i].y][pBombArr[i].x+j]);
                    } else {
                        Maze[pBombArr[i].y][pBombArr[i].x+j] = '1';
                    }
                }
                
                if((*pPlayer).tPos.x == pBombArr[i].x+j && (*pPlayer).tPos.y == pBombArr[i].y) {
                    pPlayer->tPos.x = 0;
                    pPlayer->tPos.y = 0;
                }
            }
        }
    }
    
    *pBombCount = 0;
}

int main(int argc, const char * argv[]) {
    
    srand((unsigned int)time(0));
    
    // 20 X 20 미로를 만들어 준다.
    char strMaze[21][21] = {};
    
    PLAYER tPlayer = {};
    POINT tStartPos;
    POINT tEndPos;
    
    // 폭탄 설정
    tPlayer.iBombPower = 1;
    int tBombCount = 0;
    POINT tBombPos[5];
    
    // 미로를 설정한다.
    setMaze(strMaze, &tPlayer, &tStartPos, &tEndPos);
    
    while (true) {
        
        if(tPlayer.tPos.x == tEndPos.x && tPlayer.tPos.y == tEndPos.y) {
            cout << endl;
            cout << "도착했습니다." << endl;
            break;
        }
        
        system("cls");
        // 미로를 출력한다.
        output(strMaze, &tPlayer);
        cout << "t: 폭탄설치, u: 폭탄 터뜨리기, i: 벽 밀기 ON/OFF" << endl;
        cout << "w: 위, s: 아래, a: 왼쪽, d: 오른쪽, q: 종료 ";
        char cInput = iGetch();
        cout << endl;
        
        if(cInput == 'q' || cInput == 'Q') {
            break;
        } else if(cInput == 't' || cInput == 'T') {
            createBomb(strMaze, &tPlayer, tBombPos, &tBombCount);
        } else if(cInput == 'u' || cInput == 'U') {
            fireBomb(strMaze, &tPlayer, tBombPos, &tBombCount);
        } else if(cInput == 'i' || cInput == 'I') {
            if(tPlayer.bWallPush) {
                tPlayer.bPushOnOff = !tPlayer.bPushOnOff;
            }
        }
        
        movePlayer(strMaze, &tPlayer, cInput);
    }
    
    return 0;
}










