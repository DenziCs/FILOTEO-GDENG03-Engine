#include"FileSavePanel.h"
#include"SceneTranslator.h"

FileSavePanel::FileSavePanel(std::string name) : AUIPanel::AUIPanel(name) {
	mBrowser = new ImGui::FileBrowser(ImGuiFileBrowserFlags_NoModal | ImGuiFileBrowserFlags_EnterNewFilename | ImGuiFileBrowserFlags_CreateNewDir);
	mBrowser->SetTitle("Save As");
	mBrowser->SetTypeFilters({ ".iet" });
}

FileSavePanel::~FileSavePanel() {
	delete mBrowser;
}

void FileSavePanel::draw() {
	mBrowser->Display();

	if (mBrowser->HasSelected()) {
		SceneTranslator::saveScene(mBrowser->GetSelected().string());
		mBrowser->Close();
	}
}

void FileSavePanel::openExplorer() {
	mBrowser->Open();
}

void FileSavePanel::closeExplorer() {
	mBrowser->Close();
}

bool FileSavePanel::isEnabled() {
	return mBrowser->IsOpened();
}