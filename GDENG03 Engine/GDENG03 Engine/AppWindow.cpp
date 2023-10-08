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

void AppWindow::updateObjectPosition() {
	constant shaderNumbers;

	Matrix4x4 rotator;
	mMovementSpeed += mMovementSign * 0.1f * TimeManager::getDeltaTime();

	if (mMovementSpeed >= 1.f) {
		mMovementSign = -1.f;
		mMovementSpeed = 1.f;
	}
	if (mMovementSpeed <= 0.f) {
		mMovementSign = 1.f;
		mMovementSpeed = 0.f;
	}
	shaderNumbers.coefficient = mMovementSpeed;

	shaderNumbers.worldMatrix.setIdentity();

	mTheta += 1.82f * TimeManager::getDeltaTime();

	/*
	rotator.setIdentity();
	rotator.setRotationZ(mTheta);
	shaderNumbers.worldMatrix *= rotator;

	rotator.setIdentity();
	rotator.setRotationY(mTheta);
	shaderNumbers.worldMatrix *= rotator;

	rotator.setIdentity();
	rotator.setRotationX(mTheta);
	shaderNumbers.worldMatrix *= rotator;
	*/
	shaderNumbers.worldMatrix.rotate(2, mTheta);
	shaderNumbers.worldMatrix.rotate(1, mTheta);
	shaderNumbers.worldMatrix.rotate(0, mTheta);
	
	shaderNumbers.viewMatrix.setIdentity();
	shaderNumbers.projectionMatrix.setOrthoProjection(
		(this->getWindowRect().right - this->getWindowRect().left) / 400.f,
		(this->getWindowRect().bottom - this->getWindowRect().top) / 400.f,
		-4.f,
		4.f
	);

	mConstantBuffer->update(AGraphicsEngine::getInstance()->getImmediateDeviceContext(), &shaderNumbers);
}

void AppWindow::onCreate() {
	AWindow::onCreate();
	AGraphicsEngine::getInstance()->initialize();
	mSwapChain = AGraphicsEngine::getInstance()->createSwapChain();

	RECT windowRect = this->getWindowRect();
	UINT width = windowRect.right - windowRect.left;
	UINT height = windowRect.bottom - windowRect.top;
	mSwapChain->initialize(this->mWindowHandle, width, height);
	
	Vertex* currentVertexList = new Vertex[8];
	
	currentVertexList[0] = Vertex(
		Vector3(-0.5f, -0.5f, -0.5f),
		Vector3(1.f, 0.f, 0.f),
		Vector3(0.f, 1.f, 1.f)
	);
	currentVertexList[1] = Vertex(
		Vector3(-0.5f, 0.5f, -0.5f),
		Vector3(0.f, 1.f, 0.f),
		Vector3(1.f, 0.f, 1.f)
	);
	currentVertexList[2] = Vertex(
		Vector3(0.5f, 0.5f, -0.5f),
		Vector3(0.f, 0.f, 1.f),
		Vector3(1.f, 1.f, 0.f)
	);
	currentVertexList[3] = Vertex(
		Vector3(0.5f, -0.5f, -0.5f),
		Vector3(1.f, 1.f, 1.f),
		Vector3(0.f, 0.f, 0.f)
	);
	currentVertexList[4] = Vertex(
		Vector3(0.5f, -0.5f, 0.5f),
		Vector3(1.f, 0.f, 0.f),
		Vector3(0.f, 1.f, 1.f)
	);
	currentVertexList[5] = Vertex(
		Vector3(0.5f, 0.5f, 0.5f),
		Vector3(0.f, 1.f, 0.f),
		Vector3(1.f, 0.f, 1.f)
	);
	currentVertexList[6] = Vertex(
		Vector3(-0.5f, 0.5f, 0.5f),
		Vector3(0.f, 0.f, 1.f),
		Vector3(1.f, 1.f, 0.f)
	);
	currentVertexList[7] = Vertex(
		Vector3(-0.5f, -0.5f, 0.5f),
		Vector3(1.f, 1.f, 1.f),
		Vector3(0.f, 0.f, 0.f)
	);

	unsigned int indexList[] = {
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		6, 7, 4,
		1, 6, 5,
		5, 2, 1,
		7, 0, 3,
		3, 4, 7,
		3, 2, 5,
		5, 4, 3,
		7, 6, 1,
		1, 0, 7
	};

	mVertexBuffer = AGraphicsEngine::getInstance()->createVertexBuffer();
	void* shaderByteCode = nullptr;
	size_t shaderSize;
	AGraphicsEngine::getInstance()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &shaderSize);
	mVertexShader = AGraphicsEngine::getInstance()->createVertexShader(shaderByteCode, shaderSize);

	mIndexBuffer = AGraphicsEngine::getInstance()->createIndexBuffer();
	mIndexBuffer->load(indexList, ARRAYSIZE(indexList));

	mVertexBuffer->load(currentVertexList, sizeof(Vertex), 8, shaderByteCode, shaderSize);
	delete[] currentVertexList;

	AGraphicsEngine::getInstance()->releaseCompiledVertexShader();

	AGraphicsEngine::getInstance()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shaderByteCode, &shaderSize);
	mPixelShader = AGraphicsEngine::getInstance()->createPixelShader(shaderByteCode, shaderSize);
	AGraphicsEngine::getInstance()->releaseCompiledPixelShader();

	constant clockCount;
	clockCount.coefficient = 0.f;

	mConstantBuffer = AGraphicsEngine::getInstance()->createConstantBuffer();
	mConstantBuffer->load(&clockCount, sizeof(constant));
}

void AppWindow::onUpdate() {
	AWindow::onUpdate();
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(mSwapChain, (154.f/256.f), (215.f/256.f), (216.f/256.f), 1.f);

	RECT windowRect = this->getWindowRect();
	UINT width = windowRect.right - windowRect.left;
	UINT height = windowRect.bottom - windowRect.top;
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(width, height);

	updateObjectPosition();

	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(mConstantBuffer, mVertexShader);
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(mConstantBuffer, mPixelShader);

	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(mVertexShader);
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(mPixelShader);
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(mVertexBuffer);
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setIndexBuffer(mIndexBuffer);

	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->drawIndexedTriangleList(mIndexBuffer->getIndexCount(), 0, 0);

	mSwapChain->present(false);
}

void AppWindow::onDestroy() {
	AWindow::onDestroy();
	mVertexBuffer->release();
	mIndexBuffer->release();
	mConstantBuffer->release();
	mSwapChain->release();

	for (int i = 0; i < mShapeList.size(); i++) {
		delete mShapeList[i];
	}

	mVertexShader->release();
	mPixelShader->release();

	AGraphicsEngine::getInstance()->release();
}