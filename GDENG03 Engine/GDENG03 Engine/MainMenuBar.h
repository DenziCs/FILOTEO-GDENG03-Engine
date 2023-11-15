#pragma once
#include"AUIPanel.h"

class MainMenuBar : public AUIPanel
{
public:
	MainMenuBar(std::string name);
	~MainMenuBar() {};

	void draw() override;
};