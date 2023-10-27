#include"InspectorWindow.h"
#include"GlobalProperties.h"
#include"GameObjectManager.h"

InspectorWindow::InspectorWindow(std::string name) : AUIPanel::AUIPanel(name) {}

InspectorWindow::~InspectorWindow() {}

void InspectorWindow::draw() {
	ImGuiWindowFlags windowFlags = 0;
	windowFlags |= ImGuiWindowFlags_NoResize;

	ImGui::Begin("Inspector Window", NULL, windowFlags);
	ImGui::SetWindowSize(ImVec2(300, GlobalProperties::WINDOW_HEIGHT - 64));
	ImGui::SetWindowPos(ImVec2(GlobalProperties::WINDOW_WIDTH - 321, 20));

	if (!GameObjectManager::getInstance()->getSelectedObject()) {
		ImGui::TextWrapped("No object selected. Select an object from the scene.");
	}

	else {
		AGameObject* selectedObject = GameObjectManager::getInstance()->getSelectedObject();
		// mIsSelectedObjectActive = selectedObject->isActive();

		ImGui::Text("Selected Object:");
		ImGui::Text(selectedObject->getObjectName().c_str());
		ImGui::Separator();
		ImGui::Checkbox("Enabled", &mIsSelectedObjectActive);

		// selectedObject->setActive(mIsSelectedObjectActive);
	}

	ImGui::End();
}