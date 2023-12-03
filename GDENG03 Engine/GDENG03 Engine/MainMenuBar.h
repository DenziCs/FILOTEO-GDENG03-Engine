#pragma once
#include"AUIPanel.h"

class FileSavePanel;
class FileLoadPanel;

class MainMenuBar : public AUIPanel
{
public:
	MainMenuBar(std::string name);
	~MainMenuBar() {};

	void draw() override;
	void setFileSavePanel(FileSavePanel* save_panel);
	void setFileLoadPanel(FileLoadPanel* load_panel);

private:
	FileSavePanel* mSavePanel = nullptr;
	FileLoadPanel* mLoadPanel = nullptr;
};