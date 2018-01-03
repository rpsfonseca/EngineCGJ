#pragma once

#include "GL\glew.h"
#include "glfw/glfw3.h"
#include "imgui.h"

bool ImGui_ImplGlfwGL3_Init(GLFWwindow* window, bool install_callbacks);
void ImGui_ImplGlfwGL3_RenderDrawLists(ImDrawData* draw_data);
void ImGui_ImplGlfwGL3_Shutdown();
void ImGui_ImplGlfwGL3_NewFrame();
bool ImGui_ImplGlfwGL3_CreateFontsTexture();
bool ImGui_ImplGlfwGL3_CreateDeviceObjects();
void ImGui_ImplGlfwGL3_InvalidateDeviceObjects();
void ImGui_ImplGlfwGL3_Shutdown();
void ImGui_ImplGlfwGL3_CharCallback(GLFWwindow*, unsigned int c);