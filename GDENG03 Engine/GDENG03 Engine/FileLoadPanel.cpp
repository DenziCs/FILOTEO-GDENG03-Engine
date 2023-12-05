#include"FileLoadPanel.h"
#include"SceneTranslator.h"

FileLoadPanel::FileLoadPanel(std::string name) : AUIPanel::AUIPanel(name) {
	mBrowser = new ImGui::FileBrowser(ImGuiFileBrowserFlags_NoModal);
	mBrowser->SetTitle("Select Scene");
	mBrowser->SetTypeFilters({ ".iet", ".unity" });
}

FileLoadPanel::~FileLoadPanel() {
	delete mBrowser;
}

void FileLoadPanel::draw() {
	mBrowser->Display();

	if (mBrowser->HasSelected()) {
		if (mBrowser->GetSelected().string().find(".iet") != std::string::npos)
			SceneTranslator::openScene(mBrowser->GetSelected().string());

		else if (mBrowser->GetSelected().string().find(".unity") != std::string::npos)
			SceneTranslator::openUnityScene(mBrowser->GetSelected().string());

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