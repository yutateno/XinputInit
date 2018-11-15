// DLLXinput.cpp : DLL アプリケーション用にエクスポートされる関数を定義します。
//

#include "stdafx.h"
#include "DLLXinput.h"

#include <Windows.h>
#include <math.h>

#include <Xinput.h>

#pragma comment(lib, "xinput.lib")

namespace DLLXinput
{
	static XINPUT_STATE state[4];
	static XINPUT_VIBRATION vibration;

	static unsigned __int8 playerPadNum = 0;		// プレイヤーが使うコントローラー

	// コンストラクタ
	InputPad::InputPad()
	{
		// コントローラ分ループ
		InputPad::controllerNum = 0;
		for (int i = 0; i != 4; ++i)
		{
			if (XInputGetState(i, &state[i]) == ERROR_SUCCESS)
			{
				InputPad::controllerNum++;
				InputPad::setControll[i] = true;
			}
			else
			{
				InputPad::setControll[i] = false;
			}
		}
		ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
		ZeroMemory(&state, sizeof(XINPUT_STATE));
		for (int i = 0; i != InputPad::controllerNum; ++i)
		{
			// ボタンを0に初期化(スティックはデッドゾーンの関係で行わない)
			for (int j = 0; j != 16; ++j)
			{
				InputPad::button[i][j] = 0;
			}
		}
	}

	// デストラクタ
	InputPad::~InputPad()
	{
		ZeroMemory(&state, sizeof(XINPUT_STATE));
	}


	// 更新
	void InputPad::FirstUpdate()
	{
		// コントローラの数だけ行う
		for (int i = 0; i != InputPad::controllerNum; ++i)
		{
			if (InputPad::setControll[i])		// 接続されているコントローラーのみ判断するように
			{
				ZeroMemory(&state[i], sizeof(XINPUT_STATE));
				XInputGetState(i, &state[i]);
				// ボタン操作
				for (int j = 0; j != 16; ++j)
				{
					if (j == 10 || j == 11)		// xinput.h上で割り当てられていない
					{
						continue;
					}
					if ((state[i].Gamepad.wButtons & (int)pow(2.0, (double)j)) != 0)		// ボタンを押したら
					{
						InputPad::button[i][j]++;
						if (InputPad::button[i][j] >= 1000)		// いつか上限値行くと思うので回避
						{
							InputPad::button[i][j] = 2;
						}
					}
					else if (InputPad::button[i][j] > 0)	// 押していたボタンを離したら
					{
						InputPad::button[i][j] = -1;
					}
					else		// ボタンに触れていない
					{
						InputPad::button[i][j] = 0;
					}
				}

				// スティック操作
				// 左スティックの左右(公式のデッドゾーンを使わせてもらうが自作する方が操作性よろしくなると思われる)
				if (state[i].Gamepad.sThumbLX > stickDeadZone.LEFT_RIGHT
					|| state[i].Gamepad.sThumbLX < stickDeadZone.LEFT_LEFT)		// スティックを操作したら
				{
					InputPad::stick[i][XINPUT_PAD::STICK_LEFT_X] = state[i].Gamepad.sThumbLX;
				}
				else		// スティックを操作していない
				{
					InputPad::stick[i][XINPUT_PAD::STICK_LEFT_X] = 0;
				}
				// 左スティックの上下
				if (state[i].Gamepad.sThumbLY > stickDeadZone.LEFT_UP
					|| state[i].Gamepad.sThumbLY < stickDeadZone.LEFT_DOWN)		// スティックを操作したら
				{
					InputPad::stick[i][XINPUT_PAD::STICK_LEFT_Y] = state[i].Gamepad.sThumbLY;
				}
				else		// スティックを操作していない
				{
					InputPad::stick[i][XINPUT_PAD::STICK_LEFT_Y] = 0;
				}
				// 右スティックの左右
				if (state[i].Gamepad.sThumbRX > stickDeadZone.RIGHT_RIGHT
					|| state[i].Gamepad.sThumbRX < stickDeadZone.RIGHT_LEFT)		// スティックを操作したら
				{
					InputPad::stick[i][XINPUT_PAD::STICK_RIGHT_X] = state[i].Gamepad.sThumbRX;
				}
				else		// スティックを操作していない
				{
					InputPad::stick[i][XINPUT_PAD::STICK_RIGHT_X] = 0;
				}
				// 右スティックの上下
				if (state[i].Gamepad.sThumbRY > stickDeadZone.RIGHT_UP
					|| state[i].Gamepad.sThumbRY < stickDeadZone.RIGHT_DOWN)		// スティックを操作したら
				{
					InputPad::stick[i][XINPUT_PAD::STICK_RIGHT_Y] = state[i].Gamepad.sThumbRY;
				}
				else		// スティックを操作していない
				{
					InputPad::stick[i][XINPUT_PAD::STICK_RIGHT_Y] = 0;
				}
			}
		}
	}


