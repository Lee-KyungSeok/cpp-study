#include "Stage.h"
#include "FileStream.h"
#include "Player.h"
#include "ObjectManager.h"

CStage::CStage()
{
}

CStage::~CStage()
{
}

bool CStage::Init() {
	return true;
}

bool CStage::Init(char * pFileName) {
	CFileStream file;

	if (!file.Open(pFileName, (char*)"rt"))
		return false;

	for (int i = 0; i < 10; i++) {
		int iSize = 0;
		file.ReadLine(m_cOriginStage[i], iSize);

		for (int j = 0; j < 50; j++) {
			m_cStage[i][j] = m_cOriginStage[i][j];

			if (m_cOriginStage[i][j] == SBT_START) {
				m_tStart.x = j;
				m_tStart.y = i;
			}

			if (m_cOriginStage[i][j] == SBT_END) {
				m_tEnd.x = j;
				m_tEnd.y = i;
			}
		}
	}

	return true;
}

void CStage::Render() {

	// 맵은 스크롤 처리를 해야한다. 따라서 현재 플레이어가 이동한 위치로부터 맵을 출력해야 한다.
	// 출력 크기는 세로 4칸 가로 10칸으로 한다.
	// 현재 플레이어가 처음에 있다라고 가정하고 처음 4x10 출력을 한다.
	//  - 0: 벽
	//  - 1: 길
	//  - 2: 시작점
	//  - 3: 도착점
	//  - 4: 코인

	// 플레이어 가져오기
	CPlayer* pPlayer = CObjectManager::GetInst()->GetPlayer();

	// 플레이어의 x,y 좌표를 얻어온다.
	int iX = pPlayer->GetX();
	int iY = pPlayer->GetY();

	// 맵 출력 시 X, Y 갯수를 구한다.
	int iYCount = iY + (RENDER_BLOCK_Y / 2);
	if (iYCount >= BLOCK_Y) {
		iYCount = BLOCK_Y - 1;
	}

	// 출력할 Y 의 최소 index 를 구해준다.
	int iYMin = iYCount - (RENDER_BLOCK_Y - 1);
	if (iYMin < 0) {
		iYMin = 0;
	}

	int iXCount = iX + RENDER_BLOCK_X;
	if (iXCount >= BLOCK_X) {
		iXCount = BLOCK_X;
	}

	// 가장 마지막 길 10칸을 모두 보여주기 위해서 반복문의 최솟값을 (블럭 전체길이 - 출력된 블럭) 으로 처리해준다.
	int iXMin = iX;
	if (iXMin > BLOCK_X - RENDER_BLOCK_X) {
		iXMin = BLOCK_X - RENDER_BLOCK_X;
	}

	// 맵의 출력은 플레이어의 위치를 중심으로 출력
	//  - 세로: 플레이어 위 2칸 ~ 1칸 아래 (총 4줄)
	//  - 가로: 플레이어 위치부터 오른쪽 10칸 (총 10줄)
	for (int i = iYMin; i <= iYCount; i++) {
		for (int j = iXMin; j < iXCount; j++) {

			if ((i == iY || (i == iY - 1 && pPlayer->GetBigItemEnable())) && j == iX) {
				cout << "§";
			} else if (CObjectManager::GetInst()->CheckBullet(j,i)) {
				cout << "●";
			} else if (m_cStage[i][j] == SBT_WALL) {
				cout << "■";
			} else if (m_cStage[i][j] == SBT_ROAD) {
				cout << "  ";
			} else if (m_cStage[i][j] == SBT_START) {
				cout << "☆";
			} else if (m_cStage[i][j] == SBT_END) {
				cout << "★";
			} else if (m_cStage[i][j] == SBT_COIN) {
				cout << "＠";
			} else if (m_cStage[i][j] == SBT_ITEM_BULLET) {
				cout << "♥";
			} else if (m_cStage[i][j] == SBT_ITEM_BIG) {
				cout << "◎";
			}
		}
		cout << endl;

	}
}

// 맵을 초기화
void CStage::ResetStage() {
	for (int i = 0; i < BLOCK_Y; i++) {
		for (int j = 0; j < BLOCK_X; j++) {
			m_cStage[i][j] = m_cOriginStage[i][j];
		}
	}
}
