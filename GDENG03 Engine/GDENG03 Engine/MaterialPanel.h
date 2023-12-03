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
	void closeExplorer();

	bool isEnabled();

private:
	ImGui::FileBrowser* mBrowser;
};