#pragma once
#include"AUIPanel.h"
#include"AGameObject.h"
#include"PhysicsComponent.h"

class MaterialPanel;

class InspectorWindow : public AUIPanel
{
public:
	InspectorWindow(std::string name);
	~InspectorWindow();

	void draw() override;
	void setMaterialPanel(MaterialPanel* material_panel);

private:
	void updatePanelInfo(AGameObject* selected_object);
	void updateObjectInfo(AGameObject* selected_object);

	bool mIsSelectedObjectActive = true;
	float mObjectPosition[3] = {};
	float mObjectRotation[3] = {};
	float mObjectScale[3] = { 1.f, 1.f, 1.f };

	PhysicsComponent* mCurrentPhysicsComponent = nullptr;
	bool mHasPhysicsComponent = false;
	bool mActiveBody = true;
	bool mStaticBody = false;
	bool mGravityBody = true;
	float mBodyMass = 1000.f;
	float mAppliedForce[3] = {};

	MaterialPanel* mMaterialPanel = nullptr;
};