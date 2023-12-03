#include"MaterialPanel.h"
#include<iostream>

MaterialPanel::MaterialPanel(std::string name) : AUIPanel::AUIPanel(name) {
	mBrowser = new ImGui::FileBrowser(ImGuiFileBrowserFlags_NoModal);
	mBrowser->SetTitle("Select Material");
	mBrowser->SetTypeFilters({ ".jpg", ".png" });
}

MaterialPanel::~MaterialPanel() {
	delete mBrowser;
}

void MaterialPanel::draw() {
	mBrowser->Display();

	if (mBrowser->HasSelected()) {
		std::cout << mBrowser->GetSelected().string() << std::endl;
		mBrowser->Close();
	}
}

void MaterialPanel::openExplorer() {
	mBrowser->Open();
}

void MaterialPanel::closeExplorer() {
	mBrowser->Close();
}

bool MaterialPanel::isEnabled() {
	return mBrowser->IsOpened();
}