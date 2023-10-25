#pragma once
#include<string>

class UIManager;

class AUIPanel
{
protected:
	AUIPanel(std::string name);
	~AUIPanel() {};

	std::string getName();
	virtual void draw() = 0;

	std::string mPanelName;

	friend class UIManager;
};