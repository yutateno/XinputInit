#include "Input.hpp"

// static�ϐ��̐錾
unsigned __int8 Input::controllerNum;
int Input::button[4][16];
int Input::stick[4][4];
XINPUT_STATE Input::state[4];
XINPUT_STICK_MY_DEADZONE Input::stickDeadZone;

Input::Input()
{
	// �R���g���[�������[�v
	controllerNum = 4;
	for (int i = 0; i != controllerNum; ++i)
	{
		ZeroMemory(&Input::state[i], sizeof(XINPUT_STATE));
		// �{�^����0�ɏ�����(�X�e�B�b�N�̓f�b�h�]�[���̊֌W�ōs��Ȃ�)
		for (int j = 0; j != 16; ++j)
		{
			Input::button[i][j] = 0;
		}
	}
}

Input::~Input()
{
	for (int i = 0; i != controllerNum; ++i)
	{
		ZeroMemory(&Input::state[i], sizeof(XINPUT_STATE));
	}
}

void Input::Update()
{
	// �R���g���[���̐������s��
	for (int i = 0; i < controllerNum; i++)
	{
		ZeroMemory(&Input::state[i], sizeof(XINPUT_STATE));
		if (XInputGetState(i, &Input::state[i]) == ERROR_SUCCESS)		// �ڑ�����Ă���
		{
			// �{�^������
			for (int j = 0; j != 16; ++j)
			{
				if (j == 10 || j == 11)		// xinput.h��Ŋ��蓖�Ă��Ă��Ȃ�
				{
					continue;
				}
				if ((Input::state[i].Gamepad.wButtons & (int)pow(2.0, (double)j)) != 0)		// �{�^������������
				{
					Input::button[i][j]++;
					if (Input::button[i][j] >= 1000)		// ��������l�s���Ǝv���̂ŉ��
					{
						Input::button[i][j] = 2;
					}
				}
				else if (Input::button[i][j] > 0)	// �����Ă����{�^���𗣂�����
				{
					Input::button[i][j] = -1;
				}
				else		// �{�^���ɐG��Ă��Ȃ�
				{
					Input::button[i][j] = 0;
				}
			}

			// �X�e�B�b�N����
			// ���X�e�B�b�N�̍��E(�����̃f�b�h�]�[�����g�킹�Ă��炤�����삷��������쐫��낵���Ȃ�Ǝv����)
			if (Input::state[i].Gamepad.sThumbLX > stickDeadZone.LEFT_AXIS_X_RIGHT
				|| Input::state[i].Gamepad.sThumbLX < stickDeadZone.LEFT_AXIS_X_LEFT)		// �X�e�B�b�N�𑀍삵����
			{
				Input::stick[i][XINPUT_PAD::STICK_LEFT_AXIS_X] = Input::state[i].Gamepad.sThumbLX;
			}
			else		// �X�e�B�b�N�𑀍삵�Ă��Ȃ�
			{
				Input::stick[i][XINPUT_PAD::STICK_LEFT_AXIS_X] = 0;
			}
			// ���X�e�B�b�N�̏㉺
			if (Input::state[i].Gamepad.sThumbLY > stickDeadZone.LEFT_AXIS_Y_UP
				|| Input::state[i].Gamepad.sThumbLY < stickDeadZone.LEFT_AXIS_Y_DOWN)		// �X�e�B�b�N�𑀍삵����
			{
				Input::stick[i][XINPUT_PAD::STICK_LEFT_AXIS_Y] = Input::state[i].Gamepad.sThumbLY;
			}
			else		// �X�e�B�b�N�𑀍삵�Ă��Ȃ�
			{
				Input::stick[i][XINPUT_PAD::STICK_LEFT_AXIS_Y] = 0;
			}
			// �E�X�e�B�b�N�̍��E
			if (Input::state[i].Gamepad.sThumbRX > stickDeadZone.RIGHT_AXIS_X_RIGHT
				|| Input::state[i].Gamepad.sThumbRX < stickDeadZone.RIGHT_AXIS_X_LEFT)		// �X�e�B�b�N�𑀍삵����
			{
				Input::stick[i][XINPUT_PAD::STICK_RIGHT_AXIS_X] = Input::state[i].Gamepad.sThumbRX;
			}
			else		// �X�e�B�b�N�𑀍삵�Ă��Ȃ�
			{
				Input::stick[i][XINPUT_PAD::STICK_RIGHT_AXIS_X] = 0;
			}
			// �E�X�e�B�b�N�̏㉺
			if (Input::state[i].Gamepad.sThumbRY > stickDeadZone.RIGHT_AXIS_Y_UP
				|| Input::state[i].Gamepad.sThumbRY < stickDeadZone.RIGHT_AXIS_Y_DOWN)		// �X�e�B�b�N�𑀍삵����
			{
				Input::stick[i][XINPUT_PAD::STICK_RIGHT_AXIS_Y] = Input::state[i].Gamepad.sThumbRY;
			}
			else		// �X�e�B�b�N�𑀍삵�Ă��Ȃ�
			{
				Input::stick[i][XINPUT_PAD::STICK_RIGHT_AXIS_Y] = 0;
			}
		}
		else	// �ڑ�����Ă��Ȃ�
		{
			ZeroMemory(&Input::state[i], sizeof(XINPUT_STATE));
			Input::controllerNum = i;		// ���̎��_�ŃR���g���[���̍ő�������߂�
		}
	}
}

int Input::GetPadNum()
{
	return (int)Input::controllerNum;
}

int Input::GetPadButtonData(unsigned __int8 use_padnum, unsigned __int8 use_button)
{
	return Input::button[use_padnum][use_button];
}

int Input::GetPadTriggerData(unsigned __int8 use_padnum, bool use_Is_triggerLeft)
{
	if (use_Is_triggerLeft)
	{
		return Input::state[use_padnum].Gamepad.bLeftTrigger;
	}
	else
	{
		return Input::state[use_padnum].Gamepad.bRightTrigger;
	}
}

int Input::GetPadThumbData(unsigned __int8 use_padnum, unsigned __int8 use_stick)
{
	return Input::stick[use_padnum][use_stick];
}

void Input::SetPadDeadZone(short leftPad_right, short leftPad_left
	, short leftPad_up, short leftPad_down, short rightPad_right, short rightPad_left, short rightPad_up, short rightPad_down)
{
	Input::stickDeadZone.LEFT_AXIS_X_RIGHT	 = (leftPad_right	 ==  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)  ?  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  : leftPad_right;
	Input::stickDeadZone.LEFT_AXIS_X_LEFT	 = (leftPad_left	 == -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)  ? -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  : leftPad_left;
	Input::stickDeadZone.LEFT_AXIS_Y_UP		 = (leftPad_up		 ==  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)  ?  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  : leftPad_up;
	Input::stickDeadZone.LEFT_AXIS_Y_DOWN	 = (leftPad_down	 == -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)  ? -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  : leftPad_down;
	Input::stickDeadZone.RIGHT_AXIS_X_RIGHT	 = (rightPad_right	 ==  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) ?  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE : rightPad_right;
	Input::stickDeadZone.RIGHT_AXIS_X_LEFT	 = (rightPad_left	 == -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) ? -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE : rightPad_left;
	Input::stickDeadZone.RIGHT_AXIS_Y_UP	 = (rightPad_up		 ==  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) ?  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE : rightPad_up;
	Input::stickDeadZone.RIGHT_AXIS_Y_DOWN	 = (rightPad_down	 == -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) ? -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE : rightPad_down;
}
