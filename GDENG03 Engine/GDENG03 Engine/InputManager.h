#pragma once
#include<vector>
#include"AInputListener.h"

class InputManager
{
public:
	static InputManager* getInstance();
	static void destroy();

	void addListener(AInputListener* listener);
	void removeListener(AInputListener* listener);

	void update();

	bool isKeyDown(int key);

private:
	static InputManager* instance;

	void onPress(int key);
	void onRelease(int key);

	std::vector<AInputListener*> mListenerList;

	unsigned char mCurrKeyStates[256] = {};
	unsigned char mPrevKeyStates[256] = {};

	InputManager() {}
	~InputManager();
	InputManager(InputManager const&) {};
	InputManager& operator =(InputManager const&) {};
};