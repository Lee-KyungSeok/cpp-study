
#include "Core.h"

/*
 - 50 x 10 맵을 생성
 - Stage 클래스 init 함수에서 맵을 만들고
 - Stage 클래스에 Render 함수를 만들어 이 맵을 출력
 - 그 후 Map Manager 클래스의 Run 함수에서 해당 스테이지 출력 (Render 함수 호출)
*/

int main()
{
    // 게임을 초기
    if (!CCore::GetInst()->Init())
    {
        cout << "게임 초기화 실패!!" << endl;
        CCore::DestroyInst();

        return 0;
    }

    // ÃÊ±âÈ­¿¡ ¼º°øÇß´Ù¸é °ÔÀÓÀ» ±¸µ¿½ÃÅ²´Ù.
    CCore::GetInst()->Run();

    // µ¿ÀÛÀÌ ³¡³ª¸é CCore °´Ã¼¸¦ ¸Þ¸ð¸®¿¡¼­ ÇØÁ¦½ÃÅ²´Ù.
    CCore::DestroyInst();

    return 0;
}
