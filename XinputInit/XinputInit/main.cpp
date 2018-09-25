#include <iostream>
#include "Input.hpp"

int main()
{
	InputPad::InputPad();
	InputPad::FirstUpdate();

	std::cout << "接続されているパッドの個数は" << InputPad::GetPadNum() << std::endl;

	while (true)
	{
		InputPad::EverUpdate();
		std::cout << "左スティックの左右" << (InputPad::GetPadThumbData(XINPUT_PAD::NUM01, XINPUT_PAD::STICK_LEFT_X) - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) % 24918 << std::endl;
		
		if (InputPad::GetPadButtonData(XINPUT_PAD::NUM01, XINPUT_PAD::BUTTON_B) == 1)
		{
			InputPad::SetPadDeadZone(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
				, 30000);
		}

		if(InputPad::GetPadButtonData(XINPUT_PAD::NUM01,XINPUT_PAD::BUTTON_A) == 1)	break;
	}
	
	return 0;
}
