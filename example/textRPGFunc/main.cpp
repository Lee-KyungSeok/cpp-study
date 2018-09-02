//
//  main.cpp
//  textRPGFunc
//
//  Created by Cory on 2018. 8. 24..
//  Copyright © 2018년 Cory. All rights reserved.
//

#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

enum MAIN_MENU {
    MM_NONE,
    MM_MAP,
    MM_STORE,
    MM_INVENTORY,
    MM_EXIT
};

enum MAP_TYPE {
    MT_NONE,
    MT_EASY,
    MT_NORMAL,
    MT_HARD,
    MT_BACK
};

enum JOB {
    JOB_NONE,
    JOB_KNIGHT,
    JOB_ARCHER,
    JOB_WIZARD,
    JOB_END
};

enum Battle {
    BATTLE_NONE,
    BATTLE_ATTACK,
    BATTLE_BACK
};

enum ITEM_TYPE {
    ITEM_NONE,
    ITEM_WEAPON,
    ITEM_ARMOR,
    ITEM_BACK
};

enum STORE_MENU {
    SM_NONE,
    SM_WEAPON,
    SM_ARMOR,
    SM_BACK
};

enum EQUIP {
    EQ_WEAPON,
    EQ_ARMOR,
    EQ_MAX
};


#define NAME_SIZE 32
#define ITEM_DESC_LENGH 512
#define INVENTORY_MAX 20
#define STORE_WEAPON_MAX 3
#define STORE_ARMOR_MAX 3
#define LEVEL_MAX 10

struct _tagItem {
    char strName[NAME_SIZE];
    char strTypeName[NAME_SIZE];
    ITEM_TYPE eType;
    int iMin;
    int iMax;
    int iPrice;
    int iSell;
    char strDesc[ITEM_DESC_LENGH];
};

// inventory
struct _tagInventory {
    _tagItem tItem[INVENTORY_MAX];
    int iItemCount;
    int iGold;
    
};

// 유저 설정
struct _tagPlayer {
    char strName[NAME_SIZE];
    char strJobName[NAME_SIZE];
    JOB eJob;
    int iAttackMin;
    int iAttackMax;
    int iArmorMin;
    int iArmorMax;
    int iHP;
    int iHPMax;
    int iMP;
    int iMPMax;
    int iExp;
    int iLevel;
    _tagItem tEquip[EQ_MAX];
    bool bEquip[EQ_MAX];
    _tagInventory tInventory;
};
// 몬스터 설정
struct _tagMonster {
    char strName[NAME_SIZE];
    int iAttackMin;
    int iAttackMax;
    int iArmorMin;
    int iArmorMax;
    int iHP;
    int iHPMax;
    int iMP;
    int iMPMax;
    int iLevel;
    int iExp;
    int iGoldMin;
    int iGoldMax;
};

struct _tagLevelUpStatus {
    int iAttackMin;
    int iAttackMax;
    int iArmorMin;
    int iArmorMax;
    int iHPMin;
    int iHPMax;
    int iMPMin;
    int iMPMax;
};

// 레벨이 필요한 경험치 목록 생성
const int g_iLevelUpExp[LEVEL_MAX] = {4000, 10000, 20000, 35000, 50000, 70000, 100000, 150000, 200000, 400000};
// 직업의 갯수만큼 레벨업 상태 테이블을 만든다.
_tagLevelUpStatus g_tLvUpTable[JOB_END -1] = {};


// 숫자 입력을 받는 부분
int inputInt() {
    int iInput;
    cin >> iInput;
    
    // 형식에 어긋나는 메뉴 선택시 처리
    if(cin.fail()) {
        cin.clear(); // 값을 비우고
        cin.ignore(1024, '\n'); // \n 을 지움
        return INT_MAX; // 입력이 잘못되면 INT_MAX 를 리턴
    }
    return iInput;
}

