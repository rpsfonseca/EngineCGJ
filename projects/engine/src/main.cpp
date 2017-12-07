#include "Mat4.h"
#include "Vec4.h"
#include "Quat.h"
#include "Application.h"

#include <iostream>
#include <vector>
#include <string>

using namespace math;

int main()
{
	Application app = Application(3, 3);
	app.setupApp();
	app.mainLoop();
	exit(EXIT_SUCCESS);
}