#include"MaterialPanel.h"

MaterialPanel::MaterialPanel(std::string name) : AUIPanel::AUIPanel(name) {
	mBrowser = new ImGui::FileBrowser(ImGuiFileBrowserFlags_NoModal);
	mBrowser->SetTitle("Material Explorer");
	mBrowser->SetTypeFilters({ ".h", ".cpp", ".txt", ".sln", ".vcxproj", ".hlsl" });
}

MaterialPanel::~MaterialPanel() {
	delete mBrowser;
}

void MaterialPanel::draw() {
	mBrowser->Display();
}

void MaterialPanel::openExplorer() {
	mBrowser->Open();
}

std::string MaterialPanel::getSelectedFileName() {
	return mSelectedFileName;
}