// 메인 메뉴를 화면에 보여주고 입력받은 메뉴를 반환한다.
int outPutMenu() {
    system("cls");
    cout << "*************** 로비 ***************" << endl;
    cout << "1. 맵" << endl;
    cout << "2. 상점" << endl;
    cout << "3. 가방" << endl;
    cout << "4. 종료" << endl;
    cout << "메뉴를 선택하세요: ";
    int iMenu = inputInt();
    
    if(iMenu == INT_MAX || iMenu <= MM_NONE || iMenu > MM_EXIT) {
        return MM_NONE;
    }
    return iMenu;
}

int outPutMap() {
    system("cls");
    cout << "*************** 맵 ***************" << endl;
    cout << "1. 쉬움" << endl;
    cout << "2. 보통" << endl;
    cout << "3. 어려움" << endl;
    cout << "4. 뒤로가기" << endl;
    cout << "맵을 선택하세요: ";
    int iMap = inputInt();
    
    if(iMap == INT_MAX || iMap <= MT_NONE || iMap > MT_BACK) {
        return MT_NONE;
    }
    return iMap;
    
}

void ouputBattleTag(int iMenu) {
    switch (iMenu) {
        case MT_EASY:
            cout << "*************** 쉬움 ***************" << endl << endl;
            break;
        case MT_NORMAL:
            cout << "*************** 보통 ***************" << endl << endl;
            break;
        case MT_HARD:
            cout << "*************** 어려움 ***************" << endl << endl;
            break;
    }
}

// 플레이어 정보 출력
void outPutPlayer(_tagPlayer* pPlayer) {
    cout << "*************** Player ***************" << endl;
    cout << "이름: " << pPlayer -> strName << "\t직업: " << pPlayer -> strJobName << endl;
    cout << "레벨: " << pPlayer -> iLevel << "\t경험치: " << pPlayer -> iExp << " / " << g_iLevelUpExp[pPlayer -> iLevel - 1] << endl;
    if(pPlayer -> bEquip[EQ_WEAPON]) {
        cout << "공격력: " << pPlayer -> iAttackMin << " + " << pPlayer -> tEquip[EQ_WEAPON].iMin << " - " <<
        pPlayer -> iAttackMax << " + " << pPlayer -> tEquip[EQ_WEAPON].iMax << endl;
    } else {
        cout << "공격력: " << pPlayer -> iAttackMin << " - " << pPlayer -> iAttackMax << endl;
    }
    if(pPlayer -> bEquip[EQ_ARMOR]) {
        cout << "벙어력: " << pPlayer -> iArmorMin << " + " << pPlayer -> tEquip[EQ_ARMOR].iMin << " - " <<
        pPlayer -> iArmorMax << " + " << pPlayer -> tEquip[EQ_ARMOR].iMax << endl;
    } else {
        cout << "벙어력: " << pPlayer -> iArmorMin << " - " << pPlayer -> iArmorMax << endl;
    }
    cout << "체력: " << pPlayer -> iHP << " / " << pPlayer -> iHPMax <<
    "\t마나: " << pPlayer -> iMP << " / " << pPlayer -> iMPMax << endl;
    if(pPlayer -> bEquip[EQ_WEAPON]) {
        cout << "장착무기: " << pPlayer -> tEquip[EQ_WEAPON].strName << "\t";
    } else {
        cout << "장착무기: 없음" << "\t";
    }
    if(pPlayer -> bEquip[EQ_ARMOR]) {
        cout << "장착방어구: " << pPlayer -> tEquip[EQ_ARMOR].strName << endl;
    } else {
        cout << "장착방어구: 없음" << endl;
    }
    cout << "보유 골드: " << pPlayer -> tInventory.iGold << " Gold" << endl << endl;
}

