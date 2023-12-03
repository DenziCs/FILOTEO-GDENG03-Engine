#include"SceneFilePanel.h"

SceneFilePanel::SceneFilePanel(std::string name) : AUIPanel::AUIPanel(name) {
	mBrowser = new ImGui::FileBrowser(ImGuiFileBrowserFlags_NoModal | ImGuiFileBrowserFlags_EnterNewFilename | ImGuiFileBrowserFlags_CreateNewDir);
	mBrowser->SetTitle("Save As");
	mBrowser->SetTypeFilters({ ".h", ".cpp", ".txt", ".sln", ".vcxproj", ".hlsl", ".png", ".jpg" });
}

SceneFilePanel::~SceneFilePanel() {
	delete mBrowser;
}

void SceneFilePanel::draw() {
	mBrowser->Display();
}

void SceneFilePanel::openExplorer() {
	mBrowser->Open();
}

std::string SceneFilePanel::getSelectedFileName() {
	return std::string();
}