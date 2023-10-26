#include"AppWindow.h"
#include<Windows.h>
#include"imgui.h"
#include"imgui_impl_dx11.h"
#include"imgui_impl_win32.h"
#include"imgui_stdlib.h"
#include"GlobalProperties.h"
#include<iostream>

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

	ACamera* sceneCamera = new ACamera("UnregisteredHyperCam2");
	sceneCamera->setPosition(0.f, 0.f, 0.f);
	sceneCamera->setRotation(0.f, 0.f, 0.f);
	sceneCamera->setPerspectiveProjectionMatrix(1.57f, (float)width / (float)height, 0.1f, 100.f);
	SceneCameraManager::getInstance()->setSceneCamera(sceneCamera);

	void* shaderByteCode = nullptr;
	size_t shaderSize;
	AGraphicsEngine::getInstance()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &shaderSize);
	mVertexShader = AGraphicsEngine::getInstance()->createVertexShader(shaderByteCode, shaderSize);

	for (int i = 0; i < 10; i++) {
		GameObjectManager::getInstance()->createObject(GameObjectManager::CUBE, shaderByteCode, shaderSize);
		ACube* object = (ACube*)GameObjectManager::getInstance()->findObjectByName("Cube " + std::to_string(i));
		if (object) {
			object->setScale(0.25f, 0.25f, 0.25f);
			object->setRotationSpeed(Randomizer::getRandomFloat(1.f, 5.f));
			object->setPosition(Randomizer::getRandomFloat(-1.f, 1.f), Randomizer::getRandomFloat(-1.f, 1.f), Randomizer::getRandomFloat(-1.f, 1.f));
		}
	}
	GameObjectManager::getInstance()->createObject(GameObjectManager::PLANE, shaderByteCode, shaderSize);

	AGraphicsEngine::getInstance()->releaseCompiledVertexShader();
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
	GameObjectManager::getInstance()->render(width, height, mVertexShader, mPixelShader);
	UIManager::getInstance()->draw();
	mSwapChain->present(false);
}

void AppWindow::onDestroy() {
	AWindow::onDestroy();
	mSwapChain->release();

	InputManager::destroy();
	SceneCameraManager::destroy();

	mVertexShader->release();
	mPixelShader->release();

	GameObjectManager::destroy();
	UIManager::destroy();
	AGraphicsEngine::getInstance()->release();
}