// 몬스터 정보 출력
void outPutMonster(_tagMonster* pMonster) {
    cout << "*************** Monster ***************" << endl;
    cout << "이름: " << pMonster -> strName << "\t레벨: " << pMonster -> iLevel << endl;
    cout << "공격력: " << pMonster -> iAttackMin << " - " << pMonster -> iAttackMax <<
    "\t벙어력: " << pMonster -> iArmorMin << " - " << pMonster -> iArmorMax << endl;
    cout << "체력: " << pMonster -> iHP << " / " << pMonster -> iHPMax <<
    "\t마나: " << pMonster -> iMP << " / " << pMonster -> iMPMax << endl;
    cout << "획득경험치: " << pMonster -> iExp << "\t획득 골드: " << pMonster -> iGoldMin << " - " << pMonster -> iGoldMax << endl << endl;
}

int outPutBattleMenu() {
    cout << "1. 공격" << endl;
    cout << "2. 도망가기" << endl;
    cout << "매뉴룰 선택하세요: " << endl;
    int iMenu = inputInt();
    
    if(iMenu == INT_MAX || iMenu <= BATTLE_NONE || iMenu > BATTLE_BACK) {
        return BATTLE_NONE;
    }
    
    return iMenu;
}

void goBattle(_tagPlayer* pPlayer, _tagMonster* pMonster ) {
    // 공격력
    int iAttackMin = pPlayer -> iAttackMin;
    int iAttackMax = pPlayer -> iArmorMax;
    // 무기 장착시 min max 를 더해줌
    if(pPlayer -> bEquip[EQ_WEAPON]) {
        iAttackMin += pPlayer -> tEquip[EQ_WEAPON].iMin;
        iAttackMax += pPlayer -> tEquip[EQ_WEAPON].iMax;
    }
    
    int iAttack = rand() % (iAttackMax - iAttackMin + 1) + (iAttackMin); // 공격값
    int iArmor = rand() % (pMonster -> iArmorMax - pMonster -> iArmorMax + 1) + (pMonster -> iArmorMin); // 방어값
    int iDamage = iAttack - iArmor;
    iDamage = iDamage < 1 ? 1 : iDamage; // 삼항연산자
    
    // 몬스터 HP 를 감소시킨다.
    pMonster -> iHP -= iDamage;
    cout << pPlayer -> strName << "가 " << pMonster -> strName << "에게 " << iDamage << " 피해를 입혔습니다." << endl;
    // 몬스터가 죽었을 경우
    if(pMonster -> iHP <= 0) {
        cout << pMonster -> strName << " 몬스터가 사망하였습니다." << endl;
        pPlayer -> iExp += pMonster -> iExp;
        int iGold = (rand() % (pMonster -> iGoldMax - pMonster -> iGoldMin + 1) + pMonster -> iGoldMin);
        pPlayer -> tInventory.iGold += iGold;
        
        cout << pMonster -> iExp << " 경험치를 획득하였습니다." << endl;
        cout << iGold << " Gold를 획득하였습니다." << endl;
        
        // 죽었을 경우 새로운 몬스터를 생성!
        pMonster -> iHP = pMonster -> iHPMax;
        pMonster -> iMP = pMonster -> iMPMax;
        
        // 레벨업 체크
        if(pPlayer -> iExp >= g_iLevelUpExp[pPlayer -> iLevel - 1]) {
            // 플레이어 경험치를 레벨업에 필요한 경험치 만큼 차감
            pPlayer -> iExp -= g_iLevelUpExp[pPlayer -> iLevel - 1];
            // 레벨업
            pPlayer -> iLevel++;
            
            cout << "레벨 업" << endl;
            
            // 능력치 상승
            int iJobIndex = pPlayer -> eJob - 1;
            int iHPUp = rand() % (g_tLvUpTable[iJobIndex].iHPMax - g_tLvUpTable[iJobIndex].iHPMin +1 ) + g_tLvUpTable[iJobIndex].iHPMin;
            int iMPUp = rand() % (g_tLvUpTable[iJobIndex].iMPMax - g_tLvUpTable[iJobIndex].iMPMin +1 ) + g_tLvUpTable[iJobIndex].iMPMin;
            
            pPlayer -> iAttackMin += g_tLvUpTable[iJobIndex].iAttackMin;
            pPlayer -> iAttackMax += g_tLvUpTable[iJobIndex].iAttackMax;
            pPlayer -> iArmorMin += g_tLvUpTable[iJobIndex].iArmorMin;
            pPlayer -> iArmorMax += g_tLvUpTable[iJobIndex].iArmorMax;
            pPlayer -> iHPMax += iHPUp;
            pPlayer -> iMPMax += iMPUp;
            
            // 체력과 마나 회복
            pPlayer -> iHP = pPlayer -> iHPMax;
            pPlayer -> iMP = pPlayer -> iMPMax;
        }
        return ;
    }
    
    // 방어력(방어구 확인)
    int iArmorMin = pPlayer -> iAttackMin;
    int iArmorMax = pPlayer -> iArmorMax;
    // 장착구 확인
    if(pPlayer -> bEquip[EQ_ARMOR]) {
        iArmorMin += pPlayer -> tEquip[EQ_ARMOR].iMin;
        iArmorMax += pPlayer -> tEquip[EQ_ARMOR].iMax;
    }
    
    // 몬스터가 살아 있다면 플레이어를 공격한다.
    iAttack = rand() % (pMonster -> iAttackMax - pMonster -> iAttackMin + 1) + (pMonster -> iAttackMin); // 공격값
    iArmor = rand() % (pPlayer -> iArmorMax - pPlayer -> iArmorMax + 1) + (pPlayer -> iArmorMin); // 방어값
    iDamage = iAttack - iArmor;
    iDamage = iDamage < 1 ? 1 : iDamage; // 삼항연산자
    
    // 플레이어의 HP 를 감소시킨다.
    pPlayer -> iHP -= iDamage;
    cout << pMonster -> strName << "가 " << pPlayer -> strName << "에게 " << iDamage << " 피해를 입혔습니다." << endl;
    // 몬스터가 죽었을 경우
    if( pPlayer -> iHP <= 0) {
        cout << pPlayer -> strName << " 플레이어가 사망하였습니다." << endl;
        
        // 죽으면 10프로씩 감소시킴
        int iExp = pPlayer -> iExp * 0.1f;
        int iGold = pPlayer -> tInventory.iGold * 0.1f;
        
        pPlayer -> iExp -= iExp;
        pPlayer -> tInventory.iGold -= iGold;
        
        cout << iExp << " 경험치를 잃었습니다." << endl;
        cout << iGold << " Gold를 잃었습니다." << endl;
        
        // 플레이어의 HP 와 MP 를 회복
        pPlayer -> iHP = pPlayer -> iHPMax;
        pPlayer -> iMP = pPlayer -> iMPMax;
        
        return;
    }
}

