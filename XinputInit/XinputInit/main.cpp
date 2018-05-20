#include <Windows.h>
#include <Xinput.h>
#include <stdio.h>

#pragma comment(lib, "xinput.lib")

#define MAX_CONTROLLERS 4

int main()
{
	int test = 0;
	for (DWORD i = 0; i< MAX_CONTROLLERS; i++) 
	{
		XINPUT_STATE state[MAX_CONTROLLERS];
		ZeroMemory(&state[i], sizeof(XINPUT_STATE)); 
		if(XInputGetState(i, &state[i]) == ERROR_SUCCESS )
		{      
			// Œq‚ª‚Á‚½ 
			if ((state[i].Gamepad.wButtons & XINPUT_GAMEPAD_A) != 0)
			{
				test++;
			}
			else
			{
				test = 0;
			}
		}    
		else 
		{        
			// Œq‚ª‚Á‚Ä‚¢‚È‚¢ 
		}
	}
	printf("%d", test);
	return 0;
}