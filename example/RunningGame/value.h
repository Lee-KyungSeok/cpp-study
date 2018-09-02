#pragma once

#include <iostream>
#include <time.h>
// windows.h 헤더에는 윈도우의 기능을 사용할 수 잇는 여러 함수들을 제공해주고 있다.
// 여기서 키 입력 기능을 활용할 수 있다.
#include <Windows.h>

using namespace std;

// 매크로는 #define을 이용해서 기능을 만들어 주는 것.
// 이 매크로를 사용하게 되면 사용한 부분에 컴파일 단계에서 뒤의 코드를 복사해주는 개념
// 매크로의 단점: break point 를 걸고 값을 체크할 수 없다.
#define	SAFE_DELETE(p)	if(p)	{ delete p; p = NULL; }

// Stage Max Count
#define	STAGE_MAX_COUNT	3

// Block Count
#define BLOCK_X 50
#define BLOCK_Y 10

// Render Block Count
#define RENDER_BLOCK_X 10
#define RENDER_BLOCK_Y 4

// Bullet Count Max
#define BULLET_COUNT_MAX 10

static int InputInt() {
	int iInput;
	cin >> iInput;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(1024, '\n');
		return INT_MAX;
	}
	return iInput;
}