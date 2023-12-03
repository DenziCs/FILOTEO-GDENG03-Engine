#include"FileLoadPanel.h"
#include"SceneTranslator.h"

FileLoadPanel::FileLoadPanel(std::string name) : AUIPanel::AUIPanel(name) {
	mBrowser = new ImGui::FileBrowser(ImGuiFileBrowserFlags_NoModal);
	mBrowser->SetTitle("Select Scene");
	mBrowser->SetTypeFilters({ ".iet" });
}

FileLoadPanel::~FileLoadPanel() {
	delete mBrowser;
}

void FileLoadPanel::draw() {
	mBrowser->Display();

	if (mBrowser->HasSelected()) {
		SceneTranslator::openScene(mBrowser->GetSelected().string());
		mBrowser->Close();
	}
}

void FileLoadPanel::openExplorer() {
	mBrowser->Open();
}

void FileLoadPanel::closeExplorer() {
	mBrowser->Close();
}

bool FileLoadPanel::isEnabled() {
	return mBrowser->IsOpened();
}