	// 更新
	void InputPad::EverUpdate()
	{
		ZeroMemory(&state[playerPadNum], sizeof(XINPUT_STATE));
		XInputGetState(playerPadNum, &state[playerPadNum]);
		// ボタン操作
		for (int j = 0; j != 16; ++j)
		{
			if (j == 10 || j == 11)		// xinput.h上で割り当てられていない
			{
				continue;
			}
			if ((state[playerPadNum].Gamepad.wButtons & (int)pow(2.0, (double)j)) != 0)		// ボタンを押したら
			{
				InputPad::button[playerPadNum][j]++;
				if (InputPad::button[playerPadNum][j] >= 1000)		// いつか上限値行くと思うので回避
				{
					InputPad::button[playerPadNum][j] = 2;
				}
			}
			else if (InputPad::button[playerPadNum][j] > 0)	// 押していたボタンを離したら
			{
				InputPad::button[playerPadNum][j] = -1;
			}
			else		// ボタンに触れていない
			{
				InputPad::button[playerPadNum][j] = 0;
			}
		}

		// スティック操作
		// 左スティックの左右(公式のデッドゾーンを使わせてもらうが自作する方が操作性よろしくなると思われる)
		if (state[playerPadNum].Gamepad.sThumbLX > stickDeadZone.LEFT_RIGHT
			|| state[playerPadNum].Gamepad.sThumbLX < stickDeadZone.LEFT_LEFT)		// スティックを操作したら
		{
			InputPad::stick[playerPadNum][XINPUT_PAD::STICK_LEFT_X] = state[playerPadNum].Gamepad.sThumbLX;
		}
		else		// スティックを操作していない
		{
			InputPad::stick[playerPadNum][XINPUT_PAD::STICK_LEFT_X] = 0;
		}
		// 左スティックの上下
		if (state[playerPadNum].Gamepad.sThumbLY > stickDeadZone.LEFT_UP
			|| state[playerPadNum].Gamepad.sThumbLY < stickDeadZone.LEFT_DOWN)		// スティックを操作したら
		{
			InputPad::stick[playerPadNum][XINPUT_PAD::STICK_LEFT_Y] = state[playerPadNum].Gamepad.sThumbLY;
		}
		else		// スティックを操作していない
		{
			InputPad::stick[playerPadNum][XINPUT_PAD::STICK_LEFT_Y] = 0;
		}
		// 右スティックの左右
		if (state[playerPadNum].Gamepad.sThumbRX > stickDeadZone.RIGHT_RIGHT
			|| state[playerPadNum].Gamepad.sThumbRX < stickDeadZone.RIGHT_LEFT)		// スティックを操作したら
		{
			InputPad::stick[playerPadNum][XINPUT_PAD::STICK_RIGHT_X] = state[playerPadNum].Gamepad.sThumbRX;
		}
		else		// スティックを操作していない
		{
			InputPad::stick[playerPadNum][XINPUT_PAD::STICK_RIGHT_X] = 0;
		}
		// 右スティックの上下
		if (state[playerPadNum].Gamepad.sThumbRY > stickDeadZone.RIGHT_UP
			|| state[playerPadNum].Gamepad.sThumbRY < stickDeadZone.RIGHT_DOWN)		// スティックを操作したら
		{
			InputPad::stick[playerPadNum][XINPUT_PAD::STICK_RIGHT_Y] = state[playerPadNum].Gamepad.sThumbRY;
		}
		else		// スティックを操作していない
		{
			InputPad::stick[playerPadNum][XINPUT_PAD::STICK_RIGHT_Y] = 0;
		}
	}


