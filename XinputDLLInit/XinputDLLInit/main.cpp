#include "DxLib.h"

#include "DLLXinput.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	SetAlwaysRunFlag(TRUE);

	DLLXinput::InputPad* controller = new DLLXinput::InputPad();

	controller->SetPlayerPadNum(DLLXinput::XINPUT_PAD::NUM01);

	controller->FirstUpdate();

	while (ProcessMessage() != -1) {
		ClearDrawScreen();
		controller->EverUpdate();
		DrawFormatString(0, 0, 255, "%d", controller->GetPadButtonData(controller->GetPlaerPadNumber(), DLLXinput::XINPUT_PAD::BUTTON_A));
		ScreenFlip();
	}

	DxLib_End();
	return 0;
}