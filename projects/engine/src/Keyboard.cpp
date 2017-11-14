#include "Keyboard.h"

namespace input
{
	Keyboard Keyboard::mInstance;

	Keyboard& Keyboard::GetInstance()
	{
		return mInstance;
	}
}