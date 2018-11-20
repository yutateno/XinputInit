#pragma once

#ifdef DLLXINPUT_EXPORTS
#define DLLXINPUT_API __declspec(dllexport)
#else
#define DLLXINPUT_API __declspec(dllimport)
#endif

namespace DLLXinput
{
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

		const int MAX_STICK_PLUS = 32767;
		const int MAX_STICK_MINUS = -32768;


		// �o�C�u���[�V����
		const unsigned __int16 VIB_MAX = 65535;
	}

	struct STICK_DEADZONE
	{
		// ���X�e�B�b�N�̍��E
		short LEFT_RIGHT = 7849;
		short LEFT_LEFT = -7849;

		// ���X�e�B�b�N�̏㉺
		short LEFT_UP = 7849;
		short LEFT_DOWN = -7849;

		// �E�X�e�B�b�N�̍��E
		short RIGHT_RIGHT = 8689;
		short RIGHT_LEFT = -8689;

		// �E�X�e�B�b�N�̏㉺
		short RIGHT_UP = 8689;
		short RIGHT_DOWN = -8689;
	};

		DLLXINPUT_API void Init();
		DLLXINPUT_API void Clean();

		DLLXINPUT_API void FirstUpdate();		// �Q�[���J�n�O����X�V
		DLLXINPUT_API void EverUpdate();			// �Q�[���J�n�㑀��X�V

		DLLXINPUT_API void Vibration(unsigned __int8 use_padnum, int time = 0
			, unsigned __int16 rightVib = XINPUT_PAD::VIB_MAX, unsigned __int16 leftVib = XINPUT_PAD::VIB_MAX);		// �o�C�u���[�V�������s��

		DLLXINPUT_API void VibrationSlowlyStop();

		DLLXINPUT_API void VibrationStop(unsigned __int8 use_padnum);						// �o�[�u���[�V�������~�߂�

		DLLXINPUT_API void SetPlayerPadNum(unsigned __int8 playerPadNum);					// �v���C���[�̔ԍ���ݒ�

		DLLXINPUT_API void SetPadDeadZone(short leftPad_right = 7849, short leftPad_left = -7849
			, short leftPad_up = 7849, short leftPad_down = -7849
			, short rightPad_right = 8689, short rightPad_left = -8689
			, short rightPad_up = 8689, short rightPad_down = -8689);		// �f�b�h�]�[���̐ݒ�l�ύX  // (������x�y�������̂ňꉞ�f�t�H���g�������p)

		DLLXINPUT_API const short GetPadThumbMax(const bool stickLightNow, const bool stickXAxisNow, const bool stickPlusNow);

		DLLXINPUT_API int GetPadNum();																// �R���g���[���̐�
		DLLXINPUT_API unsigned __int8 GetPlayerPadNumber();																// �R���g���[���̐�
		DLLXINPUT_API int GetPadButtonData(unsigned __int8 use_padnum, unsigned __int8 use_button);			// �R���g���[���̃{�^������
		DLLXINPUT_API int GetPadTriggerData(unsigned __int8 use_padnum, bool use_Is_triggerLeft);				// �R���g���[���̃g���K�[����
		DLLXINPUT_API int GetPadThumbData(unsigned __int8 use_padnum, unsigned __int8 use_stick);			// �R���g���[���̃X�e�B�b�N����
}