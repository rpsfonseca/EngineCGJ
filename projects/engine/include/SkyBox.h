#pragma once
#include <string>

class SkyBox {
public:
	void loadSkyBox(std::string& filename);
	void renderSkyBox();
};