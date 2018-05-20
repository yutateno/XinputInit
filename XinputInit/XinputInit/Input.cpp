#include "Input.h"

unsigned __int8 Input::controllerNum;
int Input::button[4][16];
int Input::thumb[4][4];
XINPUT_STATE Input::state[4];

Input::Input()
{
	for (int i = 0; i != 4; ++i)
	{
		ZeroMemory(&Input::state[i], sizeof(XINPUT_STATE));
	}
	controllerNum = 4;
	for (int i = 0; i != 4; ++i)
	{
		for (int j = 0; j != 16; ++j)
		{
			Input::button[i][j] = 0;
		}
	}
}

Input::~Input()
{
	for (int i = 0; i != 4; ++i)
	{
		ZeroMemory(&Input::state[i], sizeof(XINPUT_STATE));
	}
}

void Input::Update()
{
	for (int i = 0; i < controllerNum; i++)
	{
		ZeroMemory(&Input::state[i], sizeof(XINPUT_STATE));
		if (XInputGetState(i, &Input::state[i]) == ERROR_SUCCESS)		// �ڑ�����Ă���
		{
			// �{�^������
			for (int j = 0; j != 16; ++j)
			{
				if (j == 10 || j == 11)		// ���蓖�Ă��Ă��Ȃ�
				{
					continue;
				}
				if ((Input::state[i].Gamepad.wButtons & (int)pow(2.0, (double)j)) != 0)
				{
					Input::button[i][j]++;
					if (Input::button[i][j] >= 50)		// ��������l�s���Ǝv���̂ŉ��
					{
						Input::button[i][j] = 2;
					}
				}
				else if (Input::button[i][j] > 0)
				{
					Input::button[i][j] = -1;
				}
				else
				{
					Input::button[i][j] = 0;
				}
			}

			// �X�e�B�b�N����
			// ���X�e�B�b�N�̍��E
			if (Input::state[i].Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
				|| Input::state[i].Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			{
				Input::thumb[i][XINPUT_PAD::XINPUT_THUMB_LEFT_AXIS_X] = Input::state[i].Gamepad.sThumbLX;
			}
			else
			{
				Input::thumb[i][XINPUT_PAD::XINPUT_THUMB_LEFT_AXIS_X] = 0;
			}
			// ���X�e�B�b�N�̏㉺
			if (Input::state[i].Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
				|| Input::state[i].Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			{
				Input::thumb[i][XINPUT_PAD::XINPUT_THUMB_LEFT_AXIS_Y] = Input::state[i].Gamepad.sThumbLY;
			}
			else
			{
				Input::thumb[i][XINPUT_PAD::XINPUT_THUMB_LEFT_AXIS_Y] = 0;
			}
			// �E�X�e�B�b�N�̍��E
			if (Input::state[i].Gamepad.sThumbRX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE
				|| Input::state[i].Gamepad.sThumbRX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
			{
				Input::thumb[i][XINPUT_PAD::XINPUT_THUMB_RIGHT_AXIS_X] = Input::state[i].Gamepad.sThumbRX;
			}
			else
			{
				Input::thumb[i][XINPUT_PAD::XINPUT_THUMB_RIGHT_AXIS_X] = 0;
			}
			// �E�X�e�B�b�N�̏㉺
			if (Input::state[i].Gamepad.sThumbRY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE
				|| Input::state[i].Gamepad.sThumbRY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
			{
				Input::thumb[i][XINPUT_PAD::XINPUT_THUMB_RIGHT_AXIS_Y] = Input::state[i].Gamepad.sThumbRY;
			}
			else
			{
				Input::thumb[i][XINPUT_PAD::XINPUT_THUMB_RIGHT_AXIS_Y] = 0;
			}
		}
		else	// �ڑ�����Ă��Ȃ�
		{
			ZeroMemory(&Input::state[i], sizeof(XINPUT_STATE));
			Input::controllerNum = i;
		}
	}
}

int Input::GetPadNum()
{
	return (int)Input::controllerNum;
}

int Input::GetPadButtonData(unsigned __int8 padnum, unsigned __int8 input)
{
	return Input::button[padnum][input];
}

int Input::GetPadTriggerData(unsigned __int8 padnum, bool triggerLeft)
{
	return (triggerLeft)? Input::state[padnum].Gamepad.bLeftTrigger : Input::state[padnum].Gamepad.bRightTrigger;
}

int Input::GetPadThumbData(unsigned __int8 padnum, unsigned __int8 thumb)
{
	return Input::thumb[padnum][thumb];
}
