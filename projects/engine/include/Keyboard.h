#pragma once

#include "Keyboard.h"

namespace input
{
	#define MAX_KEYS 1024
	class Keyboard
	{
	public:
		static Keyboard& GetInstance();

		inline void KeyPressed(unsigned int key) { mKeys[key] = true; }
		inline void KeyReleased(unsigned int key) { mKeys[key] = false; mKeysPressed[key] = false; }
		inline void SetKeyState(unsigned int key, bool state) { mKeys[key] = state; }
		inline bool isKeyDown(unsigned int key) { return mKeys[key]; }
		inline bool Pressed(unsigned int key) 
		{ 
			if (mKeys[key] && !mKeysPressed[key])
			{
				mKeysPressed[key] = true;
				return true;
			}
			else
			{
				return false;
			}
		}

	private:
		static Keyboard mInstance;
		bool mKeys[MAX_KEYS];
		bool mKeysPressed[MAX_KEYS];

		Keyboard()
		{
			for (int i = 0; i < MAX_KEYS; i++)
			{
				mKeys[i] = false;
				mKeysPressed[i] = false;
			}
		}

	};
}