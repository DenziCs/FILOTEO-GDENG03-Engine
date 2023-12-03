#pragma once
#include"AUIPanel.h"
#include<imfilebrowser.h>

class MaterialPanel : public AUIPanel
{
public:
	MaterialPanel(std::string name);
	~MaterialPanel();

	void draw() override;
	void openExplorer();

	std::string getSelectedFileName();

private:
	ImGui::FileBrowser* mBrowser;
	std::string mSelectedFileName = "";
};