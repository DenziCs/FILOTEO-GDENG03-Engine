#pragma once
#include"AUIPanel.h"
#include<imfilebrowser.h>

class FileSavePanel : public AUIPanel
{
public:
	FileSavePanel(std::string name);
	~FileSavePanel();

	void draw() override;
	void openExplorer();
	void closeExplorer();

	bool isEnabled();

private:
	ImGui::FileBrowser* mBrowser;
};