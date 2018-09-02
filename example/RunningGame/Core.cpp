#include "Core.h"
#include "MapManager.h"
#include "ObjectManager.h"
#include "Player.h"

CCore* CCore::m_pInst = NULL;

// cpp 파일에는 클래스의 구현 부분이 있다.
CCore::CCore() {
	srand((unsigned int)time(0));
}

CCore::~CCore()
{
	CMapManager::DestroyInst();
	CObjectManager::DestroyInst();
}

CCore* CCore::GetInst()
{
	if (!m_pInst)
		m_pInst = new CCore;

	return m_pInst;
}

void CCore::DestroyInst()
{
	SAFE_DELETE(m_pInst);
}

bool CCore::Init()
{
	// 맵 관리자를 초기화한다. 실패시 false 를 리턴
	if (!CMapManager::GetInst()->Init())
		return false;

	// object 관리자를 기화
	if (!CObjectManager::GetInst()->Init())
		return false;

	return true;
}

void CCore::Run() {

	//    CMapManager::GetInst()->Render();

	//    CPlayer* pPlayer = CObjectManager::GetInst()->GetPlayer();

	while (true) {
		system("cls");

		int iStage = OutputMenu();

		if (iStage == 4)
			break;
		else if (iStage == 0)
			continue;

		CMapManager::GetInst()->Run(iStage - 1);
	}
}

int CCore::OutputMenu() {
	system("cls");
	cout << "1. Stage1" << endl;
	cout << "2. Stage2" << endl;
	cout << "3. Stage3" << endl;
	cout << "4. Exit" << endl;
	cout << "input Stage: ";
	int iInput = InputInt();

	if (iInput < 1 || iInput > 4) {
		return 0;
	}

	return iInput;
}