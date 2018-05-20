#include <stdio.h>
#include "Input.h"

int main()
{
	Input::Input();

	while (true)
	{
		Input::Update();

		printf("%d\n", Input::GetPadThumbData(XINPUT_PAD::PAD_NUM01, XINPUT_PAD::XINPUT_THUMB_LEFT_AXIS_X));
		printf("%d\n\n", Input::GetPadThumbData(XINPUT_PAD::PAD_NUM01, XINPUT_PAD::XINPUT_THUMB_LEFT_AXIS_Y));
		printf("%d\n", Input::GetPadThumbData(XINPUT_PAD::PAD_NUM01, XINPUT_PAD::XINPUT_THUMB_RIGHT_AXIS_X));
		printf("%d\n\n", Input::GetPadThumbData(XINPUT_PAD::PAD_NUM01, XINPUT_PAD::XINPUT_THUMB_RIGHT_AXIS_Y));
	}
	
	return 0;
}
