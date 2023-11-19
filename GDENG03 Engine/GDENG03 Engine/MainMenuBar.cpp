#include"MainMenuBar.h"
#include"GameObjectManager.h"

MainMenuBar::MainMenuBar(std::string name) : AUIPanel::AUIPanel(name) {}

void MainMenuBar::draw() {
	ImGui::BeginMainMenuBar();

	if (ImGui::BeginMenu("File")) {
		if (ImGui::MenuItem("New")) {}
		if (ImGui::MenuItem("Save")) {}
		if (ImGui::MenuItem("Open")) {}
		if (ImGui::MenuItem("Exit")) {}
		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu("Game Object")) {
		if (ImGui::MenuItem("Create Cube")) {
			GameObjectManager::getInstance()->createObject(GameObjectManager::CUBE);
		}
		if (ImGui::MenuItem("Create Sphere")) {}
		if (ImGui::MenuItem("Create Plane")) {
			GameObjectManager::getInstance()->createObject(GameObjectManager::PLANE);
		}
		if (ImGui::BeginMenu("Light")) {
			if (ImGui::MenuItem("Point Light")) {}
			ImGui::EndMenu();
		}
		if (ImGui::MenuItem("Create Several Physics Cubes")) {
			for (int i = 0; i < 10; i++) {
				GameObjectManager::getInstance()->createObject(GameObjectManager::PHYSICS_CUBE);
			}
		}
		if (ImGui::MenuItem("Create Static Physics Plane")) {
			GameObjectManager::getInstance()->createObject(GameObjectManager::PHYSICS_PLANE);
		}
		ImGui::EndMenu();
	}

	ImGui::EndMainMenuBar();
}