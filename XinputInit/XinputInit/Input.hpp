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

struct XINPUT_STICK_MY_DEADZONE
{
	// ���X�e�B�b�N�̍��E
	short LEFT_AXIS_X_RIGHT = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
	short LEFT_AXIS_X_LEFT = -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

	// ���X�e�B�b�N�̏㉺
	short LEFT_AXIS_Y_UP = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
	short LEFT_AXIS_Y_DOWN = -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

	// �E�X�e�B�b�N�̍��E
	short RIGHT_AXIS_X_RIGHT = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
	short RIGHT_AXIS_X_LEFT = -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;

	// �E�X�e�B�b�N�̏㉺
	short RIGHT_AXIS_Y_UP = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
	short RIGHT_AXIS_Y_DOWN = -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
};

class Input
{
private:
	static unsigned __int8 controllerNum;		// �ڑ����Ă���ő�̌�

	static int button[4][16];					// wButton�̑Ή�
	static int stick[4][4];						// stick�̑Ή�(��������thumb)

	static XINPUT_STATE state[4];				// xinput�̒��g

	static XINPUT_STICK_MY_DEADZONE stickDeadZone;			// �X�e�B�b�N�̃f�b�h�]�[���l
	
public:
	Input();		// �R���X�g���N�^
	~Input();		// �f�X�g���N�^

	static void Update();		// ����X�V

	

	static int GetPadNum();																// �R���g���[���̐�
	static int GetPadButtonData(unsigned __int8 use_padnum, unsigned __int8 use_button);			// �R���g���[���̃{�^������
	static int GetPadTriggerData(unsigned __int8 use_padnum, bool use_Is_triggerLeft);				// �R���g���[���̃g���K�[����
	static int GetPadThumbData(unsigned __int8 use_padnum, unsigned __int8 use_stick);			// �R���g���[���̃X�e�B�b�N����
	static void SetPadDeadZone(short leftPad_right = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, short leftPad_left = -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
		, short leftPad_up = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, short leftPad_down = -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
		, short rightPad_right = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE, short rightPad_left = -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE
		, short rightPad_up = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE, short rightPad_down = -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);		// �f�b�h�]�[���̐ݒ�l�ύX  // (������x�y�������̂ňꉞ�f�t�H���g�������p)
};
