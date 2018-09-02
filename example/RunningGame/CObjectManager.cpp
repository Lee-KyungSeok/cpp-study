
#include "ObjectManager.h"
#include "Player.h"
#include "Bullet.h"

CObjectManager* CObjectManager::m_pInst = NULL;

CObjectManager::CObjectManager()
	: m_pPlayer(NULL) {

}

CObjectManager::~CObjectManager() {
	SAFE_DELETE(m_pPlayer);

	for (int i = 0; i < m_iCurBulletCount; i++) {
		SAFE_DELETE(m_pBullet[i]);
	}
}

bool CObjectManager::Init() {
	m_pPlayer = new CPlayer;

	m_pPlayer->Init();

	// memeset: �޸𸮸� ���� ���ϴ� ������ ���� ����
	//	      - 1�� ���ڿ� ���� ������ �޸� �ּҸ� �־��ش�.
	//		  - 3�� ���ڿ� ���� ������ �޸� ũ�⸦ �־��ش�.
	//        - 1���� �־��� �ּҺ��� 3���� �־��� �޸� ũ�⸸ŭ 2�� ���ڿ� �� ������ �޸𸮸� �ʱ�ȭ���ش�.
	memset(m_pBullet, 0, sizeof(CBullet*) * BULLET_COUNT_MAX); // 4����Ʈ�� 10 �� �̹Ƿ� 40����Ʈ

	m_iCurBulletCount = 0;

	return true;
}

void CObjectManager::Update() {
	m_pPlayer->Update();

	for (int i = 0; i < m_iCurBulletCount; i++) {
		m_pBullet[i]->Update(); // �Ѿ��� ������Ʈ�� ��� �����Ѵ�.
	}


	for (int i = 0; i < m_iCurBulletCount;) {
		// �Ѿ��� �����Ǿ�� �� ���
		if (!m_pBullet[i]->GetEnable()) {
			delete m_pBullet[i];

			for (int j = 0; j < m_iCurBulletCount; j++) {
				m_pBullet[j] = m_pBullet[j + 1];
			}

			// ���� ������ �ε����� NULL �� �ʱ�ȭ
			m_pBullet[m_iCurBulletCount - 1] = NULL;

			m_iCurBulletCount--;

		}
		//  �Ѿ��� �������� ���� ��� i �� 1 ����
		else {
			i++;
		}
	}
}

bool CObjectManager::CreateBullet(POINT tPos) {
	// �Ѿ� ������ ������ �Ѿ��� �̹� �ִ�ġ��� ���̻� �������� �ʴ´�.
	if (m_iCurBulletCount == BULLET_COUNT_MAX) {
		return false;
	}

	// �Ѿ��� �����Ѵ�.
	CBullet* pBullet = new CBullet;

	// �Ѿ��� �ʱ�ȭ�Ѵ�. �Ѿ� �ʱ�ȭ ���н� ������ �Ѿ��� ����� false �� ��ȯ�Ѵ�.
	if (!pBullet->Init()) {
		SAFE_DELETE(pBullet);
		return false;
	}

	// ������ ���� ��ġ�� �Ѿ��� ��ġ�� �����Ѵ�.
	pBullet->SetPos(tPos.x, tPos.y);

	m_pBullet[m_iCurBulletCount] = pBullet;
	m_iCurBulletCount++;

	return true;
}

// �ش� ��ġ�� �Ѿ��� �ִ��� �Ѿ˸�Ͽ��� �˻�
// ���� ��� true, ���� ��� false �� ��ȯ
// �ش� ��ġ�� �Ѿ��� �ִ����� �Ǵ�
bool CObjectManager::CheckBullet(int x, int y) {
	// ���� �Ѿ��� �߰��� ����ŭ �ݺ��ϸ� �� �Ѿ˵��� ��ġ�� üũ
	for (int i = 0; i < m_iCurBulletCount; i++) {
		// �Ѿ��� ��ġ�� ���ڷ� ���� ��ġ�� ���ٸ� �Ѿ��̹Ƿ� true �� ����
		if (m_pBullet[i]->GetPos().x == x && m_pBullet[i]->GetPos().y == y) {
			return true;
		}
	}
	return false;
}