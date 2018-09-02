#include "Core.h"

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