#pragma once

#ifndef _MY_INPUT_H

#include <Windows.h>
#include <Xinput.h>
#include <math.h>

#pragma comment(lib, "xinput.lib")

#endif // !_MY_INPUT_H

namespace XINPUT_PAD
{
	// 番号
	const unsigned __int8 PAD_NUM01 = 0;
	const unsigned __int8 PAD_NUM02 = 1;
	const unsigned __int8 PAD_NUM03 = 2;
	const unsigned __int8 PAD_NUM04 = 3;

	// ボタン
	const unsigned __int8 XINPUT_DPAD_UP			 = 0;
	const unsigned __int8 XINPUT_DPAD_DOWN			 = 1;
	const unsigned __int8 XINPUT_DPAD_LEFT			 = 2;
	const unsigned __int8 XINPUT_DPAD_RIGHT			 = 3;
	const unsigned __int8 XINPUT_START				 = 4;
	const unsigned __int8 XINPUT_BACK				 = 5;
	const unsigned __int8 XINPUT_LEFT_THUMB_PUSH	 = 6;
	const unsigned __int8 XINPUT_RIGHT_THUMB_PUSH	 = 7;
	const unsigned __int8 XINPUT_LEFT_SHOULDER		 = 8;
	const unsigned __int8 XINPUT_RIGHT_SHOULDER		 = 9;
	const unsigned __int8 XINPUT_A					 = 12;
	const unsigned __int8 XINPUT_B					 = 13;
	const unsigned __int8 XINPUT_X					 = 14;
	const unsigned __int8 XINPUT_Y					 = 15;

	// トリガー
	const bool XINPUT_TRIGGER_RIGHT	 = 0;
	const bool XINPUT_TRIGGER_LEFT	 = 1;

	// スティック
	const unsigned __int8 XINPUT_THUMB_RIGHT_AXIS_X	 = 0;
	const unsigned __int8 XINPUT_THUMB_RIGHT_AXIS_Y	 = 1;
	const unsigned __int8 XINPUT_THUMB_LEFT_AXIS_X	 = 2;
	const unsigned __int8 XINPUT_THUMB_LEFT_AXIS_Y	 = 3;
}

class Input
{
private:
	static unsigned __int8 controllerNum;		// 接続している最大の個数

	static int button[4][16];					// wButtonの対応
	static int thumb[4][4];						// thumbの対応

	static XINPUT_STATE state[4];				// xinputの中身

public:
	Input();		// コンストラクタ
	~Input();		// デストラクタ

	static void Update();		// 操作更新

	static int GetPadNum();																// コントローラーの数
	static int GetPadButtonData(unsigned __int8 padnum, unsigned __int8 input);			// コントローラーのボタン操作
	static int GetPadTriggerData(unsigned __int8 padnum, bool triggerLeft);					// コントローラーのトリガー操作
	static int GetPadThumbData(unsigned __int8 padnum, unsigned __int8 thumb);			// コントローラーのスティック操作
};
