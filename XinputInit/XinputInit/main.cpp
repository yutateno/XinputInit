#include <iostream>
#include "Input.hpp"

int main()
{
	Input::Input();
	Input::Update();

	std::cout << "�ڑ�����Ă���p�b�h�̌���" << Input::GetPadNum() << std::endl;

	while (true)
	{
		Input::Update();
		std::cout << "�E�X�e�B�b�N�̍��E" << Input::GetPadThumbData(XINPUT_PAD::PAD_NUM01, XINPUT_PAD::STICK_RIGHT_AXIS_X) << std::endl;
		
		if (Input::GetPadButtonData(XINPUT_PAD::PAD_NUM01, XINPUT_PAD::BUTTON_B) == 1)
		{
			Input::SetPadDeadZone(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE
				, 30000);
		}

		if(Input::GetPadButtonData(XINPUT_PAD::PAD_NUM01,XINPUT_PAD::BUTTON_A) == 1)	break;
	}
	
	return 0;
}
