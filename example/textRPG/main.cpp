//
//  main.cpp
//  textRPG
//
//  Created by Cory on 2018. 8. 23..
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

int main(int argc, const char * argv[]) {
    srand((unsigned int)time(0));
    
    // 레벨이 필요한 경험치 목록 생성
    const int iLevelUpExp[LEVEL_MAX] = {4000, 10000, 20000, 35000, 50000, 70000, 100000, 150000, 200000, 400000};
    // 직업의 갯수만큼 테ㅣ블을 만든다.
    _tagLevelUpStatus tLvUpTable[JOB_END -1];
    
    tLvUpTable[JOB_KNIGHT -1].iAttackMin = 4;
    tLvUpTable[JOB_KNIGHT -1].iAttackMax = 10;
    tLvUpTable[JOB_KNIGHT -1].iArmorMin = 8;
    tLvUpTable[JOB_KNIGHT -1].iArmorMax = 16;
    tLvUpTable[JOB_KNIGHT -1].iHPMin = 50;
    tLvUpTable[JOB_KNIGHT -1].iHPMax = 100;
    tLvUpTable[JOB_KNIGHT -1].iMPMin = 10;
    tLvUpTable[JOB_KNIGHT -1].iMPMax = 20;
    
    tLvUpTable[JOB_ARCHER -1].iAttackMin = 10;
    tLvUpTable[JOB_ARCHER -1].iAttackMax = 15;
    tLvUpTable[JOB_ARCHER -1].iArmorMin = 5;
    tLvUpTable[JOB_ARCHER -1].iArmorMax = 10;
    tLvUpTable[JOB_ARCHER -1].iHPMin = 30;
    tLvUpTable[JOB_ARCHER -1].iHPMax = 60;
    tLvUpTable[JOB_ARCHER -1].iMPMin = 30;
    tLvUpTable[JOB_ARCHER -1].iMPMax = 50;
    
    tLvUpTable[JOB_WIZARD -1].iAttackMin = 15;
    tLvUpTable[JOB_WIZARD -1].iAttackMax = 20;
    tLvUpTable[JOB_WIZARD -1].iArmorMin = 3;
    tLvUpTable[JOB_WIZARD -1].iArmorMax = 7;
    tLvUpTable[JOB_WIZARD -1].iHPMin = 20;
    tLvUpTable[JOB_WIZARD -1].iHPMax = 40;
    tLvUpTable[JOB_WIZARD -1].iMPMin = 50;
    tLvUpTable[JOB_WIZARD -1].iMPMax = 100;
    
    // 게임 시작 때 플레이어 정보 설정
    _tagPlayer tPlayer = {};
    cout << "이름: ";
    cin.getline(tPlayer.strName, NAME_SIZE - 1); // 한줄로 입력, & NAME_SIZE 보다 하나 작게 하여 null 을 넣을 수 있는 공간을 만든다. (문자열은 마지막에 null 을 넣어야 한다.)
    
    // 직업 설정
    int iJob = JOB_NONE;
    while(iJob == JOB_NONE) {
        system("cls");
        cout << "1. 기사" << endl;
        cout << "2. 궁수" << endl;
        cout << "3. 마법사" << endl;
        cout << "직업을 선택하세요: ";
        cin >> iJob;
        
        if(cin.fail()) {
            cin.clear();
            cin.ignore(1024, '\n');
            continue;
        }
        
        // 잘못 입력했을 경우 반복시키기 위함
        if(iJob <= JOB_NONE || iJob >= JOB_END) {
            iJob = JOB_NONE;
        }
    }
    
    tPlayer.eJob = (JOB)iJob;
    switch (tPlayer.eJob) {
        case JOB_KNIGHT:
            strcpy(tPlayer.strJobName, "기사");
            tPlayer.iAttackMin = 5;
            tPlayer.iAttackMax = 10;
            tPlayer.iArmorMin = 15;
            tPlayer.iArmorMax = 20;
            tPlayer.iHP = 500;
            tPlayer.iHPMax = 500;
            tPlayer.iMP = 100;
            tPlayer.iMPMax = 100;
            break;
        case JOB_ARCHER:
            strcpy(tPlayer.strJobName, "궁수");
            tPlayer.iAttackMin = 10;
            tPlayer.iAttackMax = 15;
            tPlayer.iArmorMin = 10;
            tPlayer.iArmorMax = 15;
            tPlayer.iHP = 400;
            tPlayer.iHPMax = 400;
            tPlayer.iMP = 200;
            tPlayer.iMPMax = 200;
            break;
        case JOB_WIZARD:
            strcpy(tPlayer.strJobName, "마법사");
            tPlayer.iAttackMin = 15;
            tPlayer.iAttackMax = 20;
            tPlayer.iArmorMin = 5;
            tPlayer.iArmorMax = 10;
            tPlayer.iHP = 300;
            tPlayer.iHPMax = 300;
            tPlayer.iMP = 300;
            tPlayer.iMPMax = 300;
            break;
        default:
            break;
    }
    
    // 관련 없는 초기값 설정
    tPlayer.iLevel = 1;
    tPlayer.iExp = 0;
    tPlayer.tInventory.iGold = 10000;
    
    
    // 몬스터 생성
    _tagMonster tMonsterArr[MT_BACK - 1] = {};
    // 고블린 생성
    strcpy(tMonsterArr[0].strName, "고블린");
    tMonsterArr[0].iAttackMin = 20;
    tMonsterArr[0].iAttackMax = 30;
    tMonsterArr[0].iArmorMin = 2;
    tMonsterArr[0].iArmorMax = 5;
    tMonsterArr[0].iHP = 100;
    tMonsterArr[0].iHPMax = 100;
    tMonsterArr[0].iMP = 10;
    tMonsterArr[0].iMPMax = 10;
    tMonsterArr[0].iLevel = 1;
    tMonsterArr[0].iExp = 1000;
    tMonsterArr[0].iGoldMin = 500;
    tMonsterArr[0].iGoldMax = 1500;
    // 트롤 생성
    strcpy(tMonsterArr[1].strName, "트롤");
    tMonsterArr[1].iAttackMin = 80;
    tMonsterArr[1].iAttackMax = 130;
    tMonsterArr[1].iArmorMin = 60;
    tMonsterArr[1].iArmorMax = 90;
    tMonsterArr[1].iHP = 2000;
    tMonsterArr[1].iHPMax = 2000;
    tMonsterArr[1].iMP = 100;
    tMonsterArr[1].iMPMax = 100;
    tMonsterArr[1].iLevel = 5;
    tMonsterArr[1].iExp = 7000;
    tMonsterArr[1].iGoldMin = 6000;
    tMonsterArr[1].iGoldMax = 8000;
    // 드래곤 생성
    strcpy(tMonsterArr[1].strName, "드래곤");
    tMonsterArr[2].iAttackMin = 250;
    tMonsterArr[2].iAttackMax = 500;
    tMonsterArr[2].iArmorMin = 200;
    tMonsterArr[2].iArmorMax = 400;
    tMonsterArr[2].iHP = 30000;
    tMonsterArr[2].iHPMax = 30000;
    tMonsterArr[2].iMP = 20000;
    tMonsterArr[2].iMPMax = 20000;
    tMonsterArr[2].iLevel = 10;
    tMonsterArr[2].iExp = 30000;
    tMonsterArr[2].iGoldMin = 20000;
    tMonsterArr[2].iGoldMax = 50000;
    
    // 상점에서 판매할 아이템 목록을 생성
    _tagItem tStoreWeapon[STORE_WEAPON_MAX] = {};
    _tagItem tStoreArmor[STORE_ARMOR_MAX] = {};
    
    // 각 아이템 정보들을 설정해준다.
    strcpy(tStoreWeapon[0].strName, "목검");
    strcpy(tStoreWeapon[0].strTypeName, "무기");
    tStoreWeapon[0].eType = (ITEM_TYPE)ITEM_WEAPON;
    tStoreWeapon[0].iMin = 5;
    tStoreWeapon[0].iMax = 10;
    tStoreWeapon[0].iPrice = 1000;
    tStoreWeapon[0].iSell = 500;
    strcpy(tStoreWeapon[0].strDesc, "나무로 만든 칼");
    
    strcpy(tStoreWeapon[1].strName, "장궁");
    strcpy(tStoreWeapon[1].strTypeName, "무기");
    tStoreWeapon[1].eType = (ITEM_TYPE)ITEM_WEAPON;
    tStoreWeapon[1].iMin = 20;
    tStoreWeapon[1].iMax = 40;
    tStoreWeapon[1].iPrice = 7000;
    tStoreWeapon[1].iSell = 3500;
    strcpy(tStoreWeapon[1].strDesc, "짱짱한 활");
    
    strcpy(tStoreWeapon[2].strName, "지팡이");
    strcpy(tStoreWeapon[2].strTypeName, "무기");
    tStoreWeapon[2].eType = (ITEM_TYPE)ITEM_WEAPON;
    tStoreWeapon[2].iMin = 90;
    tStoreWeapon[2].iMax = 150;
    tStoreWeapon[2].iPrice = 30000;
    tStoreWeapon[2].iSell = 15000;
    strcpy(tStoreWeapon[2].strDesc, "나무로 만든 지팡이");
    
    strcpy(tStoreArmor[0].strName, "천갑옷");
    strcpy(tStoreArmor[0].strTypeName, "방어구");
    tStoreArmor[0].eType = (ITEM_TYPE)ITEM_ARMOR;
    tStoreArmor[0].iMin = 2;
    tStoreArmor[0].iMax = 5;
    tStoreArmor[0].iPrice = 1000;
    tStoreArmor[0].iSell = 500;
    strcpy(tStoreArmor[0].strDesc, "천으로 만든 허접한 갑옷");
    
    strcpy(tStoreArmor[1].strName, "가죽갑옷");
    strcpy(tStoreArmor[1].strTypeName, "방어구");
    tStoreArmor[1].eType = (ITEM_TYPE)ITEM_ARMOR;
    tStoreArmor[1].iMin = 10;
    tStoreArmor[1].iMax = 20;
    tStoreArmor[1].iPrice = 7000;
    tStoreArmor[1].iSell = 3500;
    strcpy(tStoreArmor[1].strDesc, "동물 가죽으로 만든 질긴 갑옷");
    
    strcpy(tStoreArmor[2].strName, "플레이트 아머");
    strcpy(tStoreArmor[2].strTypeName, "방어구");
    tStoreArmor[2].eType = (ITEM_TYPE)ITEM_ARMOR;
    tStoreArmor[2].iMin = 70;
    tStoreArmor[2].iMax = 90;
    tStoreArmor[2].iPrice = 30000;
    tStoreArmor[2].iSell = 15000;
    strcpy(tStoreArmor[2].strDesc, "강철로 만든 판금 갑옷");
    
    while (true) {
        system("cls");
        cout << "*************** 로비 ***************" << endl;
        cout << "1. 맵" << endl;
        cout << "2. 상점" << endl;
        cout << "3. 가방" << endl;
        cout << "4. 종료" << endl;
        cout << "메뉴를 선택하세요: ";
        int iMenu;
        cin >> iMenu;
        
        // 형식에 어긋나는 메뉴 선택시 처리
        if(cin.fail()) {
            cin.clear(); // 값을 비우고
            cin.ignore(1024, '\n'); // \n 을 지움
            continue;
        }
        
        // 종료
        if(iMenu == MM_EXIT) {
            break;
        }
        
        // 각각의 메뉴에 대한 선택
        switch (iMenu) {
            case MM_MAP:
                while(true) {
                    system("cls");
                    cout << "*************** 맵 ***************" << endl;
                    cout << "1. 쉬움" << endl;
                    cout << "2. 보통" << endl;
                    cout << "3. 어려움" << endl;
                    cout << "4. 뒤로가기" << endl;
                    cout << "맵을 선택하세요: ";
                    cin >> iMenu;
                    if(cin.fail()) {
                        cin.clear();
                        cin.ignore(1024, '\n');
                        continue;
                    }
                    
                    // 맵 상태 종료
                    if(iMenu == MT_BACK) {
                        break;
                    }
                    
                    // 선택한 메뉴에서 1을 빼주면 몬스터 배열의 인덱스!
                    _tagMonster tMonster = tMonsterArr[iMenu - 1];
                    
                    while (true) {
                        system("cls");
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
                        
                        // 플레이어 정보를 출력
                        cout << "*************** Player ***************" << endl;
                        cout << "이름: " << tPlayer.strName << "\t직업: " << tPlayer.strJobName << endl;
                        cout << "레벨: " << tPlayer.iLevel << "\t경험치: " << tPlayer.iExp << " / " << iLevelUpExp[tPlayer.iLevel - 1] << endl;
                        if(tPlayer.bEquip[EQ_WEAPON]) {
                            cout << "공격력: " << tPlayer.iAttackMin << " + " << tPlayer.tEquip[EQ_WEAPON].iMin << " - " <<
                            tPlayer.iAttackMax << " + " << tPlayer.tEquip[EQ_WEAPON].iMax << endl;
                        } else {
                            cout << "공격력: " << tPlayer.iAttackMin << " - " << tPlayer.iAttackMax << endl;
                        }
                        if(tPlayer.bEquip[EQ_ARMOR]) {
                            cout << "벙어력: " << tPlayer.iArmorMin << " + " << tPlayer.tEquip[EQ_ARMOR].iMin << " - " <<
                            tPlayer.iArmorMax << " + " << tPlayer.tEquip[EQ_ARMOR].iMax << endl;
                        } else {
                            cout << "벙어력: " << tPlayer.iArmorMin << " - " << tPlayer.iArmorMax << endl;
                        }
                        cout << "체력: " << tPlayer.iHP << " / " << tPlayer.iHPMax <<
                            "\t마나: " << tPlayer.iMP << " / " << tPlayer.iMPMax << endl;
                        if(tPlayer.bEquip[EQ_WEAPON]) {
                            cout << "장착무기: " << tPlayer.tEquip[EQ_WEAPON].strName << "\t";
                        } else {
                            cout << "장착무기: 없음" << "\t";
                        }
                        if(tPlayer.bEquip[EQ_ARMOR]) {
                            cout << "장착방어구: " << tPlayer.tEquip[EQ_ARMOR].strName << endl;
                        } else {
                            cout << "장착방어구: 없음" << endl;
                        }
                        cout << "보유 골드: " << tPlayer.tInventory.iGold << " Gold" << endl << endl;
                        
                        // 몬스터 정보를 출력
                        cout << "*************** Monster ***************" << endl;
                        cout << "이름: " << tMonster.strName << "\t레벨: " << tMonster.iLevel << endl;
                        cout << "공격력: " << tMonster.iAttackMin << " - " << tMonster.iAttackMax <<
                        "\t벙어력: " << tMonster.iArmorMin << " - " << tMonster.iArmorMax << endl;
                        cout << "체력: " << tMonster.iHP << " / " << tMonster.iHPMax <<
                        "\t마나: " << tMonster.iMP << " / " << tMonster.iMPMax << endl;
                        cout << "획득경험치: " << tMonster.iExp << "\t획득 골드: " << tMonster.iGoldMin << " - " << tMonster.iGoldMax << endl << endl;
                        
                        cout << "1. 공격" << endl;
                        cout << "2. 도망가기" << endl;
                        cout << "매뉴룰 선택하세요: " << endl;
                        cin >> iMenu;
                        if(cin.fail()) {
                            cin.clear();
                            cin.ignore(1024, '\n');
                            continue;
                        }
                        
                        if(iMenu == BATTLE_BACK) {
                            break;
                        }
                        switch (iMenu) {
                            case BATTLE_ATTACK:
                                // 공격력
                                int iAttackMin = tPlayer.iAttackMin;
                                int iAttackMax = tPlayer.iArmorMax;
                                // 무기 장착시 min max 를 더해줌
                                if(tPlayer.bEquip[EQ_WEAPON]) {
                                    iAttackMin += tPlayer.tEquip[EQ_WEAPON].iMin;
                                    iAttackMax += tPlayer.tEquip[EQ_WEAPON].iMax;
                                }
                                
                                int iAttack = rand() % (iAttackMax - iAttackMin + 1) + (iAttackMin); // 공격값
                                int iArmor = rand() % (tMonster.iArmorMax - tMonster.iArmorMax + 1) + (tMonster.iArmorMin); // 방어값
                                int iDamage = iAttack - iArmor;
                                iDamage = iDamage < 1 ? 1 : iDamage; // 삼항연산자
                                
                                // 몬스터 HP 를 감소시킨다.
                                tMonster.iHP -= iDamage;
                                cout << tPlayer.strName << "가 " << tMonster.strName << "에게 " << iDamage << " 피해를 입혔습니다." << endl;
                                // 몬스터가 죽었을 경우
                                if(tMonster.iHP <= 0) {
                                    cout << tMonster.strName << " 몬스터가 사망하였습니다." << endl;
                                    tPlayer.iExp += tMonster.iExp;
                                    int iGold = (rand() % (tMonster.iGoldMax - tMonster.iGoldMin + 1) + tMonster.iGoldMin);
                                    tPlayer.tInventory.iGold += iGold;
                                    
                                    cout << tMonster.iExp << " 경험치를 획득하였습니다." << endl;
                                    cout << iGold << " Gold를 획득하였습니다." << endl;
                                    
                                    // 죽었을 경우 새로운 몬스터를 생성!
                                    tMonster.iHP = tMonster.iHPMax;
                                    tMonster.iMP = tMonster.iMPMax;
                                    
                                    // 레벨업 체크
                                    if(tPlayer.iExp >= iLevelUpExp[tPlayer.iLevel - 1]) {
                                        // 플레이어 경험치를 레벨업에 필요한 경험치 만큼 차감
                                        tPlayer.iExp -= iLevelUpExp[tPlayer.iLevel - 1];
                                        // 레벨업
                                        tPlayer.iLevel++;
                                        
                                        cout << "레벨 업" << endl;
                                        
                                        // 능력치 상승
                                        int iJobIndex = tPlayer.eJob - 1;
                                        int iHPUp = rand() % (tLvUpTable[iJobIndex].iHPMax - tLvUpTable[iJobIndex].iHPMin +1 ) + tLvUpTable[iJobIndex].iHPMin;
                                        int iMPUp = rand() % (tLvUpTable[iJobIndex].iMPMax - tLvUpTable[iJobIndex].iMPMin +1 ) + tLvUpTable[iJobIndex].iMPMin;
                                        
                                        tPlayer.iAttackMin += tLvUpTable[iJobIndex].iAttackMin;
                                        tPlayer.iAttackMax += tLvUpTable[iJobIndex].iAttackMax;
                                        tPlayer.iArmorMin += tLvUpTable[iJobIndex].iArmorMin;
                                        tPlayer.iArmorMax += tLvUpTable[iJobIndex].iArmorMax;
                                        tPlayer.iHPMax += iHPUp;
                                        tPlayer.iMPMax += iMPUp;
                                        
                                        // 체력과 마나 회복
                                        tPlayer.iHP = tPlayer.iHPMax;
                                        tPlayer.iMP = tPlayer.iMPMax;
                                    }
                                    
                                    break;
                                }
                                
                                // 방어력(방어구 확인)
                                int iArmorMin = tPlayer.iAttackMin;
                                int iArmorMax = tPlayer.iArmorMax;
                                // 장착구 확인
                                if(tPlayer.bEquip[EQ_ARMOR]) {
                                    iArmorMin += tPlayer.tEquip[EQ_ARMOR].iMin;
                                    iArmorMax += tPlayer.tEquip[EQ_ARMOR].iMax;
                                }
                                
                                // 몬스터가 살아 있다면 플레이어를 공격한다.
                                iAttack = rand() % (tMonster.iAttackMax - tMonster.iAttackMin + 1) + (tMonster.iAttackMin); // 공격값
                                iArmor = rand() % (tPlayer.iArmorMax - tPlayer.iArmorMax + 1) + (tPlayer.iArmorMin); // 방어값
                                iDamage = iAttack - iArmor;
                                iDamage = iDamage < 1 ? 1 : iDamage; // 삼항연산자
                                
                                // 플레이어의 HP 를 감소시킨다.
                                tPlayer.iHP -= iDamage;
                                cout << tMonster.strName << "가 " << tPlayer.strName << "에게 " << iDamage << " 피해를 입혔습니다." << endl;
                                // 몬스터가 죽었을 경우
                                if( tPlayer.iHP <= 0) {
                                    cout << tPlayer.strName << " 플레이어가 사망하였습니다." << endl;
                                    
                                    // 죽으면 10프로씩 감소시킴
                                    int iExp = tPlayer.iExp * 0.1f;
                                    int iGold = tPlayer.tInventory.iGold * 0.1f;
                                    
                                    tPlayer.iExp -= iExp;
                                    tPlayer.tInventory.iGold -= iGold;
                                    
                                    cout << iExp << " 경험치를 잃었습니다." << endl;
                                    cout << iGold << " Gold를 잃었습니다." << endl;
                                    
                                    // 플레이어의 HP 와 MP 를 회복
                                    tPlayer.iHP = tPlayer.iHPMax;
                                    tPlayer.iMP = tPlayer.iMPMax;
                                    
                                    break;
                                }
                                
                                system("pause");
                                break;
                        }
                    }
                }
                break;
            case MM_STORE:
                while(true) {
                    system("cls");
                    cout << "*************** 상점 ***************" << endl;
                    cout << "1. 무기상점" << endl;
                    cout << "2. 방어구상점" << endl;
                    cout << "3. 뒤로가기" << endl;
                    cout << "상점을 선택하세요: ";
                    cin >> iMenu;
                    if(cin.fail()) {
                        cin.clear();
                        cin.ignore(1024, '\n');
                        continue;
                    }
                    
                    if(iMenu == SM_BACK) {
                        break;
                    }
                    
                    switch (iMenu) {
                        case SM_WEAPON:
                            while(true) {
                                system("cls");
                                // 상점 목록을 보여준다.
                                cout << "*************** 무기상점 ***************" << endl;
                                for(int i=0; i<STORE_WEAPON_MAX; i++) {
                                    cout << i +1 << ". 이름: " << tStoreWeapon[i].strName << "\t종류: " <<tStoreWeapon[i].strTypeName << endl;
                                    cout << "공격력: " << tStoreWeapon[i].iMin << " - " << tStoreWeapon[i].iMax << endl;
                                    cout << "판매가격: " << tStoreWeapon[i].iPrice << "\t구매가격: " <<tStoreWeapon[i].iSell << endl;
                                    cout << "설명: " << tStoreWeapon[i].strDesc << endl << endl;
                                }
                                
                                cout << STORE_WEAPON_MAX + 1 << ". 뒤로가기" << endl;
                                cout << "보유금액: " << tPlayer.tInventory.iGold << " Gold" << endl;
                                cout << "남은공간: " << INVENTORY_MAX - tPlayer.tInventory.iItemCount << endl;
                                cout << "구입할 아이템을 선택하세요: ";
                                cin >> iMenu;
                                
                                if(cin.fail()) {
                                    cin.clear();
                                    cin.ignore(1024, '\n');
                                    continue;
                                }
                                
                                if (iMenu == STORE_WEAPON_MAX + 1) {
                                    break;
                                } else if(iMenu < 1 || iMenu > STORE_WEAPON_MAX + 1) {
                                    cout << "잘못 입력하였습니다." << endl;
                                    system("pause");
                                    continue;
                                }
                                
                                // 상점 판매목록 배열의 인덱스를 구해준다.
                                int iWeaponIndex = iMenu - 1;
                                
                                if(tPlayer.tInventory.iItemCount == INVENTORY_MAX) {
                                    // 인벤토리가 꽉 찼는지 검사
                                    cout << "가방이 꽉 찼습니다." << endl;
                                    system("pause");
                                    continue;
                                } else if(tPlayer.tInventory.iGold < tStoreWeapon[iWeaponIndex].iPrice) {
                                    // 돈이 부족한 경우
                                    cout << "보유 금액이 부족합니다." << endl;
                                    system("pause");
                                    continue;
                                }
                                
                                // 처음에 iItemCount 는 한개도 없기 때문에 0으로 초기화!
                                tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount] = tStoreWeapon[iWeaponIndex];
                                tPlayer.tInventory.iItemCount++;
                                
                                // 골드 차감
                                tPlayer.tInventory.iGold -= tStoreWeapon[iWeaponIndex].iPrice;
                                
                                cout << tStoreWeapon[iWeaponIndex].strName << " 아이템을 구매하였습니다." << endl;
                                system("pause");
                                
                            }
                            break;
                        case SM_ARMOR:
                            while(true) {
                                system("cls");
                                // 상점 목록을 보여준다.
                                cout << "*************** 방어구 상점 ***************" << endl;
                                for(int i=0; i<STORE_ARMOR_MAX; i++) {
                                    cout << i +1 << ". 이름: " << tStoreArmor[i].strName << "\t종류: " <<tStoreArmor[i].strTypeName << endl;
                                    cout << "공격력: " << tStoreArmor[i].iMin << " - " << tStoreArmor[i].iMax << endl;
                                    cout << "판매가격: " << tStoreArmor[i].iPrice << "\t구매가격: " <<tStoreArmor[i].iSell << endl;
                                    cout << "설명: " << tStoreArmor[i].strDesc << endl << endl;
                                }
                                
                                cout << STORE_ARMOR_MAX + 1 << ". 뒤로가기" << endl;
                                cout << "보유금액: " << tPlayer.tInventory.iGold << " Gold" << endl;
                                cout << "남은공간: " << INVENTORY_MAX - tPlayer.tInventory.iItemCount << endl;
                                cout << "구입할 아이템을 선택하세요: ";
                                cin >> iMenu;
                                
                                if(cin.fail()) {
                                    cin.clear();
                                    cin.ignore(1024, '\n');
                                    continue;
                                }
                                
                                if (iMenu == STORE_ARMOR_MAX + 1) {
                                    break;
                                } else if(iMenu < 1 || iMenu > STORE_ARMOR_MAX + 1) {
                                    cout << "잘못 입력하였습니다." << endl;
                                    system("pause");
                                    continue;
                                }
                                
                                // 상점 판매목록 배열의 인덱스를 구해준다.
                                int iArmorIndex = iMenu - 1;
                                
                                if(tPlayer.tInventory.iItemCount == INVENTORY_MAX) {
                                    // 인벤토리가 꽉 찼는지 검사
                                    cout << "가방이 꽉 찼습니다." << endl;
                                    system("pause");
                                    continue;
                                } else if(tPlayer.tInventory.iGold < tStoreArmor[iArmorIndex].iPrice) {
                                    // 돈이 부족한 경우
                                    cout << "보유 금액이 부족합니다." << endl;
                                    system("pause");
                                    continue;
                                }
                                
                                // 처음에 iItemCount 는 한개도 없기 때문에 0으로 초기화!
                                tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount] = tStoreArmor[iArmorIndex];
                                tPlayer.tInventory.iItemCount++;
                                
                                // 골드 차감
                                tPlayer.tInventory.iGold -= tStoreArmor[iArmorIndex].iPrice;
                                
                                cout << tStoreArmor[iArmorIndex].strName << " 아이템을 구매하였습니다." << endl;
                                system("pause");
                                
                            }
                            break;
                    }
                }
                break;
            case MM_INVENTORY:
                while(true) {
                    system("cls");
                    cout << "*************** 가방 ***************" << endl;
                    cout << "*************** Player ***************" << endl;
                    cout << "이름: " << tPlayer.strName << "\t직업: " << tPlayer.strJobName << endl;
                    cout << "레벨: " << tPlayer.iLevel << "\t경험치: " << tPlayer.iExp << " / " << iLevelUpExp[tPlayer.iLevel - 1] << endl;
                    // 아이템 착용 여부에 따라 공격력/방어력 표시를 다르게
                    if(tPlayer.bEquip[EQ_WEAPON]) {
                        cout << "공격력: " << tPlayer.iAttackMin << " + " << tPlayer.tEquip[EQ_WEAPON].iMin << " - " <<
                            tPlayer.iAttackMax << " + " << tPlayer.tEquip[EQ_WEAPON].iMax << endl;
                    } else {
                        cout << "공격력: " << tPlayer.iAttackMin << " - " << tPlayer.iAttackMax << endl;
                    }
                    if(tPlayer.bEquip[EQ_ARMOR]) {
                        cout << "벙어력: " << tPlayer.iArmorMin << " + " << tPlayer.tEquip[EQ_ARMOR].iMin << " - " <<
                            tPlayer.iArmorMax << " + " << tPlayer.tEquip[EQ_ARMOR].iMax << endl;
                    } else {
                        cout << "벙어력: " << tPlayer.iArmorMin << " - " << tPlayer.iArmorMax << endl;
                    }
                    cout << "체력: " << tPlayer.iHP << " / " << tPlayer.iHPMax <<
                    "\t마나: " << tPlayer.iMP << " / " << tPlayer.iMPMax << endl;
                    if(tPlayer.bEquip[EQ_WEAPON]) {
                        cout << "장착무기: " << tPlayer.tEquip[EQ_WEAPON].strName << "\t";
                    } else {
                        cout << "장착무기: 없음" << "\t";
                    }
                    if(tPlayer.bEquip[EQ_ARMOR]) {
                        cout << "장착방어구: " << tPlayer.tEquip[EQ_ARMOR].strName << endl;
                    } else {
                        cout << "장착방어구: 없음" << endl;
                    }
                    cout << "보유 골드: " << tPlayer.tInventory.iGold << " Gold" << endl << endl;
                    
                    for(int i=0; i<tPlayer.tInventory.iItemCount; i++) {
                        cout << i +1 << ". 이름: " << tPlayer.tInventory.tItem[i].strName << "\t종류: " << tPlayer.tInventory.tItem[i].strTypeName << endl;
                        cout << "공격력: " << tPlayer.tInventory.tItem[i].iMin << " - " << tPlayer.tInventory.tItem[i].iMax << endl;
                        cout << "판매가격: " << tPlayer.tInventory.tItem[i].iPrice << "\t구매가격: " << tPlayer.tInventory.tItem[i].iSell << endl;
                        cout << "설명: " << tPlayer.tInventory.tItem[i].strDesc << endl << endl;
                    }
                    
                    cout << tPlayer.tInventory.iItemCount + 1 << ". 뒤로가기" << endl;
                    cout << "장착할 아이템을 선택하세요: ";
                    cin >> iMenu;
                    if(cin.fail()) {
                        cin.clear();
                        cin.ignore(1024, '\t');
                        continue;
                    }
                    
                    if( iMenu == tPlayer.tInventory.iItemCount + 1) {
                        break;
                    } else if(iMenu < 1 || iMenu > tPlayer.tInventory.iItemCount + 1) {
                        cout << "잘못 선택하였습니다." << endl;
                        system("pasue");
                        continue;
                    }
                    // 아이템 인텍스를 구한다.
                    int idx = iMenu - 1;
                    // 제대로 선택했을 경우 해당 아이템의 종류에 따라 장차 부위를 결정
                    EQUIP eq;
                    
                    switch (tPlayer.tInventory.tItem[idx].eType) {
                        case ITEM_WEAPON:
                            eq = EQ_WEAPON;
                            break;
                        case ITEM_ARMOR:
                            eq = EQ_ARMOR;
                            break;
                    }
                    
                    // 아이템이 장착되어 있을 경우 장착되어 있는 아이템과 장착할 아이템을 교체
                    // 그렇지 않을 경우 장착하고 한칸 비우기 (안쪽으로 push)
                    if(tPlayer.bEquip[eq] == true) {
                        _tagItem tSwap = tPlayer.tEquip[eq];
                        tPlayer.tEquip[eq] = tPlayer.tInventory.tItem[idx];
                        tPlayer.tInventory.tItem[idx] = tSwap;
                    } else {
                        tPlayer.tEquip[eq] = tPlayer.tInventory.tItem[idx];
                        for(int i=0; i< tPlayer.tInventory.iItemCount - 1; i++) {
                            tPlayer.tInventory.tItem[i] = tPlayer.tInventory.tItem[i+1];
                        }
                        tPlayer.tInventory.iItemCount--;
                        tPlayer.bEquip[eq] = true; // 장착
                    }
                    cout << tPlayer.tEquip[eq].strName << " 아이템을 장착하였습니다." << endl;
                    system("pause");
                }

                break;
            default:
                cout << "잘못 선택하였습니다." << endl;
                break;
        }
    }
    return 0;
}









