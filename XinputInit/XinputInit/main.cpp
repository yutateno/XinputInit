#include <stdio.h>
#include "Input.h"

int main()
{
	Input::Input();

	while (true)
	{
		Input::Update();

		//printf("%d\n", Input::GetPadThumbData(XINPUT_PAD::PAD_NUM01, XINPUT_PAD::STICK_LEFT_AXIS_X));
		//printf("%d\n\n", Input::GetPadThumbData(XINPUT_PAD::PAD_NUM01, XINPUT_PAD::STICK_LEFT_AXIS_Y));
		//printf("%d\n", Input::GetPadThumbData(XINPUT_PAD::PAD_NUM01, XINPUT_PAD::STICK_RIGHT_AXIS_X));
		//printf("%d\n\n", Input::GetPadThumbData(XINPUT_PAD::PAD_NUM01, XINPUT_PAD::STICK_RIGHT_AXIS_Y));
		break;
	}
	printf("%d\n", Input::GetPadNum());
	
	return 0;
}
