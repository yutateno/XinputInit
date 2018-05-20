#include <Windows.h>
#include <Xinput.h>
#include <stdio.h>
#include <math.h>
#include <winerror.h>

#pragma comment(lib, "xinput.lib")

const static int MAX_CONTROLLERS = 4;

int main()
{
	int test[16]{ 0,0,0,0,0,0,0,0,0,0,-1,-1,0,0,0,0};
	while (true)
	{
		for (DWORD i = 0; i < MAX_CONTROLLERS; i++)
		{
			XINPUT_STATE state[MAX_CONTROLLERS];
			ZeroMemory(&state[i], sizeof(XINPUT_STATE));
			if (XInputGetState(i, &state[i]) == ERROR_SUCCESS)
			{
				// ƒ{ƒ^ƒ“‘€ì
				for (int j = 0; j != 16; ++j)
				{
					if (j == 10 || j == 11)
					{
						continue;
					}
					if ((state[i].Gamepad.wButtons & (int)pow(2.0, (double)j)) != 0)
					{
						test[j]++;
					}
					else
					{
						test[j] = 0;
					}
					printf("%d", test[j]);
				}
			}
			else
			{
				ZeroMemory(&state[i], sizeof(XINPUT_STATE));
			}
		}
	}
	return 0;
}