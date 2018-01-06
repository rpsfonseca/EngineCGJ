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

	//const char* listbox_items[] = { "Apple", "Banana", "Cherry", "Kiwi", "Mango", "Orange", "Pineapple", "Strawberry", "Watermelon" };
	//static int listbox_item_current = -1, listbox_item_current2 = -1;
	//ImGui::ListBox("listbox\n(single select)", &listbox_item_current, listbox_items, 4);

	////ImGui::PushItemWidth(-1);
	//ImGui::ListBox("listbox2\n(single select)", &listbox_item_current2, listbox_items, 4);
	////ImGui::PopItemWidth();
	//
	ImGui::End();

	ImGui::Render();
}

void EditorGUI::shutdown()
{
	ImGui_ImplGlfwGL3_Shutdown();
}
