#include"AppWindow.h"
#include<Windows.h>
#include<iostream>

AppWindow::AppWindow() {}

AppWindow::~AppWindow() {}

void AppWindow::onCreate() {
	AWindow::onCreate();
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

	for (int i = 0; i < 50; i++) {
		ACube* cube = new ACube("Cube", shaderByteCode, shaderSize);
		cube->setPosition(Randomizer::getRandomFloat(-0.5f, 0.5f), Randomizer::getRandomFloat(-0.5f, 0.5f), Randomizer::getRandomFloat(-0.5f, 0.5f));
		cube->setScale(0.25f, 0.25f, 0.25f);
		cube->setRotationSpeed(2.5f);
		// cube->setRotationSpeed(Randomizer::getRandomFloat(2.f, 3.f));
		mObjectList.push_back(cube);
	}

	AGraphicsEngine::getInstance()->releaseCompiledVertexShader();
	AGraphicsEngine::getInstance()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shaderByteCode, &shaderSize);
	mPixelShader = AGraphicsEngine::getInstance()->createPixelShader(shaderByteCode, shaderSize);
	AGraphicsEngine::getInstance()->releaseCompiledPixelShader();
}

void AppWindow::onUpdate() {
	AWindow::onUpdate();
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(mSwapChain, (154.f/255.f), (216.f/255.f), (216.f/255.f), 1.f);

	RECT windowRect = this->getWindowRect();
	UINT width = windowRect.right - windowRect.left;
	UINT height = windowRect.bottom - windowRect.top;
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(width, height);

	InputManager::getInstance()->update();
	SceneCameraManager::getInstance()->update();

	for (int i = 0; i < mObjectList.size(); i++) {
		mObjectList[i]->update(TimeManager::getDeltaTime());
		mObjectList[i]->draw(width, height, mVertexShader, mPixelShader);
	}

	mSwapChain->present(false);
}

void AppWindow::onDestroy() {
	AWindow::onDestroy();
	mSwapChain->release();

	InputManager::destroy();
	SceneCameraManager::destroy();

	for (int i = 0; i < mObjectList.size(); i++) {
		delete mObjectList[i];
	}

	mVertexShader->release();
	mPixelShader->release();

	AGraphicsEngine::getInstance()->release();
}