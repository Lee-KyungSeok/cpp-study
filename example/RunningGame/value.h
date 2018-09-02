#pragma once

#include <iostream>
#include <time.h>
// windows.h ������� �������� ����� ����� �� �մ� ���� �Լ����� �������ְ� �ִ�.
// ���⼭ Ű �Է� ����� Ȱ���� �� �ִ�.
#include <Windows.h>

using namespace std;

// ��ũ�δ� #define�� �̿��ؼ� ����� ����� �ִ� ��.
// �� ��ũ�θ� ����ϰ� �Ǹ� ����� �κп� ������ �ܰ迡�� ���� �ڵ带 �������ִ� ����
// ��ũ���� ����: break point �� �ɰ� ���� üũ�� �� ����.
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