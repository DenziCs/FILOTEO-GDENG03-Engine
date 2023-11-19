#include"AppWindow.h"
#include<Windows.h>
#include"imgui.h"
#include"imgui_impl_dx11.h"
#include"imgui_impl_win32.h"
#include"imgui_stdlib.h"
#include"GlobalProperties.h"
#include<iostream>
#include"PhysicsComponent.h"

AppWindow::AppWindow() {}

AppWindow::~AppWindow() {}

void AppWindow::onCreate() {
	AWindow::onCreate();
	GameObjectManager::initialize();
	AGraphicsEngine::getInstance()->initialize();
	mSwapChain = AGraphicsEngine::getInstance()->createSwapChain();

	RECT windowRect = this->getWindowRect();
	UINT width = windowRect.right - windowRect.left;
	UINT height = windowRect.bottom - windowRect.top;
	mSwapChain->initialize(this->mWindowHandle, width, height);

	SystemManager::initialize();

	ACamera* sceneCamera = new ACamera("UnregisteredHyperCam2");
	sceneCamera->setPosition(0.f, -15.f, -10.f);
	sceneCamera->setRotation(0.f, 0.f, 0.f);
	sceneCamera->setPerspectiveProjectionMatrix(1.57f, (float)width / (float)height, 0.1f, 100.f);
	SceneCameraManager::getInstance()->setSceneCamera(sceneCamera);

	void* shaderByteCode = nullptr;
	size_t shaderSize;
	AGraphicsEngine::getInstance()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &shaderSize);
	mVertexShader = AGraphicsEngine::getInstance()->createVertexShader(shaderByteCode, shaderSize);
	GameObjectManager::getInstance()->setVertexShaderProperties(shaderByteCode, shaderSize);

	AGraphicsEngine::getInstance()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shaderByteCode, &shaderSize);
	mPixelShader = AGraphicsEngine::getInstance()->createPixelShader(shaderByteCode, shaderSize);
	AGraphicsEngine::getInstance()->releaseCompiledPixelShader();

	UIManager::initialize(this->mWindowHandle);
}

void AppWindow::onUpdate() {
	AWindow::onUpdate();

	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(
		mSwapChain,
		GlobalProperties::BACKGROUND_COLOR[0],
		GlobalProperties::BACKGROUND_COLOR[1],
		GlobalProperties::BACKGROUND_COLOR[2],
		1.f
	);

	RECT windowRect = this->getWindowRect();
	UINT width = windowRect.right - windowRect.left;
	UINT height = windowRect.bottom - windowRect.top;
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(width, height);

	InputManager::getInstance()->update();
	SceneCameraManager::getInstance()->update();

	GameObjectManager::getInstance()->update();
	SystemManager::getInstance()->update();
	GameObjectManager::getInstance()->draw(width, height, mVertexShader, mPixelShader);
	UIManager::getInstance()->draw();
	mSwapChain->present(false);
}

void AppWindow::onDestroy() {
	AWindow::onDestroy();
	AGraphicsEngine::getInstance()->releaseCompiledVertexShader();
	mSwapChain->release();

	SystemManager::destroy();
	InputManager::destroy();
	SceneCameraManager::destroy();

	mVertexShader->release();
	mPixelShader->release();

	GameObjectManager::destroy();
	UIManager::destroy();
	AGraphicsEngine::getInstance()->release();
}