void runBattle(_tagPlayer* pPlayer, _tagMonster* pMonsterArr, int iMenu) {
    bool bLoop = true;
    // 몬스터 생성
    _tagMonster tMonster = pMonsterArr[iMenu -1];
    
    while(bLoop) {
        system("cls");
        ouputBattleTag(iMenu);
        outPutPlayer(pPlayer);
        outPutMonster(&tMonster);
        
        switch (outPutBattleMenu()) {
            case BATTLE_ATTACK:
                goBattle(pPlayer, &tMonster);
                system("pause");
                break;
            case BATTLE_BACK:
                bLoop = false;
                break;
        }
    }
}

// 맵 관련 동작 처리
void runMap(_tagPlayer* pPlayer, _tagMonster* pMonsterArr) {
    bool bLoop = true;
    
    while (bLoop) {
        
        int iMenu = outPutMap();
        
        if(MT_BACK == iMenu) {
            return;
        }
        
        // 전투 시작
        runBattle(pPlayer, pMonsterArr, iMenu);
    }
}

int selectJob() {
    int iJob = JOB_NONE;
    while(iJob == JOB_NONE) {
        system("cls");
        cout << "1. 기사" << endl;
        cout << "2. 궁수" << endl;
        cout << "3. 마법사" << endl;
        cout << "직업을 선택하세요: ";
        iJob = inputInt();
        
        // 잘못 입력했을 경우 반복시키기 위함
        if(iJob == INT_MAX || iJob <= JOB_NONE || iJob >= JOB_END) {
            iJob = JOB_NONE;
        }
    }
    return iJob;
}

