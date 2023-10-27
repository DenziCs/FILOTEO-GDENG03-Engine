#pragma once
#include"AUIPanel.h"
#include"AGameObject.h"

class InspectorWindow : public AUIPanel
{
public:
	InspectorWindow(std::string name);
	~InspectorWindow();

	void draw() override;
	void selectObject(AGameObject* game_object);

private:
	AGameObject* mSelectedObject = nullptr;
};