#include "DxLib.h"

#include "DLLXinput.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	SetAlwaysRunFlag(TRUE);

	DLLXinput::Init();

	DLLXinput::SetPlayerPadNum(DLLXinput::XINPUT_PAD::NUM01);

	DLLXinput::FirstUpdate();

	while (ProcessMessage() != -1) {
		ClearDrawScreen();
		DLLXinput::EverUpdate();
		DrawFormatString(0, 0, 255, "%d", DLLXinput::GetPadButtonData(DLLXinput::GetPlaerPadNumber(), DLLXinput::XINPUT_PAD::BUTTON_A));
		ScreenFlip();
	}
	DLLXinput::Clean();
	DxLib_End();
	return 0;
}