
#pragma once

#include "value.h"

enum JUMP_DIR {
    JD_STOP,
    JD_UP,
    JD_DOWN
};

#define JUMP_BLOCK_MAX 3

class CPlayer {

public:
    CPlayer();
    ~CPlayer();

private:
//    int m_iX;
//    int m_iY;
    POINT m_tPos;
    bool m_bJump;
    int m_iJumpDir;
    int m_iJumpState;
    int m_iScore;
    bool m_bComplete;

public:
    void setPos(int x, int y) {
        this->m_tPos.x = x;
        this->m_tPos.y = y;
    }
public:
    int GetX() {
        return m_tPos.x;
    }
    int GetY() {
        return m_tPos.y;
    }

    int GetScore() {
        return m_iScore;
    }

    bool GetComplete() {
        return m_bComplete;
    }

public:
    bool Init();

public:
    void Update();
};
