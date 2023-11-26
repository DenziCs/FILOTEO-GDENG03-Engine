#include"InspectorWindow.h"
#include"GlobalProperties.h"
#include"GameObjectManager.h"
#include"AngleConverter.h"
#include"ActionHistoryManager.h"
#include"BackendManager.h"
#include<iostream>

InspectorWindow::InspectorWindow(std::string name) : AUIPanel::AUIPanel(name) {}

InspectorWindow::~InspectorWindow() {}

void InspectorWindow::draw() {
	ImGuiWindowFlags windowFlags = 0;
	windowFlags |= ImGuiWindowFlags_NoResize;

	ImGui::Begin("Inspector Window", NULL, windowFlags);
	ImGui::SetWindowSize(ImVec2(300, GlobalProperties::WINDOW_HEIGHT - 64));
	ImGui::SetWindowPos(ImVec2(GlobalProperties::WINDOW_WIDTH - 321, 20));

	if (BackendManager::getInstance()->getEditorMode() != BackendManager::EDIT) ImGui::BeginDisabled();

	if (!GameObjectManager::getInstance()->getSelectedObject()) {
		ImGui::TextWrapped("No object selected. Select an object from the scene.");
	}

	else {
		AGameObject* selectedObject = GameObjectManager::getInstance()->getSelectedObject();
		updateObjectInfo(selectedObject);

		ImGui::Text("Selected Object:");
		ImGui::SameLine();
		ImGui::Text(selectedObject->getObjectName().c_str());
		ImGui::Separator();

		if (ImGui::Checkbox("Enabled", &mIsSelectedObjectActive)) {
			ActionHistoryManager::getInstance()->startAction(selectedObject);
			selectedObject->setActive(mIsSelectedObjectActive);
			ActionHistoryManager::getInstance()->endAction();
			std::cout << "Action taken: Modified isActive." << std::endl;
		}

		if (ImGui::DragFloat3("Position", mObjectPosition, 0.25f)) {
			ActionHistoryManager::getInstance()->startAction(selectedObject);
			selectedObject->setPosition(mObjectPosition[0], mObjectPosition[1], mObjectPosition[2]);
			ActionHistoryManager::getInstance()->endAction();
			std::cout << "Action taken: Modified position." << std::endl;
		}

		if (ImGui::DragFloat3("Rotation", mObjectRotation, 1.f, -360.f, 360.f)) {
			ActionHistoryManager::getInstance()->startAction(selectedObject);
			selectedObject->setRotation(AngleConverter::toRadians(mObjectRotation[0]), AngleConverter::toRadians(mObjectRotation[1]), AngleConverter::toRadians(mObjectRotation[2]));
			ActionHistoryManager::getInstance()->endAction();
			std::cout << "Action taken: Modified rotation." << std::endl;
		}

		if (ImGui::DragFloat3("Scale", mObjectScale, 0.25f, 0.f, 100.f)) {
			ActionHistoryManager::getInstance()->startAction(selectedObject);
			selectedObject->setScale(mObjectScale[0], mObjectScale[1], mObjectScale[2]);
			ActionHistoryManager::getInstance()->endAction();
			std::cout << "Action taken: Modified scale." << std::endl;
		}
	}

	if (BackendManager::getInstance()->getEditorMode() != BackendManager::EDIT) ImGui::EndDisabled();
	ImGui::End();
}

void InspectorWindow::updateObjectInfo(AGameObject* selected_object) {
	mIsSelectedObjectActive = selected_object->isActive();

	Vector3D position = selected_object->getLocalPosition();
	mObjectPosition[0] = position.x;
	mObjectPosition[1] = position.y;
	mObjectPosition[2] = position.z;

	Vector3D rotation = selected_object->getLocalRotation();
	mObjectRotation[0] = AngleConverter::toDegrees(rotation.x);
	mObjectRotation[1] = AngleConverter::toDegrees(rotation.y);
	mObjectRotation[2] = AngleConverter::toDegrees(rotation.z);

	Vector3D scale = selected_object->getLocalScale();
	mObjectScale[0] = scale.x;
	mObjectScale[1] = scale.y;
	mObjectScale[2] = scale.z;
}