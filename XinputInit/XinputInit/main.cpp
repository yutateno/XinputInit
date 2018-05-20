#include <stdio.h>
#include "Input.h"

int main()
{
	Input::Input();

	while (true)
	{
		Input::Update();

		printf("%d", Input::GetPadButtonDate(XINPUT_PAD::PAD_NUM01, XINPUT_PAD::XINPUT_A));
	}
	
	return 0;
}