	// バイブレーションを行う
	void InputPad::Vibration(unsigned __int8 use_padnum, int time, unsigned __int16 rightVib, unsigned __int16 leftVib)
	{
		// バイブレーション値
		vibration.wRightMotorSpeed = rightVib;
		vibration.wLeftMotorSpeed = leftVib;

		XInputSetState(use_padnum, &vibration);		// バーブレーション値を設定
	}


	// バイブレーションを止める
	void InputPad::VibrationStop(unsigned __int8 use_padnum)
	{
		// バイブレーション値
		vibration.wRightMotorSpeed = 0;				// 0にする
		vibration.wLeftMotorSpeed = 0;				// 0にする

		XInputSetState(use_padnum, &vibration);		// バイブレーション値を設定
	}

	void InputPad::SetPlayerPadNum(unsigned __int8 number)
	{
		playerPadNum = number;
	}


	// コントローラーの繋がっている数
	int InputPad::GetPadNum()
	{
		return (int)InputPad::controllerNum;
	}

	unsigned __int8 InputPad::GetPlaerPadNumber()
	{
		return playerPadNum;
	}

	// ボタン入力取得
	int InputPad::GetPadButtonData(unsigned __int8 use_padnum, unsigned __int8 use_button)
	{
		return InputPad::button[use_padnum][use_button];
	}

	// トリガー入力取得
	int InputPad::GetPadTriggerData(unsigned __int8 use_padnum, bool use_Is_triggerLeft)
	{
		if (use_Is_triggerLeft)
		{
			return state[use_padnum].Gamepad.bLeftTrigger;
		}
		else
		{
			return state[use_padnum].Gamepad.bRightTrigger;
		}
	}

	// スティック入力取得
	int InputPad::GetPadThumbData(unsigned __int8 use_padnum, unsigned __int8 use_stick)
	{
		return InputPad::stick[use_padnum][use_stick];
	}

	// スティックのデッドゾーン設定
	void InputPad::SetPadDeadZone(short leftPad_right, short leftPad_left
		, short leftPad_up, short leftPad_down, short rightPad_right, short rightPad_left, short rightPad_up, short rightPad_down)
	{
		InputPad::stickDeadZone.LEFT_RIGHT = (leftPad_right == XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) ? XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE : leftPad_right;
		InputPad::stickDeadZone.LEFT_LEFT = (leftPad_left == -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) ? -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE : leftPad_left;
		InputPad::stickDeadZone.LEFT_UP = (leftPad_up == XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) ? XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE : leftPad_up;
		InputPad::stickDeadZone.LEFT_DOWN = (leftPad_down == -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) ? -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE : leftPad_down;
		InputPad::stickDeadZone.RIGHT_RIGHT = (rightPad_right == XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) ? XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE : rightPad_right;
		InputPad::stickDeadZone.RIGHT_LEFT = (rightPad_left == -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) ? -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE : rightPad_left;
		InputPad::stickDeadZone.RIGHT_UP = (rightPad_up == XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) ? XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE : rightPad_up;
		InputPad::stickDeadZone.RIGHT_DOWN = (rightPad_down == -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) ? -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE : rightPad_down;
	}

}
