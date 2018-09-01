#pragma once

#include "value.h"

// Çì´õÆÄÀÏ¿¡´Â Å¬·¡½ºÀÇ ¼±¾ðºÎºÐÀÌ µé¾î¿Â´Ù.
class CCore
{
private:
    CCore();
    ~CCore();

private:
    static CCore*	m_pInst;

public:
    static CCore* GetInst();
    static void DestroyInst();

public:
    // 전체 게임을 초기화
    bool Init();

    // 게임을 동작
    void Run();

private:
    int OutputMenu();
};

