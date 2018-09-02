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
		// true: 0이 아니므로 총알이 더 나갈 수 있는 상태
		// false: 총알이 나갈 수 있는 사정거리까지 모두 나간 상태로 총알을 삭제함
		return m_iDist != 0;
	}

public:
	bool Init();
	void Update();

};

