#pragma once
#include"AUIPanel.h"
#include<vector>
#include<unordered_map>
#include<Windows.h>
#include"imgui.h"
#include"imgui_impl_dx11.h"
#include"imgui_impl_win32.h"
#include"imgui_stdlib.h"

class UIManager
{
public:
	static UIManager* getInstance();
	static void initialize(HWND window_handle);
	static void destroy();

	void draw();

private:
	UIManager(HWND window_handle);
	~UIManager();
	UIManager(UIManager const&) {};
	UIManager& operator =(UIManager const&) {};
	static UIManager* instance;

	std::vector<AUIPanel*> mListUI;
};