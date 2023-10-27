#pragma once
#include"AUIPanel.h"
#include"AGameObject.h"

class InspectorWindow : public AUIPanel
{
public:
	InspectorWindow(std::string name);
	~InspectorWindow();

	void draw() override;

private:
	void updateObjectInfo(AGameObject* selected_object);

	bool mIsSelectedObjectActive = true;
	float mObjectPosition[3] = {};
	float mObjectRotation[3] = {};
	float mObjectScale[3] = { 1.f, 1.f, 1.f };
};