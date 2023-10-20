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
	cubeA->setPosition(0.0f, 0.0f, 1.3f);
	cubeA->setScale(0.25f, 0.25f, 0.25f);
	cubeA->setRotationSpeed(5.f);
	mObjectList.push_back(cubeA);

	ACube* cubeB = new ACube("CubeB", shaderByteCode, shaderSize);
	cubeB->setPosition(0.3f, 0.3f, 1.3f);
	cubeB->setScale(0.25f, 0.25f, 0.25f);
	cubeB->setRotationSpeed(4.5f);
	mObjectList.push_back(cubeB);

	ACube* cubeC = new ACube("CubeC", shaderByteCode, shaderSize);
	cubeC->setPosition(-0.35f, -0.35f, 2.35f);
	cubeC->setScale(0.25f, 0.25f, 0.25f);
	cubeC->setRotationSpeed(4.f);
	mObjectList.push_back(cubeC);

	ACube* cubeD = new ACube("CubeD", shaderByteCode, shaderSize);
	cubeD->setPosition(-0.4f, 0.4f, 1.35f);
	cubeD->setScale(0.25f, 0.25f, 0.25f);
	cubeD->setRotationSpeed(3.5f);
	mObjectList.push_back(cubeD);

	ACube* cubeE = new ACube("CubeE", shaderByteCode, shaderSize);
	cubeE->setPosition(0.5f, -0.5f, 0.5f);
	cubeE->setScale(0.25f, 0.25f, 0.25f);
	cubeE->setRotationSpeed(3.f);
	mObjectList.push_back(cubeE);

	ACube* cubeF = new ACube("CubeF", shaderByteCode, shaderSize);
	cubeF->setPosition(-0.65f, -0.65f, 0.65f);
	cubeF->setScale(0.25f, 0.25f, 0.25f);
	cubeF->setRotationSpeed(2.5f);
	mObjectList.push_back(cubeF);

	ACube* cubeG = new ACube("CubeG", shaderByteCode, shaderSize);
	cubeG->setPosition(-0.7f, 0.7f, 0.7f);
	cubeG->setScale(0.25f, 0.25f, 0.25f);
	cubeG->setRotationSpeed(2.f);
	mObjectList.push_back(cubeG);

	ACube* cubeH = new ACube("CubeH", shaderByteCode, shaderSize);
	cubeH->setPosition(0.72f, -0.2f, 0.72f);
	cubeH->setScale(0.25f, 0.25f, 0.25f);
	cubeH->setRotationSpeed(1.75f);
	mObjectList.push_back(cubeH);

	ACube* cubeI = new ACube("CubeI", shaderByteCode, shaderSize);
	cubeI->setPosition(-0.9f, -0.5f, 1.05f);
	cubeI->setScale(0.25f, 0.25f, 0.25f);
	cubeI->setRotationSpeed(1.5f);
	mObjectList.push_back(cubeI);

	ACube* cubeJ = new ACube("CubeJ", shaderByteCode, shaderSize);
	cubeJ->setPosition(0.9f, 0.5f, 0.85f);
	cubeJ->setScale(0.25f, 0.25f, 0.25f);
	cubeJ->setRotationSpeed(1.25f);
	mObjectList.push_back(cubeJ);

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