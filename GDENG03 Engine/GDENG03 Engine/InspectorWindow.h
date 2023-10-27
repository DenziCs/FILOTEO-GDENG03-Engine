#pragma once
#include"AUIPanel.h"

class InspectorWindow : public AUIPanel
{
public:
	InspectorWindow(std::string name);
	~InspectorWindow();

	void draw() override;

private:
	bool mIsSelectedObjectActive = true;
};