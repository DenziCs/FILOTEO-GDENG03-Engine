#pragma once
#include"AUIPanel.h"
#include<imfilebrowser.h>

class InspectorWindow;

class MaterialPanel : public AUIPanel
{
public:
	MaterialPanel(std::string name);
	~MaterialPanel();

	void draw() override;
	void openExplorer();
	void closeExplorer();
	void setInspectorWindow(InspectorWindow* inspector_window);

	bool isEnabled();

private:
	ImGui::FileBrowser* mBrowser;
	InspectorWindow* mInspector = nullptr;
};