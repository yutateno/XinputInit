#include "Input.h"

int Input::button[4][16];
unsigned __int8 Input::controllerNum;
XINPUT_STATE Input::state[4];

Input::Input()
{
	for (int i = 0; i != 4; ++i)
	{
		ZeroMemory(&state[i], sizeof(XINPUT_STATE));
	}
	controllerNum = 4;
}

Input::~Input()
{
	for (int i = 0; i != 4; ++i)
	{
		ZeroMemory(&state[i], sizeof(XINPUT_STATE));
	}
}

void Input::Update()
{
	for (int i = 0; i < controllerNum; i++)
	{
		ZeroMemory(&state[i], sizeof(XINPUT_STATE));
		if (XInputGetState(i, &state[i]) == ERROR_SUCCESS)
		{
			// ボタン操作
			for (int j = 0; j != 16; ++j)
			{
				if (j == 10 || j == 11)		// 割り当てられていない
				{
					continue;
				}
				if ((state[i].Gamepad.wButtons & (int)pow(2.0, (double)j)) != 0)
				{
					button[i][j]++;
					if (button[i][j] >= 50)		// いつか上限値行くと思うので回避
					{
						button[i][j] = 2;
					}
				}
				else if (button[i][j] > 0)
				{
					button[i][j] = -1;
				}
				else
				{
					button[i][j] = 0;
				}
			}
		}
		else
		{
			ZeroMemory(&state[i], sizeof(XINPUT_STATE));
			controllerNum = i;
		}
	}
}

int Input::GetPadNum()
{
	return (int)controllerNum;
}

int Input::GetPadButtonDate(int padnum, int input)
{
	return button[padnum][input];
}
