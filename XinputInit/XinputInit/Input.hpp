#pragma once
#ifndef _MY_INPUTPAD_H
#define _MY_INPUTPAD_H

#include <Windows.h>
#include <math.h>

#include <Xinput.h>

#pragma comment(lib, "xinput.lib")

namespace XINPUT_PAD
{
	// �ԍ�
	const unsigned __int8 NUM01 = 0;
	const unsigned __int8 NUM02 = 1;
	const unsigned __int8 NUM03 = 2;
	const unsigned __int8 NUM04 = 3;


	// �{�^��
	const unsigned __int8 BUTTON_UP = 0;
	const unsigned __int8 BUTTON_DOWN = 1;
	const unsigned __int8 BUTTON_LEFT = 2;
	const unsigned __int8 BUTTON_RIGHT = 3;

	const unsigned __int8 BUTTON_START = 4;
	const unsigned __int8 BUTTON_BACK = 5;

	const unsigned __int8 BUTTON_STICK_LEFT = 6;
	const unsigned __int8 BUTTON_STICK_RIGHT = 7;

	const unsigned __int8 BUTTON_A = 12;
	const unsigned __int8 BUTTON_B = 13;
	const unsigned __int8 BUTTON_X = 14;
	const unsigned __int8 BUTTON_Y = 15;


	// �g���K
	const bool TRIGGER_RT = 0;
	const bool TRIGGER_LT = 1;

	const unsigned __int8 SHOULDER_LB = 8;
	const unsigned __int8 SHOULDER_RB = 9;


	// �X�e�B�b�N
	const unsigned __int8 STICK_RIGHT_X = 0;
	const unsigned __int8 STICK_RIGHT_Y = 1;
	const unsigned __int8 STICK_LEFT_X = 2;
	const unsigned __int8 STICK_LEFT_Y = 3;


	// �o�C�u���[�V����
	const unsigned __int16 VIB_MAX = 65535;
}

struct STICK_DEADZONE
{
	// ���X�e�B�b�N�̍��E
	short LEFT_RIGHT = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
	short LEFT_LEFT = -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

	// ���X�e�B�b�N�̏㉺
	short LEFT_UP = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
	short LEFT_DOWN = -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

	// �E�X�e�B�b�N�̍��E
	short RIGHT_RIGHT = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
	short RIGHT_LEFT = -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;

	// �E�X�e�B�b�N�̏㉺
	short RIGHT_UP = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
	short RIGHT_DOWN = -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
};

class InputPad
{
private:
	static unsigned __int8 controllerNum;		// �ڑ����Ă���ő�̌�
	static bool setControll[4];

	static unsigned __int8 playerPadNum;		// �v���C���[���g���R���g���[���[

	static int button[4][16];					// wButton�̑Ή�
	static int stick[4][4];						// stick�̑Ή�(��������thumb)

	static XINPUT_STATE state[4];				// xinput�̒��g

	static STICK_DEADZONE stickDeadZone;		// �X�e�B�b�N�̃f�b�h�]�[���l

	static XINPUT_VIBRATION vibration;			// �o�C�u���[�V�����̍\����

public:
	InputPad();		// �R���X�g���N�^
	~InputPad();		// �f�X�g���N�^

	static void FirstUpdate();		// �Q�[���J�n�O����X�V
	static void EverUpdate();			// �Q�[���J�n�㑀��X�V

	static void Vibration(unsigned __int8 use_padnum, int time = 0
		, unsigned __int16 rightVib = XINPUT_PAD::VIB_MAX, unsigned __int16 leftVib = XINPUT_PAD::VIB_MAX);		// �o�C�u���[�V�������s��

	static void VibrationStop(unsigned __int8 use_padnum);						// �o�[�u���[�V�������~�߂�

	static void SetPlayerPadNum(unsigned __int8 playerPadNum);					// �v���C���[�̔ԍ���ݒ�

	static void SetPadDeadZone(short leftPad_right = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, short leftPad_left = -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
		, short leftPad_up = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, short leftPad_down = -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
		, short rightPad_right = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE, short rightPad_left = -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE
		, short rightPad_up = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE, short rightPad_down = -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);		// �f�b�h�]�[���̐ݒ�l�ύX  // (������x�y�������̂ňꉞ�f�t�H���g�������p)

	static int GetPadNum();																// �R���g���[���̐�
	static int GetPadButtonData(unsigned __int8 use_padnum, unsigned __int8 use_button);			// �R���g���[���̃{�^������
	static int GetPadTriggerData(unsigned __int8 use_padnum, bool use_Is_triggerLeft);				// �R���g���[���̃g���K�[����
	static int GetPadThumbData(unsigned __int8 use_padnum, unsigned __int8 use_stick);			// �R���g���[���̃X�e�B�b�N����
};

#endif // !_MY_INPUTPAD_H