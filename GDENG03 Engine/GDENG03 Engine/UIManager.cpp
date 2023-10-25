#include"UIManager.h"
#include"AGraphicsEngine.h"
#include"ADeviceContext.h"

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
}

void UIManager::draw() {
    for (int i = 0; i < mListUI.size(); i++) {
        mListUI[i]->draw();
    }
}

UIManager::~UIManager() {
    delete instance;
}