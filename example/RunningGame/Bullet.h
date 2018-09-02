#pragma once

#include "value.h"

class CBullet
{
public:
	CBullet();
	~CBullet();

private:
	POINT m_tPos;
	int m_iDist;

public:
	void SetPos(int x, int y) {
		m_tPos.x = x;
		m_tPos.y = y;
	}

public:
	POINT GetPos() {
		return m_tPos;
	}

	bool GetEnable() {
		// true: 0�� �ƴϹǷ� �Ѿ��� �� ���� �� �ִ� ����
		// false: �Ѿ��� ���� �� �ִ� �����Ÿ����� ��� ���� ���·� �Ѿ��� ������
		return m_iDist != 0;
	}

public:
	bool Init();
	void Update();

};

