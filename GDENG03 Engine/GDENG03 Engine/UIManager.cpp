#include"UIManager.h"
#include"AGraphicsEngine.h"
#include"ADeviceContext.h"
#include"SimpleWindowPanel.h"

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
        mListUI[i]->draw();
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

    SimpleWindowPanel* simpleWindowPanel = new SimpleWindowPanel("First Panel");
    mListUI.push_back(simpleWindowPanel);
}

UIManager::~UIManager() {
    delete instance;
}