void setPlayer(_tagPlayer* pPlayer) { // 포인터 타입임에 주의
    // 이름
    cout << "이름: ";
    cin.getline(pPlayer -> strName, NAME_SIZE - 1); // 한줄로 입력, & NAME_SIZE 보다 하나 작게 하여 null 을 넣을 수 있는 공간을 만든다. (문자열은 마지막에 null 을 넣어야 한다.)
    // 초기값 세팅
    pPlayer -> eJob = (JOB)selectJob(); // 직업 선택
    pPlayer -> iLevel = 1;
    pPlayer -> iExp = 0;
    pPlayer -> tInventory.iGold = 10000;
    
    // 직업에 따라 설정값 세팅
    switch (pPlayer -> eJob) {
        case JOB_KNIGHT:
            strcpy(pPlayer -> strJobName, "기사");
            pPlayer -> iAttackMin = 5;
            pPlayer -> iAttackMax = 10;
            pPlayer -> iArmorMin = 15;
            pPlayer -> iArmorMax = 20;
            pPlayer -> iHP = 500;
            pPlayer -> iHPMax = 500;
            pPlayer -> iMP = 100;
            pPlayer -> iMPMax = 100;
            break;
        case JOB_ARCHER:
            strcpy(pPlayer -> strJobName, "궁수");
            pPlayer -> iAttackMin = 10;
            pPlayer -> iAttackMax = 15;
            pPlayer -> iArmorMin = 10;
            pPlayer -> iArmorMax = 15;
            pPlayer -> iHP = 400;
            pPlayer -> iHPMax = 400;
            pPlayer -> iMP = 200;
            pPlayer -> iMPMax = 200;
            break;
        case JOB_WIZARD:
            strcpy(pPlayer -> strJobName, "마법사");
            pPlayer -> iAttackMin = 15;
            pPlayer -> iAttackMax = 20;
            pPlayer -> iArmorMin = 5;
            pPlayer -> iArmorMax = 10;
            pPlayer -> iHP = 300;
            pPlayer -> iHPMax = 300;
            pPlayer -> iMP = 300;
            pPlayer -> iMPMax = 300;
            break;
        default:
            break;
    }
}

// 몬스터를 생성
_tagMonster createMonster(char* pName, int iAttackMin, int iAttackMax, int iArmorMin, int iArmorMax,
                          int iHP, int iMP, int iLevel, int iExp, int iGoldMin, int iGoldMax) {
    _tagMonster tMonster = {};
    
    strcpy(tMonster.strName, pName);
    tMonster.iAttackMin = iAttackMin;
    tMonster.iAttackMin = iAttackMin;
    tMonster.iArmorMin = iArmorMin;
    tMonster.iArmorMax = iArmorMax;
    tMonster.iHP = iHP;
    tMonster.iHPMax = iHP;
    tMonster.iMP = iMP;
    tMonster.iMPMax = iMP;
    tMonster.iLevel = iLevel;
    tMonster.iExp = iExp;
    tMonster.iGoldMin = iGoldMin;
    tMonster.iGoldMax = iGoldMax;
    
    return tMonster;
}

void setMonster(_tagMonster* pMonsterArr) {
    pMonsterArr[0] = createMonster((char*)"고블린", 20, 30, 2, 5, 100, 10, 1, 1000, 500, 1500);
    pMonsterArr[1] = createMonster((char*)"트롤", 80, 130, 60, 90, 2000, 100, 5, 7000, 6000, 8000);
    pMonsterArr[2] = createMonster((char*)"드래곤", 250, 500, 200, 400, 30000, 20000, 10, 30000, 20000, 50000);
}

