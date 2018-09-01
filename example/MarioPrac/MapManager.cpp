#include "MapManager.h"
#include "Stage.h"
#include "Player.h"
#include "ObjectManager.h"

CMapManager* CMapManager::m_pInst = NULL;

CMapManager::CMapManager()
{
    for (int i = 0; i < STAGE_MAX_COUNT; ++i)
    {
        m_pStage[i] = NULL;
    }
}

CMapManager::~CMapManager()
{
    // 스테이지 메모리 해제
    for (int i = 0; i < STAGE_MAX_COUNT; ++i)
    {
        SAFE_DELETE(m_pStage[i]);
    }
}

CMapManager * CMapManager::GetInst()
{
    if (!m_pInst)
        m_pInst = new CMapManager;

    return m_pInst;
}

void CMapManager::DestroyInst()
{
    SAFE_DELETE(m_pInst);
}

bool CMapManager::Init()
{
    char* pStageFile[3] = {(char*)"Stage1.txt", (char*)"Stage2.txt", (char*)"Stage3.txt"};
    for (int i = 0; i < STAGE_MAX_COUNT; ++i)
    {
        m_pStage[i] = new CStage;

        if (!m_pStage[i]->Init(pStageFile[i]))
            return false;
    }

    return true;
}

void CMapManager::Run(int iStage) {


    CPlayer* pPlayer = CObjectManager::GetInst()->GetPlayer();
    m_iEnableState = iStage;

    pPlayer->setPos(m_pStage[iStage]->GetStart().x, m_pStage[iStage]->GetStart().y);

    while (true) {

        system("cls");

        if(GetAsyncKeyState('Q') & 0x8000) {
            break;
        }

        pPlayer->Update();
        m_pStage[iStage]->Render();
        cout << "Score: " << pPlayer->GetScore() << endl;

        if(pPlayer->GetComplete()) {
            cout << "완료" << endl;
            break;
        }

        // 아래도 윈도우용....
        Sleep(100);
    }
}

void CMapManager::Render() {
    m_pStage[0]->Render();
}

