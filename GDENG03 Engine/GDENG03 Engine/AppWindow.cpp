#include"AppWindow.h"
#include<Windows.h>
#include<iostream>

__declspec(align(16))
struct constant {
	Matrix4x4 worldMatrix;
	Matrix4x4 viewMatrix;
	Matrix4x4 projectionMatrix;
	float coefficient;
};

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

	void* shaderByteCode = nullptr;
	size_t shaderSize;
	AGraphicsEngine::getInstance()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &shaderSize);
	mVertexShader = AGraphicsEngine::getInstance()->createVertexShader(shaderByteCode, shaderSize);

	ACube* cubeA = new ACube("CubeA", shaderByteCode, shaderSize);
	cubeA->setScale(0.25f, 0.25f, 0.25f);
	cubeA->setAnimationSpeed(5.f);
	mObjectList.push_back(cubeA);

	ACube* cubeB = new ACube("CubeB", shaderByteCode, shaderSize);
	cubeB->setPosition(0.3f, 0.3f, 0.3f);
	cubeB->setScale(0.25f, 0.25f, 0.25f);
	cubeB->setAnimationSpeed(4.5f);
	mObjectList.push_back(cubeB);

	ACube* cubeC = new ACube("CubeC", shaderByteCode, shaderSize);
	cubeC->setPosition(-0.35f, -0.35f, -0.35f);
	cubeC->setScale(0.25f, 0.25f, 0.25f);
	cubeC->setAnimationSpeed(4.f);
	mObjectList.push_back(cubeC);

	ACube* cubeD = new ACube("CubeD", shaderByteCode, shaderSize);
	cubeD->setPosition(-0.4f, 0.4f, 0.35f);
	cubeD->setScale(0.25f, 0.25f, 0.25f);
	cubeD->setAnimationSpeed(3.5f);
	mObjectList.push_back(cubeD);

	ACube* cubeE = new ACube("CubeE", shaderByteCode, shaderSize);
	cubeE->setPosition(0.5f, -0.5f, -0.5f);
	cubeE->setScale(0.25f, 0.25f, 0.25f);
	cubeE->setAnimationSpeed(3.f);
	mObjectList.push_back(cubeE);

	ACube* cubeF = new ACube("CubeF", shaderByteCode, shaderSize);
	cubeF->setPosition(-0.65f, -0.65f, 0.65f);
	cubeF->setScale(0.25f, 0.25f, 0.25f);
	cubeF->setAnimationSpeed(2.5f);
	mObjectList.push_back(cubeF);

	ACube* cubeG = new ACube("CubeG", shaderByteCode, shaderSize);
	cubeG->setPosition(-0.7f, 0.7f, -0.7f);
	cubeG->setScale(0.25f, 0.25f, 0.25f);
	cubeG->setAnimationSpeed(2.f);
	mObjectList.push_back(cubeG);

	ACube* cubeH = new ACube("CubeH", shaderByteCode, shaderSize);
	cubeH->setPosition(0.72f, -0.2f, -0.72f);
	cubeH->setScale(0.25f, 0.25f, 0.25f);
	cubeH->setAnimationSpeed(1.75f);
	mObjectList.push_back(cubeH);

	ACube* cubeI = new ACube("CubeI", shaderByteCode, shaderSize);
	cubeI->setPosition(-0.9f, -0.5f, 0.35f);
	cubeI->setScale(0.25f, 0.25f, 0.25f);
	cubeI->setAnimationSpeed(1.5f);
	mObjectList.push_back(cubeI);

	ACube* cubeJ = new ACube("CubeJ", shaderByteCode, shaderSize);
	cubeJ->setPosition(0.9f, 0.5f, -0.35f);
	cubeJ->setScale(0.25f, 0.25f, 0.25f);
	cubeJ->setAnimationSpeed(1.25f);
	mObjectList.push_back(cubeJ);

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

	for (int i = 0; i < mObjectList.size(); i++) {
		delete mObjectList[i];
	}

	mVertexShader->release();
	mPixelShader->release();

	AGraphicsEngine::getInstance()->release();
}