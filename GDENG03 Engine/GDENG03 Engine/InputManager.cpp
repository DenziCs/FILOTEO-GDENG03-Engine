#include"InputManager.h"
#include<Windows.h>
#include<iostream>

InputManager* InputManager::instance = nullptr;

InputManager* InputManager::getInstance() {
	if (instance == nullptr) instance = new InputManager();
	return instance;
}

void InputManager::destroy() {
	if (instance) instance->mListenerList.clear();
}

void InputManager::addListener(AInputListener* listener) {
	mListenerList.push_back(listener);
}

void InputManager::removeListener(AInputListener* listener) {
	int index = -1;
	for (int i = 0; i < mListenerList.size(); i++) {
		if (mListenerList[i] == listener) {
			index = i;
			break;
		}
	}

	if (index > -1) {
		mListenerList.erase(mListenerList.begin() + index);
	}
}

void InputManager::update() {
	if (GetKeyboardState(mCurrKeyStates)) {
		for (int i = 0; i < ARRAYSIZE(mCurrKeyStates); i++) {
			if (mCurrKeyStates[i] & 0x80 && mCurrKeyStates[i] != mPrevKeyStates[i]) onPress(i);
			else if (mCurrKeyStates[i] != mPrevKeyStates[i]) onRelease(i);
		}
	}

	::memcpy(mPrevKeyStates, mCurrKeyStates, 256 * sizeof(unsigned char));
}

bool InputManager::isKeyDown(int key) {
	for (int i = 0; i < ARRAYSIZE(mCurrKeyStates); i++) {
		if (mCurrKeyStates[i] & 0x80 && i == key) return true;
		else if (i == key) return false;
	}

	return false;
}

void InputManager::onPress(int key) {
	for (int i = 0; i < mListenerList.size(); i++) {
		mListenerList[i]->onPress(key);
	}
}

void InputManager::onRelease(int key) {
	for (int i = 0; i < mListenerList.size(); i++) {
		mListenerList[i]->onRelease(key);
	}
}

InputManager::~InputManager() {}