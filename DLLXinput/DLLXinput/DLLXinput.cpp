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

	// プレイヤーが使うコントローラー
	static unsigned __int8 playerPadNum = 0;

	// 接続している最大の個数
	static unsigned __int8 controllerNum;

	// コントローラー４つ
	static bool setControll[4];

	// wButtonの対応
	static int button[4][16];

	// stickの対応(公式だとthumb)
	static int stick[4][4];

	// スティックのデッドゾーン値
	static STICK_DEADZONE stickDeadZone;

	// バイブレーション時間から減らす数値
	static int rightVibrationSlow = 0;
	static int leftVibrationSlow = 0;


	
	void Init()
	{
		// コントローラ分ループ
		controllerNum = 0;
		for (int i = 0; i != 4; ++i)
		{
			if (XInputGetState(i, &state[i]) == ERROR_SUCCESS)
			{
				controllerNum++;
				setControll[i] = true;
			}
			else
			{
				setControll[i] = false;
			}
		}
		ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
		ZeroMemory(&state, sizeof(XINPUT_STATE));
		for (int i = 0; i != controllerNum; ++i)
		{
			// ボタンを0に初期化(スティックはデッドゾーンの関係で行わない)
			for (int j = 0; j != 16; ++j)
			{
				button[i][j] = 0;
			}
		}
		rightVibrationSlow = 0;
		leftVibrationSlow = 0;
	}


	void Clean()
	{
		ZeroMemory(&state, sizeof(XINPUT_STATE));
	}


	void AllControllerUpdate()
	{
		// コントローラの数だけ行う
		for (int i = 0; i != 4; ++i)
		{
			if (setControll[i])		// 接続されているコントローラーのみ判断するように
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
						button[i][j]++;
						if (button[i][j] >= 1000)		// いつか上限値行くと思うので回避
						{
							button[i][j] = 2;
						}
					}
					else if (button[i][j] > 0)	// 押していたボタンを離したら
					{
						button[i][j] = -1;
					}
					else		// ボタンに触れていない
					{
						button[i][j] = 0;
					}
				}

				// スティック操作
				// 左スティックの左右(公式のデッドゾーンを使わせてもらうが自作する方が操作性よろしくなると思われる)
				if (state[i].Gamepad.sThumbLX > stickDeadZone.LEFT_RIGHT
					|| state[i].Gamepad.sThumbLX < stickDeadZone.LEFT_LEFT)		// スティックを操作したら
				{
					if (state[i].Gamepad.sThumbLX > 0)
					{
						stick[i][XINPUT_PAD::STICK_LEFT_X] = state[i].Gamepad.sThumbLX - stickDeadZone.LEFT_RIGHT;
					}
					else
					{
						stick[i][XINPUT_PAD::STICK_LEFT_X] = state[i].Gamepad.sThumbLX - stickDeadZone.LEFT_LEFT;
					}
				}
				else		// スティックを操作していない
				{
					stick[i][XINPUT_PAD::STICK_LEFT_X] = 0;
				}
				// 左スティックの上下
				if (state[i].Gamepad.sThumbLY > stickDeadZone.LEFT_UP
					|| state[i].Gamepad.sThumbLY < stickDeadZone.LEFT_DOWN)		// スティックを操作したら
				{
					if (state[i].Gamepad.sThumbLY > 0)
					{
						stick[i][XINPUT_PAD::STICK_LEFT_Y] = state[i].Gamepad.sThumbLY - stickDeadZone.LEFT_UP;
					}
					else
					{
						stick[i][XINPUT_PAD::STICK_LEFT_Y] = state[i].Gamepad.sThumbLY - stickDeadZone.LEFT_DOWN;
					}
				}
				else		// スティックを操作していない
				{
					stick[i][XINPUT_PAD::STICK_LEFT_Y] = 0;
				}
				// 右スティックの左右
				if (state[i].Gamepad.sThumbRX > stickDeadZone.RIGHT_RIGHT
					|| state[i].Gamepad.sThumbRX < stickDeadZone.RIGHT_LEFT)		// スティックを操作したら
				{
					if (state[i].Gamepad.sThumbRX > 0)
					{
						stick[i][XINPUT_PAD::STICK_RIGHT_X] = state[i].Gamepad.sThumbRX - stickDeadZone.RIGHT_RIGHT;
					}
					else
					{
						stick[i][XINPUT_PAD::STICK_RIGHT_X] = state[i].Gamepad.sThumbRX - stickDeadZone.RIGHT_LEFT;
					}
				}
				else		// スティックを操作していない
				{
					stick[i][XINPUT_PAD::STICK_RIGHT_X] = 0;
				}
				// 右スティックの上下
				if (state[i].Gamepad.sThumbRY > stickDeadZone.RIGHT_UP
					|| state[i].Gamepad.sThumbRY < stickDeadZone.RIGHT_DOWN)		// スティックを操作したら
				{
					if (state[i].Gamepad.sThumbRY > 0)
					{
						stick[i][XINPUT_PAD::STICK_RIGHT_Y] = state[i].Gamepad.sThumbRY - stickDeadZone.RIGHT_UP;
					}
					else
					{
						stick[i][XINPUT_PAD::STICK_RIGHT_Y] = state[i].Gamepad.sThumbRY - stickDeadZone.RIGHT_DOWN;
					}
				}
				else		// スティックを操作していない
				{
					stick[i][XINPUT_PAD::STICK_RIGHT_Y] = 0;
				}
			}
		}
	}


	// 更新
	void OneControllerUpdate()
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
				button[playerPadNum][j]++;
				if (button[playerPadNum][j] >= 1000)		// いつか上限値行くと思うので回避
				{
					button[playerPadNum][j] = 2;
				}
			}
			else if (button[playerPadNum][j] > 0)	// 押していたボタンを離したら
			{
				button[playerPadNum][j] = -1;
			}
			else		// ボタンに触れていない
			{
				button[playerPadNum][j] = 0;
			}
		}

		// スティック操作
		// 左スティックの左右(公式のデッドゾーンを使わせてもらうが自作する方が操作性よろしくなると思われる)
		if (state[playerPadNum].Gamepad.sThumbLX > stickDeadZone.LEFT_RIGHT
			|| state[playerPadNum].Gamepad.sThumbLX < stickDeadZone.LEFT_LEFT)		// スティックを操作したら
		{
			if (state[playerPadNum].Gamepad.sThumbLX > 0)
			{
				stick[playerPadNum][XINPUT_PAD::STICK_LEFT_X] = state[playerPadNum].Gamepad.sThumbLX - stickDeadZone.LEFT_RIGHT;
			}
			else
			{
				stick[playerPadNum][XINPUT_PAD::STICK_LEFT_X] = state[playerPadNum].Gamepad.sThumbLX - stickDeadZone.LEFT_LEFT;
			}
		}
		else		// スティックを操作していない
		{
			stick[playerPadNum][XINPUT_PAD::STICK_LEFT_X] = 0;
		}
		// 左スティックの上下
		if (state[playerPadNum].Gamepad.sThumbLY > stickDeadZone.LEFT_UP
			|| state[playerPadNum].Gamepad.sThumbLY < stickDeadZone.LEFT_DOWN)		// スティックを操作したら
		{
			if (state[playerPadNum].Gamepad.sThumbLY > 0)
			{
				stick[playerPadNum][XINPUT_PAD::STICK_LEFT_Y] = state[playerPadNum].Gamepad.sThumbLY - stickDeadZone.LEFT_UP;
			}
			else
			{
				stick[playerPadNum][XINPUT_PAD::STICK_LEFT_Y] = state[playerPadNum].Gamepad.sThumbLY - stickDeadZone.LEFT_DOWN;
			}
		}
		else		// スティックを操作していない
		{
			stick[playerPadNum][XINPUT_PAD::STICK_LEFT_Y] = 0;
		}
		// 右スティックの左右
		if (state[playerPadNum].Gamepad.sThumbRX > stickDeadZone.RIGHT_RIGHT
			|| state[playerPadNum].Gamepad.sThumbRX < stickDeadZone.RIGHT_LEFT)		// スティックを操作したら
		{
			if (state[playerPadNum].Gamepad.sThumbRX > 0)
			{
				stick[playerPadNum][XINPUT_PAD::STICK_RIGHT_X] = state[playerPadNum].Gamepad.sThumbRX - stickDeadZone.RIGHT_RIGHT;
			}
			else
			{
				stick[playerPadNum][XINPUT_PAD::STICK_RIGHT_X] = state[playerPadNum].Gamepad.sThumbRX - stickDeadZone.RIGHT_LEFT;
			}
		}
		else		// スティックを操作していない
		{
			stick[playerPadNum][XINPUT_PAD::STICK_RIGHT_X] = 0;
		}
		// 右スティックの上下
		if (state[playerPadNum].Gamepad.sThumbRY > stickDeadZone.RIGHT_UP
			|| state[playerPadNum].Gamepad.sThumbRY < stickDeadZone.RIGHT_DOWN)		// スティックを操作したら
		{
			if (state[playerPadNum].Gamepad.sThumbRY > 0)
			{
				stick[playerPadNum][XINPUT_PAD::STICK_RIGHT_Y] = state[playerPadNum].Gamepad.sThumbRY - stickDeadZone.RIGHT_UP;
			}
			else
			{
				stick[playerPadNum][XINPUT_PAD::STICK_RIGHT_Y] = state[playerPadNum].Gamepad.sThumbRY - stickDeadZone.RIGHT_DOWN;
			}
		}
		else		// スティックを操作していない
		{
			stick[playerPadNum][XINPUT_PAD::STICK_RIGHT_Y] = 0;
		}
	}


	// バイブレーションを行う
	void Vibration(unsigned __int8 use_padnum, int time, unsigned __int16 rightVib, unsigned __int16 leftVib)
	{
		// バイブレーション値
		vibration.wRightMotorSpeed = rightVib;
		vibration.wLeftMotorSpeed = leftVib;

		if (time != 0)
		{
			rightVibrationSlow = static_cast<int>(rightVib / time);
			leftVibrationSlow = static_cast<int>(leftVib / time);
		}
		else
		{
			rightVibrationSlow = rightVib;
			leftVibrationSlow = leftVib;
		}

		XInputSetState(use_padnum, &vibration);		// バーブレーション値を設定
	}


	void VibrationSlowlyStop(unsigned __int8 use_padnum)
	{
		// バイブレーション値
		if (vibration.wRightMotorSpeed > 0)
		{
			if (vibration.wRightMotorSpeed - rightVibrationSlow <= 0)
			{
				vibration.wRightMotorSpeed = 0;				// 0にする
				rightVibrationSlow = 0;
			}
			else
			{
				vibration.wRightMotorSpeed -= rightVibrationSlow;
			}
		}

		if (vibration.wLeftMotorSpeed > 0)
		{
			if (vibration.wLeftMotorSpeed - leftVibrationSlow <= 0)
			{
				vibration.wLeftMotorSpeed = 0;				// 0にする
				leftVibrationSlow = 0;
			}
			else
			{
				vibration.wLeftMotorSpeed -= leftVibrationSlow;
			}
		}

		XInputSetState(use_padnum, &vibration);		// バイブレーション値を設定
	}


	// バイブレーションを止める
	void VibrationStop(unsigned __int8 use_padnum)
	{
		// バイブレーション値
		vibration.wRightMotorSpeed = 0;				// 0にする
		vibration.wLeftMotorSpeed = 0;				// 0にする

		XInputSetState(use_padnum, &vibration);		// バイブレーション値を設定
	}


	void SetPlayerPadNum(unsigned __int8 number)
	{
		playerPadNum = number;
	}


	// コントローラーの繋がっている数
	int GetPadNum()
	{
		return (int)controllerNum;
	}


	unsigned __int8 GetPlayerPadNumber()
	{
		return playerPadNum;
	}


	// ボタン入力取得
	int GetPadButtonData(unsigned __int8 use_padnum, unsigned __int8 use_button)
	{
		return button[use_padnum][use_button];
	}


	// トリガー入力取得
	int GetPadTriggerData(unsigned __int8 use_padnum, bool use_Is_triggerLeft)
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
	int GetPadThumbData(unsigned __int8 use_padnum, unsigned __int8 use_stick)
	{
		return stick[use_padnum][use_stick];
	}


	const short GetPadThumbMax(const bool stickLightNow, const bool stickXAxisNow, const bool stickPlusNow)
	{
		if (stickLightNow)
		{
			if (stickXAxisNow)
			{
				if (stickPlusNow)
				{
					return XINPUT_PAD::MAX_STICK_PLUS - stickDeadZone.RIGHT_RIGHT;
				}
				else
				{
					return -(XINPUT_PAD::MAX_STICK_MINUS - stickDeadZone.RIGHT_LEFT);
				}
			}
			else
			{
				if (stickPlusNow)
				{
					return XINPUT_PAD::MAX_STICK_PLUS - stickDeadZone.RIGHT_UP;
				}
				else
				{
					return -(XINPUT_PAD::MAX_STICK_MINUS - stickDeadZone.RIGHT_DOWN);
				}
			}
		}
		else
		{
			if (stickXAxisNow)
			{
				if (stickPlusNow)
				{
					return XINPUT_PAD::MAX_STICK_PLUS - stickDeadZone.LEFT_RIGHT;
				}
				else
				{
					return -(XINPUT_PAD::MAX_STICK_MINUS - stickDeadZone.LEFT_LEFT);
				}
			}
			else
			{
				if (stickPlusNow)
				{
					return XINPUT_PAD::MAX_STICK_PLUS - stickDeadZone.LEFT_UP;
				}
				else
				{
					return -(XINPUT_PAD::MAX_STICK_MINUS - stickDeadZone.LEFT_DOWN);
				}
			}
		}
	}


	// スティックのデッドゾーン設定
	void SetPadDeadZone(short leftPad_right, short leftPad_left
		, short leftPad_up, short leftPad_down, short rightPad_right, short rightPad_left, short rightPad_up, short rightPad_down)
	{
		stickDeadZone.LEFT_RIGHT = (leftPad_right == XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) ? XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE : leftPad_right;
		stickDeadZone.LEFT_LEFT = (leftPad_left == -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) ? -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE : leftPad_left;
		stickDeadZone.LEFT_UP = (leftPad_up == XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) ? XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE : leftPad_up;
		stickDeadZone.LEFT_DOWN = (leftPad_down == -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) ? -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE : leftPad_down;
		stickDeadZone.RIGHT_RIGHT = (rightPad_right == XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) ? XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE : rightPad_right;
		stickDeadZone.RIGHT_LEFT = (rightPad_left == -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) ? -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE : rightPad_left;
		stickDeadZone.RIGHT_UP = (rightPad_up == XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) ? XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE : rightPad_up;
		stickDeadZone.RIGHT_DOWN = (rightPad_down == -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) ? -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE : rightPad_down;
	}

}
