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

	ACube* cubeA = new ACube("CubeA", shaderByteCode, shaderSize);
	cubeA->setPosition(-1.5f, 1.f, -3.f);
	mObjectList.push_back(cubeA);

	ACube* cubeB = new ACube("CubeB", shaderByteCode, shaderSize);
	cubeB->setPosition(0.f, 1.f, 0.f);
	mObjectList.push_back(cubeB);

	ACube* cubeC = new ACube("CubeC", shaderByteCode, shaderSize);
	cubeC->setPosition(2.6f, 1.f, 2.f);
	mObjectList.push_back(cubeC);

	APlane* planeA = new APlane("PlaneA", shaderByteCode, shaderSize);
	planeA->setPosition(0.f, 0.0f, 0.f);
	planeA->setScale(10.f, 1.f, 10.f);
	mObjectList.push_back(planeA);

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