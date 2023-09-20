#include"AWindow.h"

AWindow* window = nullptr;

AWindow::AWindow() {}

AWindow::~AWindow() {}

LRESULT CALLBACK WndProc(HWND window_handle, UINT msg, WPARAM w_param, LPARAM l_param) {
	switch (msg) {
	case WM_CREATE: {
		window->setWindowHandle(window_handle);
		window->onCreate();
		break;
	}
	case WM_DESTROY: {
		window->onDestroy();
		PostQuitMessage(0);
		break;
	}
	default: return ::DefWindowProc(window_handle, msg, w_param, l_param);
	}

	return NULL;
}

bool AWindow::initialize() {
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;

	wc.lpszClassName = L"AWindowClass";
	wc.lpszMenuName = L"";
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;

	if (!::RegisterClassEx(&wc)) return false;

	if (!window) window = this;
	mWindowHandle = ::CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		L"AWindowClass",
		L"FILOTEO HO -- Rendering Multiple Quads",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		1024,
		768,
		NULL,
		NULL,
		NULL,
		NULL
	);
	if (!mWindowHandle) return false;

	::ShowWindow(mWindowHandle, SW_SHOW);
	::UpdateWindow(mWindowHandle);

	mIsRunning = true;
	return true;
}

bool AWindow::broadcast() {
	window->onUpdate();

	MSG msg;

	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Sleep(1);

	return true;
}

bool AWindow::release() {
	if (!::DestroyWindow(mWindowHandle)) return false;

	return true;
}

bool AWindow::isRunning() {
	return mIsRunning;
}

RECT AWindow::getWindowRect()
{
	RECT windowRect;
	::GetClientRect(mWindowHandle, &windowRect);
	return windowRect;
}

void AWindow::setWindowHandle(HWND window_handle) {
	mWindowHandle = window_handle;
}

void AWindow::onCreate() {}

void AWindow::onUpdate() {}

void AWindow::onDestroy() {
	mIsRunning = false;
}