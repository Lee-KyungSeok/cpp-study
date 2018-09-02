#include "Player.h"
#include "MapManager.h"
#include "Stage.h"
#include "ObjectManager.h"

CPlayer::CPlayer() {

}

CPlayer::~CPlayer() {

}

bool CPlayer::Init() {

	m_tPos.x = 4;
	m_tPos.y = 8;

	m_bJump = false;
	m_bComplete = false;
	m_iJumpDir = JD_STOP;
	m_iJumpState = 0;
	m_iScore = 0;
	m_bBulletFire = false;
	m_bBigItem = false;

	return true;
}

void CPlayer::Update() {

	CStage* pStage = CMapManager::GetInst()->GetStage();

	// 키 입력을 받는다.
	// GetAsyncKeyState 함수는 win32 API 에서 제공되는 키 입력 함수(MAC 은... ㅜㅜ 일단 ㄲ)
	// A 키를 눌렀을 때 바로 반응하게 하기 위해서 0x8000 과 & 연산을 하여 눌렀을 경우 true 가 나오게 된다.
	if (GetAsyncKeyState('A') & 0x8000) {

		if (pStage->GetBlock(m_tPos.x - 1, m_tPos.y) != SBT_WALL) {

			if (!m_bBigItem) {
				--m_tPos.x;
			}
			else {
				// 커져라 아이템을 획득한 상태라면 바로 위칸의 왼쪽도 체크
				if (pStage->GetBlock(m_tPos.x - 1, m_tPos.y - 1) != SBT_WALL) {
					--m_tPos.x;
				}
			}

			if (m_tPos.x < 0)
				m_tPos.x = 0;
		}
	}

	if (GetAsyncKeyState('D') & 0x8000) {
		if (pStage->GetBlock(m_tPos.x + 1, m_tPos.y) != SBT_WALL) {

			if (!m_bBigItem) {
				++m_tPos.x;
			}
			else {
				// 커져라 아이템을 획득한 상태라면 바로 위칸의 오른쪽도 체크
				if (pStage->GetBlock(m_tPos.x + 1, m_tPos.y - 1) != SBT_WALL) {
					++m_tPos.x;
				}
			}

			if (m_tPos.x >= BLOCK_X)
				m_tPos.x = 49;
		}
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000 && !m_bJump) {
		m_bJump = true;
		m_iJumpDir = JD_UP;
		m_iJumpState = 0;
	}

	int iBigCount = 1;
	// 커져있음을 체크하기 위한 코드
	if (m_bBigItem) {
		iBigCount = 2;
	}

	// jump 가 true 라면?
	if (m_bJump) {
		switch (m_iJumpDir) {
		case JD_UP:
			m_iJumpState++;

			if (m_iJumpState > JUMP_BLOCK_MAX) {
				m_iJumpState = JUMP_BLOCK_MAX;
				m_iJumpDir = JD_DOWN;
			}
			else if (pStage->GetBlock(m_tPos.x, m_tPos.y - iBigCount) == SBT_WALL) {
				m_iJumpState--;
				// 벽을 깼을 때 아이템을 랜덤하게 둘 중 하나로 나오게 한다.
				int iRand = rand() % 100;
				STAGE_BLOCK_TYPE eBlockType;

				if (iRand < 70) {
					eBlockType = SBT_ITEM_BULLET;
				} else {
					eBlockType = SBT_ITEM_BIG;
				}

				pStage->ChangeBlock(m_tPos.x, m_tPos.y - iBigCount, eBlockType);
				m_iJumpDir = JD_DOWN;
			}
			else {
				m_tPos.y--;
			}
			break;
		case JD_DOWN:
			if (m_tPos.y >= BLOCK_Y) {
				cout << "플레이어 사망" << endl;
				system("pause");
				m_tPos.y = BLOCK_Y - 1;
			} else if (pStage->GetBlock(m_tPos.x, m_tPos.y + 1) == SBT_WALL) {
				m_iJumpDir = JD_STOP;
				m_bJump = false;
			}
			else {
				m_tPos.y++;
			}
			break;
		}
	}

	// 점프상태가 아니고 아래가 벽이 아니면 떨어뜨린다.
	if (pStage->GetBlock(m_tPos.x, m_tPos.y + 1) != SBT_WALL && !m_bJump) {
		m_tPos.y++;
	}

	STAGE_BLOCK_TYPE eCurBlockType = (STAGE_BLOCK_TYPE)pStage->GetBlock(m_tPos.x, m_tPos.y);
	STAGE_BLOCK_TYPE eUpBlockType = (STAGE_BLOCK_TYPE)pStage->GetBlock(m_tPos.x, m_tPos.y -1);

	// 코인 먹은 경우
	if (eCurBlockType == SBT_COIN || 
		(eUpBlockType == SBT_COIN && m_bBigItem)) {
		pStage->ChangeBlock(m_tPos.x, m_tPos.y, SBT_ROAD);
		pStage->ChangeBlock(m_tPos.x, m_tPos.y-1, SBT_ROAD);
		m_iScore += 1000;
	}
	// 총알 먹은 경우
	else if (eCurBlockType == SBT_ITEM_BULLET ||
		(eUpBlockType == SBT_ITEM_BULLET && m_bBigItem)) {
		m_bBulletFire = true;
		pStage->ChangeBlock(m_tPos.x, m_tPos.y, SBT_ROAD);
		pStage->ChangeBlock(m_tPos.x, m_tPos.y-1, SBT_ROAD);
	}
	// 커지는 아이템 먹은 경우
	else if (eCurBlockType == SBT_ITEM_BIG ||
		(eUpBlockType == SBT_ITEM_BIG && m_bBigItem)) {
		m_bBigItem = true;
		pStage->ChangeBlock(m_tPos.x, m_tPos.y, SBT_ROAD);
		pStage->ChangeBlock(m_tPos.x, m_tPos.y - 1, SBT_ROAD);
	}
	// 종료 지점에 도달한 경우
	else if (eCurBlockType == SBT_END ||
		(eUpBlockType == SBT_END && m_bBigItem)) {
		m_bComplete = true;
	}

	if (m_tPos.y >= BLOCK_Y) {
		cout << "플레이어 사망" << endl;
		m_tPos = pStage->GetStart();
		Reset();
		pStage->ResetStage();
		system("pause");
		return;
	}

	// 마우스 왼쪽을 누르면 총알 발사
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && m_bBulletFire) {
		// 내 위치에서 한칸 앞에 총알을 넣는다.
		POINT tPos = m_tPos;
		tPos.x++;
		CObjectManager::GetInst()->CreateBullet(tPos);


	}
}