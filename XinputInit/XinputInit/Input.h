#pragma once

#ifndef _MY_INPUT_H

#include <Windows.h>
#include <Xinput.h>
#include <math.h>

#pragma comment(lib, "xinput.lib")

#endif // !_MY_INPUT_H

namespace XINPUT_PAD
{
	// �ԍ�
	const unsigned __int8 PAD_NUM01 = 0;
	const unsigned __int8 PAD_NUM02 = 1;
	const unsigned __int8 PAD_NUM03 = 2;
	const unsigned __int8 PAD_NUM04 = 3;

	// �{�^��
	const unsigned __int8 CROSS_BUTTON_UP		 = 0;
	const unsigned __int8 CROSS_BUTTON_DOWN		 = 1;
	const unsigned __int8 CROSS_BUTTON_LEFT		 = 2;
	const unsigned __int8 CROSS_BUTTON_RIGHT	 = 3;
	const unsigned __int8 BUTTON_START			 = 4;
	const unsigned __int8 BUTTON_BACK			 = 5;
	const unsigned __int8 STICK_PUSH_LEFT		 = 6;
	const unsigned __int8 STICK_PUSH_RIGHT		 = 7;
	const unsigned __int8 SHOULDER_LEFT			 = 8;
	const unsigned __int8 SHOULDER_RIGHT		 = 9;
	const unsigned __int8 BUTTON_A				 = 12;
	const unsigned __int8 BUTTON_B				 = 13;
	const unsigned __int8 BUTTON_X				 = 14;
	const unsigned __int8 BUTTON_Y				 = 15;

	// �g���K
	const bool TRIGGER_RIGHT = 0;
	const bool TRIGGER_LEFT	 = 1;

	// �X�e�B�b�N
	const unsigned __int8 STICK_RIGHT_AXIS_X	 = 0;
	const unsigned __int8 STICK_RIGHT_AXIS_Y	 = 1;
	const unsigned __int8 STICK_LEFT_AXIS_X		 = 2;
	const unsigned __int8 STICK_LEFT_AXIS_Y		 = 3;
}

class Input
{
private:
	static unsigned __int8 controllerNum;		// �ڑ����Ă���ő�̌�

	static int button[4][16];					// wButton�̑Ή�
	static int stick[4][4];						// stick�̑Ή�(��������thumb)

	static XINPUT_STATE state[4];				// xinput�̒��g

public:
	Input();		// �R���X�g���N�^
	~Input();		// �f�X�g���N�^

	static void Update();		// ����X�V

	static int GetPadNum();																// �R���g���[���̐�
	static int GetPadButtonData(unsigned __int8 use_padnum, unsigned __int8 use_input);			// �R���g���[���̃{�^������
	static int GetPadTriggerData(unsigned __int8 use_padnum, bool use_Is_triggerLeft);				// �R���g���[���̃g���K�[����
	static int GetPadThumbData(unsigned __int8 use_padnum, unsigned __int8 use_stick);			// �R���g���[���̃X�e�B�b�N����
};
