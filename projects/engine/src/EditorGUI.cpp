#include "EditorGUI.h"

EditorGUI::EditorGUI()
{
}

EditorGUI::~EditorGUI()
{
}

void EditorGUI::init(GLFWwindow * window)
{
	ImGui_ImplGlfwGL3_Init(window, true);
}

void EditorGUI::newFrame()
{
	ImGui_ImplGlfwGL3_NewFrame();
}

void EditorGUI::renderGUI()
{
	ImGui::Begin("Renderer", (bool*)1);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	
	ImGui::End();

	ImGui::Render();
}

void EditorGUI::shutdown()
{
	ImGui_ImplGlfwGL3_Shutdown();
}
