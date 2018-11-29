#pragma once

#ifdef DLLXINPUT_EXPORTS
#define DLLXINPUT_API __declspec(dllexport)
#else
#define DLLXINPUT_API __declspec(dllimport)
#endif

namespace DLLXinput
{
	// ボタン番号
	namespace XINPUT_PAD
	{
		/// 番号------------------------------------
		// コントローラー1番
		const unsigned __int8 NUM01 = 0;
		// コントローラー2番
		const unsigned __int8 NUM02 = 1;
		// コントローラー3番
		const unsigned __int8 NUM03 = 2;
		// コントローラー4番
		const unsigned __int8 NUM04 = 3;


		/// ボタン-------------------------------------
		// 十字キー上
		const unsigned __int8 BUTTON_UP = 0;
		// 十字キー下
		const unsigned __int8 BUTTON_DOWN = 1;
		// 十字キー左
		const unsigned __int8 BUTTON_LEFT = 2;
		// 十字キー右
		const unsigned __int8 BUTTON_RIGHT = 3;
		// スタートボタン
		const unsigned __int8 BUTTON_START = 4;
		// バックボタン
		const unsigned __int8 BUTTON_BACK = 5;
		// 左スティック押し込み
		const unsigned __int8 BUTTON_STICK_LEFT = 6;
		// 右スティック押し込み
		const unsigned __int8 BUTTON_STICK_RIGHT = 7;
		// Aボタン
		const unsigned __int8 BUTTON_A = 12;
		// Bボタン
		const unsigned __int8 BUTTON_B = 13;
		// Xボタン
		const unsigned __int8 BUTTON_X = 14;
		// Yボタン
		const unsigned __int8 BUTTON_Y = 15;


		/// トリガ-------------------------------------
		// RTボタン
		const bool TRIGGER_RT = 0;
		// LTボタン
		const bool TRIGGER_LT = 1;
		// LBボタン
		const unsigned __int8 SHOULDER_LB = 8;
		// RBボタン
		const unsigned __int8 SHOULDER_RB = 9;


		/// スティック---------------------------------
		// 右スティック左右
		const unsigned __int8 STICK_RIGHT_X = 0;
		// 右スティック上下
		const unsigned __int8 STICK_RIGHT_Y = 1;
		// 左スティック左右
		const unsigned __int8 STICK_LEFT_X = 2;
		// 左スティック上下
		const unsigned __int8 STICK_LEFT_Y = 3;
		// スティックの右と上の最大値
		const int MAX_STICK_PLUS = 32767;
		// スティックの左と下の最大値
		const int MAX_STICK_MINUS = -32768;


		// バイブレーション最大値
		const unsigned __int16 VIB_MAX = 65535;
	}


	// スティックのデッドゾーン
	struct STICK_DEADZONE
	{
		// 左スティックの右
		short LEFT_RIGHT = 7849;
		// 左スティックの左
		short LEFT_LEFT = -7849;
		// 左スティックの上
		short LEFT_UP = 7849;
		// 左スティックの下
		short LEFT_DOWN = -7849;

		// 右スティックの右
		short RIGHT_RIGHT = 8689;
		// 右スティックの左
		short RIGHT_LEFT = -8689;
		// 右スティックの上
		short RIGHT_UP = 8689;
		// 右すてぃくの下
		short RIGHT_DOWN = -8689;
	};


	// 初期化
	DLLXINPUT_API void Init();

	// 解放
	DLLXINPUT_API void Clean();

	// ゲーム開始前操作更新
	DLLXINPUT_API void FirstUpdate();

	// ゲーム開始後操作更新
	DLLXINPUT_API void EverUpdate();

	// バイブレーションを行う
	DLLXINPUT_API void Vibration(unsigned __int8 use_padnum, int time = 0
		, unsigned __int16 rightVib = XINPUT_PAD::VIB_MAX, unsigned __int16 leftVib = XINPUT_PAD::VIB_MAX);	

	// バイブレーションをゆっくり止める
	DLLXINPUT_API void VibrationSlowlyStop();

	// バーブレーションを止める
	DLLXINPUT_API void VibrationStop(unsigned __int8 use_padnum);

	// プレイヤーの番号を設定
	DLLXINPUT_API void SetPlayerPadNum(unsigned __int8 playerPadNum);

	// デッドゾーンの設定値変更  // (ある程度楽したいので一応デフォルト引数乱用)
	DLLXINPUT_API void SetPadDeadZone(short leftPad_right = 7849, short leftPad_left = -7849
		, short leftPad_up = 7849, short leftPad_down = -7849
		, short rightPad_right = 8689, short rightPad_left = -8689
		, short rightPad_up = 8689, short rightPad_down = -8689);

	// デッドゾーンを考慮したコントローラーの稼働領域
	DLLXINPUT_API const short GetPadThumbMax(const bool stickLightNow, const bool stickXAxisNow, const bool stickPlusNow);

	// コントローラの数
	DLLXINPUT_API int GetPadNum();

	// 一人用ゲームでのユーザーの使用コントローラー
	DLLXINPUT_API unsigned __int8 GetPlayerPadNumber();

	// コントローラのボタン操作
	DLLXINPUT_API int GetPadButtonData(unsigned __int8 use_padnum, unsigned __int8 use_button);

	// コントローラのトリガー操作
	DLLXINPUT_API int GetPadTriggerData(unsigned __int8 use_padnum, bool use_Is_triggerLeft);

	// コントローラのスティック操作
	DLLXINPUT_API int GetPadThumbData(unsigned __int8 use_padnum, unsigned __int8 use_stick);
}