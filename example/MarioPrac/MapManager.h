#pragma once

#include "value.h"

// Å¬·¡½º Àü¹æ¼±¾ð : ÀÌ°÷¿¡¼­ Àü¹æ¼±¾ðÇÑ Å¬·¡½º°¡ ÀÖ´Ù ¶ó°í ÀÎ½ÄÇÏ°Ô ¸¸µç´Ù.
// Àü¹æ¼±¾ð ÇÑ ºÎºÐ¿¡¼­´Â °¡Á¤¸¸ ÇÏ´Â °ÍÀÌ±â ¶§¹®¿¡ Àü¹æ¼±¾ðÇÑ Å¬·¡½ºÀÇ °´Ã¼
// ¸¦ »ý¼ºÇÏ´ø°¡ ±â´ÉÀ» ²ø¾î´Ù »ç¿ëÇÒ ¼ö ¾ø´Ù.
// ´Ü¼øÈ÷ Æ÷ÀÎÅÍ º¯¼ö¸¦ ¼±¾ðÇÒ ¸ñÀûÀ¸·Î ÁÖ·Î »ç¿ëÇÏ°í Àü¹æ¼±¾ðÀ» »ç¿ëÇÔÀ¸·Î
// ½á Çì´õ¿¡¼­ Çì´õ¸¦ #include ÇÏ´Â »óÈ²À» ¸·¾ÆÁÖ°í cpp¿¡¼­ ½ÇÁ¦ »ç¿ëÇÒ
// ¶§ include¸¦ ÇØÁÖ¾î¼­ Çì´õ°£¿¡ ¼­·Î includeÇÏ´Â »óÈ²À» ¸·¾ÆÁÙ ¼ö ÀÖ´Ù.
class CStage;
class CMapManager
{
private:
    CMapManager();
    ~CMapManager();

private:
    static CMapManager*	m_pInst;

public:
    static CMapManager* GetInst();
    static void DestroyInst();

private:
    CStage* m_pStage[STAGE_MAX_COUNT];
    int m_iEnableState;

public:
    CStage* GetStage() {
        return m_pStage[m_iEnableState];
    }

public:
    bool Init();
    void Run(int iStage);
    void Render();
};