_tagLevelUpStatus createLvUpStatus(int iAttackMin, int iAttackMax, int iArmorMin, int iArmorMax,
                                   int iHPMin, int iHPMax, int iMPMin,  int iMPMax) {
    _tagLevelUpStatus tStatus = {};
    tStatus.iAttackMin = iAttackMin;
    tStatus.iAttackMax = iAttackMax;
    tStatus.iArmorMin = iArmorMin;
    tStatus.iArmorMax = iArmorMax;
    tStatus.iHPMin = iHPMin;
    tStatus.iHPMax = iHPMax;
    tStatus.iMPMin = iMPMin;
    tStatus.iMPMax = iMPMax;
    
    return tStatus;
}

_tagItem createItem(char* pName, ITEM_TYPE eType, int iMin,
                    int iMax, int iPrice,  int iSell,  char* pDesc) {
    _tagItem tItem = {};
    
    strcpy(tItem.strName, pName);
    tItem.eType = eType;
    tItem.iMin = iMin;
    tItem.iMax = iMax;
    tItem.iPrice = iPrice;
    tItem.iSell = iSell;
    strcpy(tItem.strDesc, pDesc);
    
    switch (eType) {
        case ITEM_WEAPON:
            strcpy(tItem.strTypeName, "무기");
            break;
        case ITEM_ARMOR:
            strcpy(tItem.strTypeName, "방어구");
            break;
    }
    
    return tItem;
}

int outPutStoreMenu() {
    system("cls");
    cout << "*************** 상점 ***************" << endl;
    cout << "1. 무기상점" << endl;
    cout << "2. 방어구상점" << endl;
    cout << "3. 뒤로가기" << endl;
    cout << "상점을 선택하세요: ";
    int iMenu = inputInt();
    
    // 잘못 입력했을 경우 반복시키기 위함
    if(iMenu == INT_MAX || iMenu <= SM_NONE || iMenu > SM_BACK) {
        iMenu = SM_NONE;
    }
    
    return iMenu;
}

int outPutStoreItemList(_tagInventory* pInventory, _tagItem* pStore, int iItemCount) {
    // 판매 목록을 보여준다.
    for(int i=0; i<iItemCount; i++) {
        cout << i +1 << ". 이름: " << pStore[i].strName << "\t종류: " <<pStore[i].strTypeName << endl;
        cout << "공격력: " << pStore[i].iMin << " - " << pStore[i].iMax << endl;
        cout << "판매가격: " << pStore[i].iPrice << "\t구매가격: " <<pStore[i].iSell << endl;
        cout << "설명: " << pStore[i].strDesc << endl << endl;
    }
    
    cout << iItemCount + 1 << ". 뒤로가기" << endl;
    cout << "보유금액: " << pInventory -> iGold << " Gold" << endl;
    cout << "남은공간: " << INVENTORY_MAX - pInventory -> iItemCount << endl;
    cout << "구입할 아이템을 선택하세요: ";
    int iMenu = inputInt();
    
    if(iMenu <1 || iMenu > iItemCount + 1) {
        return INT_MAX;
    }
    
    return iMenu;
}

