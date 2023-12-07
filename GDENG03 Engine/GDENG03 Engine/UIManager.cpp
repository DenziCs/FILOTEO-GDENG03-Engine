#include"UIManager.h"
#include"AGraphicsEngine.h"
#include"ADeviceContext.h"
#include"MainMenuBar.h"
#include"InspectorWindow.h"
#include"SceneOutliner.h"
#include"EngineProfiler.h"
#include"ScenePlayOptionsWindow.h"
#include"MaterialPanel.h"
#include"FileSavePanel.h"
#include"FileLoadPanel.h"

UIManager* UIManager::instance = nullptr;

UIManager* UIManager::getInstance() {
    return instance;
}

void UIManager::initialize(HWND window_handle) {
    instance = new UIManager(window_handle);
}

void UIManager::destroy() {
    for (int i = 0; i < instance->mListUI.size(); i++) {
        delete instance->mListUI[i];
    }

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void UIManager::draw() {
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    for (int i = 0; i < mListUI.size(); i++) {
        if (mListUI[i]->mIsEnabled) mListUI[i]->draw();
    }

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

UIManager::UIManager(HWND window_handle) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui_ImplWin32_Init(window_handle);
    ImGui_ImplDX11_Init(
        AGraphicsEngine::getInstance()->getD3DDevice(),
        AGraphicsEngine::getInstance()->getImmediateDeviceContext()->getD3DDeviceContext()
    );

    MainMenuBar* mainMenuBar = new MainMenuBar("Toolbar");
    mListUI.push_back(mainMenuBar);

    SceneOutliner* sceneOutliner = new SceneOutliner("Scene Outliner");
    mListUI.push_back(sceneOutliner);

    InspectorWindow* inspectorWindow = new InspectorWindow("Inspector Window");
    mListUI.push_back(inspectorWindow);

    EngineProfiler* engineProfiler = new EngineProfiler("Engine Profiler");
    mListUI.push_back(engineProfiler);

    ScenePlayOptionsWindow* scenePlay = new ScenePlayOptionsWindow("Scene Play Options");
    mListUI.push_back(scenePlay);

    MaterialPanel* material = new MaterialPanel("Material Panel");
    mListUI.push_back(material);
    inspectorWindow->setMaterialPanel(material);
    material->setInspectorWindow(inspectorWindow);

    FileSavePanel* save = new FileSavePanel("Save Panel");
    mListUI.push_back(save);
    mainMenuBar->setFileSavePanel(save);

    FileLoadPanel* load = new FileLoadPanel("Load Panel");
    mListUI.push_back(load);
    mainMenuBar->setFileLoadPanel(load);
}

UIManager::~UIManager() {
    delete instance;
}