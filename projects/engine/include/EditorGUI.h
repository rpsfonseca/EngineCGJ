#pragma once

#include "imgui_GLFW.h"

class EditorGUI
{
public:
	EditorGUI();
	~EditorGUI();

	static void init(GLFWwindow* window);
	static void newFrame();
	static void renderGUI();
	static void shutdown();
};