void buyItem(_tagInventory* pInventory, _tagItem* pStore, int iItemCount, int iStoreType) {
    
    while (true) {
        system("cls");
        switch (iStoreType) {
            case SM_WEAPON:
                cout << "*************** 무기 상점 ***************" << endl;
                break;
            case SM_ARMOR:
                cout << "*************** 방어구 상점 ***************" << endl;
                break;
        }
        
        int iInput = outPutStoreItemList(pInventory, pStore, iItemCount);
        
        if(iInput == INT_MAX) {
            cout << "잘못 입력하였습니다." << endl;
            system("pause");
            continue;
        } else if(iInput == iItemCount + 1) {
            break;
        }
        
        // 상점 판매목록 배열의 인덱스를 구해준다.
        int iStoreIndex = iInput - 1;
        
        if(pInventory -> iItemCount == INVENTORY_MAX) {
            // 인벤토리가 꽉 찼는지 검사
            cout << "가방이 꽉 찼습니다." << endl;
            system("pause");
            continue;
        } else if(pInventory -> iGold < pStore[iStoreIndex].iPrice) {
            // 돈이 부족한 경우
            cout << "보유 금액이 부족합니다." << endl;
            system("pause");
            continue;
        }
        
        // 처음에 iItemCount 는 한개도 없기 때문에 0으로 초기화!
        pInventory -> tItem[pInventory -> iItemCount] = pStore[iStoreIndex];
        pInventory -> iItemCount++;
        
        // 골드 차감
        pInventory -> iGold -= pStore[iStoreIndex].iPrice;
        
        cout << pStore[iStoreIndex].strName << " 아이템을 구매하였습니다." << endl;
        system("pause");
    }
}

void runStore(_tagInventory* pInventory, _tagItem* pWeapon, _tagItem* pArmor) {
    bool bLoop = true;
    
    while (bLoop) {
        switch (outPutStoreMenu()) {
            case SM_WEAPON:
                buyItem(pInventory, pWeapon, STORE_WEAPON_MAX, SM_WEAPON);
                break;
            case SM_ARMOR:
                buyItem(pInventory, pArmor, STORE_ARMOR_MAX, SM_ARMOR);
                break;
            case SM_BACK:
                bLoop = false;
                break;
        }
    }
}

int outPutInventory(_tagPlayer* pPlayer) {
    system("cls");
    cout << "*************** 가방 ***************" << endl;
    outPutPlayer(pPlayer);
    
    for(int i=0; i<pPlayer -> tInventory.iItemCount; i++) {
        cout << i +1 << ". 이름: " << pPlayer -> tInventory.tItem[i].strName << "\t종류: " << pPlayer -> tInventory.tItem[i].strTypeName << endl;
        cout << "공격력: " << pPlayer -> tInventory.tItem[i].iMin << " - " << pPlayer -> tInventory.tItem[i].iMax << endl;
        cout << "판매가격: " << pPlayer -> tInventory.tItem[i].iPrice << "\t구매가격: " << pPlayer -> tInventory.tItem[i].iSell << endl;
        cout << "설명: " << pPlayer -> tInventory.tItem[i].strDesc << endl << endl;
    }
    
    cout << pPlayer -> tInventory.iItemCount + 1 << ". 뒤로가기" << endl;
    cout << "장착할 아이템을 선택하세요: ";
    int iMenu = inputInt();
    
    if(iMenu < 1 || iMenu > pPlayer -> tInventory.iItemCount + 1) {
        return INT_MAX;
    }
    return iMenu;
}

EQUIP computeEquipType(ITEM_TYPE eType) {
    // 제대로 선택했을 경우 해당 아이템의 종류에 따라 장차 부위를 결정
    EQUIP eq;
    switch (eType) {
        case ITEM_WEAPON:
            eq = EQ_WEAPON;
            break;
        case ITEM_ARMOR:
            eq = EQ_ARMOR;
            break;
    }
    return eq;
}

