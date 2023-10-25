#include"SimpleWindowPanel.h"
#include"GlobalProperties.h"
#include"imgui.h"

SimpleWindowPanel::SimpleWindowPanel(std::string name) : AUIPanel::AUIPanel(name) {
	mBackgroundColor[0] = GlobalProperties::BACKGROUND_COLOR[0];
	mBackgroundColor[1] = GlobalProperties::BACKGROUND_COLOR[1];
	mBackgroundColor[2] = GlobalProperties::BACKGROUND_COLOR[2];
}

void SimpleWindowPanel::draw() {
	ImGuiWindowFlags windowFlags = 0;
	windowFlags |= ImGuiWindowFlags_NoResize;
	ImGui::Begin("Scene Settings", NULL, windowFlags);
	ImGui::SetWindowSize(ImVec2(400, 120));
	ImGui::Text("Below are settings for configuring the scene.");
	ImGui::Checkbox("Show Demo Window", &mIsDemoWindowOpen);
	ImGui::ColorEdit3("Clear Color", mBackgroundColor);
	if (GlobalProperties::IS_CUBE_MOVEMENT_ON) {
		if (ImGui::Button("Pause Animation")) GlobalProperties::setActiveCubes(false);
	}
	else if (ImGui::Button("Resume Animation")) GlobalProperties::setActiveCubes(true);

	ImGui::End();

	if (mIsDemoWindowOpen) ImGui::ShowDemoWindow();
	GlobalProperties::setBackgroundColor(mBackgroundColor[0], mBackgroundColor[1], mBackgroundColor[2]);
}