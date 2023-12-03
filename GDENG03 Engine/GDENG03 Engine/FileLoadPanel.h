#pragma once
#include"AUIPanel.h"
#include<imfilebrowser.h>

class FileLoadPanel : public AUIPanel
{
public:
	FileLoadPanel(std::string name);
	~FileLoadPanel();

	void draw() override;
	void openExplorer();
	void closeExplorer();

	bool isEnabled();

private:
	ImGui::FileBrowser* mBrowser;
};