void runInventory(_tagPlayer* pPlayer) {
    while (true) {
        int iInput = outPutInventory(pPlayer);
        
        if(iInput == INT_MAX) {
            continue;
        } else if(iInput == pPlayer -> tInventory.iItemCount + 1) {
            break;
        }
        
        // 아이템 인텍스를 구한다.
        int idx = iInput - 1;
        EQUIP eq = computeEquipType(pPlayer -> tInventory.tItem[idx].eType);
        
        // 아이템이 장착되어 있을 경우 장착되어 있는 아이템과 장착할 아이템을 교체
        // 그렇지 않을 경우 장착하고 한칸 비우기 (안쪽으로 push)
        if(pPlayer -> bEquip[eq] == true) {
            _tagItem tSwap = pPlayer -> tEquip[eq];
            pPlayer -> tEquip[eq] = pPlayer -> tInventory.tItem[idx];
            pPlayer -> tInventory.tItem[idx] = tSwap;
        } else {
            pPlayer -> tEquip[eq] = pPlayer -> tInventory.tItem[idx];
            for(int i=0; i< pPlayer -> tInventory.iItemCount - 1; i++) {
                pPlayer -> tInventory.tItem[i] = pPlayer -> tInventory.tItem[i+1];
            }
            pPlayer -> tInventory.iItemCount--;
            pPlayer -> bEquip[eq] = true; // 장착
        }
        cout << pPlayer -> tEquip[eq].strName << " 아이템을 장착하였습니다." << endl;
        system("pause");
    }
}

int main(int argc, const char * argv[]) {
    srand((unsigned int)time(0));
    bool bLoop = true; // 반복문 종료 조건 설정
    
    // 게임 시작 때 플레이어 정보 설정
    _tagPlayer tPlayer = {};
    // 플레이어 정보를 정의
    setPlayer(&tPlayer);
    
    // 몬스터 생성
    _tagMonster tMonsterArr[MT_BACK -1] = {};
    setMonster(tMonsterArr);
    
    // 직업 레벨업 테이블 생성
    g_tLvUpTable[JOB_KNIGHT -1] = createLvUpStatus(4, 10, 8, 16, 50, 100, 10, 20);
    g_tLvUpTable[JOB_ARCHER -1] = createLvUpStatus(10, 15, 5, 10, 30, 60, 30, 50);
    g_tLvUpTable[JOB_WIZARD -1] = createLvUpStatus(15, 20, 3, 7, 20, 40, 50, 100);
    
    // 상점에서 판매할 아이템 목록 생성
    _tagItem tStoreWeapon[STORE_WEAPON_MAX] = {};
    _tagItem tStoreArmor[STORE_ARMOR_MAX] = {};
    
    tStoreWeapon[0] = createItem((char*)"목검", (ITEM_TYPE)ITEM_WEAPON, 5, 10, 1000, 500, (char*)"나무로 만든 검");
    tStoreWeapon[1] = createItem((char*)"장궁", (ITEM_TYPE)ITEM_WEAPON, 20, 40, 7000, 3500, (char*)"짱짱한 활");
    tStoreWeapon[2] = createItem((char*)"지팡이", (ITEM_TYPE)ITEM_WEAPON, 90, 150, 30000, 15000, (char*)"나무로 만든 지팡이");
    
    tStoreArmor[0] = createItem((char*)"천갑옷", (ITEM_TYPE)ITEM_ARMOR, 2, 5, 1000, 500, (char*)"천으로 만든 갑옷");
    tStoreArmor[1] = createItem((char*)"가죽갑옷", (ITEM_TYPE)ITEM_ARMOR, 10, 20, 7000, 3500, (char*)"동물 가죽으로 만든 질긴 갑옷");
    tStoreArmor[2] = createItem((char*)"플레이트 아머", (ITEM_TYPE)ITEM_ARMOR, 70, 90, 30000, 15000, (char*)"강철로 만든 판금 갑옷");
    
    while(bLoop) {
        switch (outPutMenu()) {
            case MM_MAP:
                runMap(&tPlayer, tMonsterArr); // Map 관련 처리
                break;
            case MM_STORE:
                runStore(&tPlayer.tInventory, tStoreWeapon, tStoreArmor);
                break;
            case MM_INVENTORY:
                runInventory(&tPlayer);
                break;
            case MM_EXIT:
                bLoop = false;
                break;
        }
    }
    
    return 0;
}












