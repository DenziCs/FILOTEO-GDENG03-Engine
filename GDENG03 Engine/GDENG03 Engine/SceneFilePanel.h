#pragma once
#include"AUIPanel.h"
#include<imfilebrowser.h>

class SceneFilePanel : public AUIPanel
{
public:
	SceneFilePanel(std::string name);
	~SceneFilePanel();

	void draw() override;
	void openExplorer();

	std::string getSelectedFileName();

private:
	ImGui::FileBrowser* mBrowser;
	std::string mSelectedFileName = "";
};