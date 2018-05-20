#pragma once

#ifndef _MY_INPUT_H

#include <Windows.h>
#include <Xinput.h>
#include <math.h>

#pragma comment(lib, "xinput.lib")

#endif // !_MY_INPUT_H

namespace XINPUT_PAD
{
	const int PAD_NUM01 = 0;
	const int PAD_NUM02 = 1;
	const int PAD_NUM03 = 2;
	const int PAD_NUM04 = 3;

	const int XINPUT_DPAD_UP = 0;
	const int XINPUT_DPAD_DOWN = 1;
	const int XINPUT_DPAD_LEFT = 2;
	const int XINPUT_DPAD_RIGHT = 3;
	const int XINPUT_START = 4;
	const int XINPUT_BACK = 5;
	const int XINPUT_LEFT_THUMB = 6;
	const int XINPUT_RIGHT_THUMB = 7;
	const int XINPUT_LEFT_SHOULDER = 8;
	const int XINPUT_RIGHT_SHOULDER = 9;
	const int XINPUT_A = 12;
	const int XINPUT_B = 13;
	const int XINPUT_X = 14;
	const int XINPUT_Y = 15;
}

class Input
{
private:
	static unsigned __int8 controllerNum;					// �ڑ����Ă���ő�̌�

	static int button[4][16];					// wButton�̑Ή�

	static XINPUT_STATE state[4];				// xinput�̒��g

public:
	Input();		// �R���X�g���N�^
	~Input();		// �f�X�g���N�^

	static void Update();		// ����X�V

	static int GetPadNum();								// �R���g���[���[�̐�
	static int GetPadButtonDate(int padnum, int input);	// �R���g���[���[�̃{�^������
};
