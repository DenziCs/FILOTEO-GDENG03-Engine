#include"InspectorWindow.h"
#include"imgui.h"
#include"GlobalProperties.h"

InspectorWindow::InspectorWindow(std::string name) : AUIPanel::AUIPanel(name) {
}

InspectorWindow::~InspectorWindow() {
}

void InspectorWindow::draw() {
	ImGuiWindowFlags windowFlags = 0;
	windowFlags |= ImGuiWindowFlags_NoResize;

	ImGui::Begin("Scene Settings", NULL, windowFlags);
	ImGui::SetWindowSize(ImVec2(300, GlobalProperties::WINDOW_HEIGHT - 64));
	ImGui::SetWindowPos(ImVec2(GlobalProperties::WINDOW_WIDTH - 321, 20));

	if (!mSelectedObject) {
		ImGui::TextWrapped("No object selected. Select an object from the scene.");
	}

	ImGui::End();
}

void InspectorWindow::selectObject(AGameObject* game_object) {
	mSelectedObject = game_object;
}