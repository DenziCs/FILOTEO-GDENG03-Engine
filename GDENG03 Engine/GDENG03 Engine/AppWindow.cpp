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

	shaderNumbers.worldMatrix.setTranslation(0.f, 0.f, 0.f);
	shaderNumbers.viewMatrix.setIdentity();
	shaderNumbers.projectionMatrix.setOrthoProjection(
		(this->getWindowRect().right - this->getWindowRect().left) / 400.f,
		(this->getWindowRect().bottom - this->getWindowRect().top) / 400.f,
		-4.f,
		4.f
	);

	mMovementSpeed += mMovementSign * 0.5f * TimeManager::getDeltaTime();
	if (mMovementSpeed >= 1.f) {
		mMovementSign = -1.f;
		mMovementSpeed = 1.f;
	}
	if (mMovementSpeed <= 0.f) {
		mMovementSign = 1.f;
		mMovementSpeed = 0.f;
	}
	shaderNumbers.coefficient = mMovementSpeed;

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

	Vertex* currentVertexList = new Vertex[4];

	
	currentVertexList[1] = Vertex(
		Vector3(-0.1f, 0.8f, 0.f),
		Vector3(-0.9f, 0.1f, 0.f),
		Vector3(1.f, 0.f, 0.f),
		Vector3(0.f, 1.f, 1.f)
	);
	currentVertexList[3] = Vertex(
		Vector3(0.75f, 0.75f, 0.f),
		Vector3(-0.83f, -0.4f, 0.f),
		Vector3(0.f, 1.f, 0.f),
		Vector3(1.f, 0.f, 1.f)
	);
	currentVertexList[0] = Vertex(
		Vector3(-0.25f, -0.1f, 0.f),
		Vector3(-0.75f, -0.9f, 0.f),
		Vector3(0.f, 0.f, 1.f),
		Vector3(1.f, 1.f, 0.f)
	);
	currentVertexList[2] = Vertex(
		Vector3(0.1f, -0.8f, 0.f),
		Vector3(1.f, -0.25f, 0.f),
		Vector3(1.f, 1.f, 1.f),
		Vector3(0.f, 0.f, 0.f)
	);

	AShape* quadA = new AShape(currentVertexList, 4, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	mShapeList.push_back(quadA);

	delete[] currentVertexList;

	mVertexBuffer = AGraphicsEngine::getInstance()->createVertexBuffer();
	void* shaderByteCode = nullptr;
	size_t shaderSize;
	AGraphicsEngine::getInstance()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &shaderSize);
	mVertexShader = AGraphicsEngine::getInstance()->createVertexShader(shaderByteCode, shaderSize);

	std::vector<Vertex> vertexVector;
	Vertex* currentSet = nullptr;
	UINT currentCount = 0;
	UINT totalCount = 0;

	for (int i = 0; i < mShapeList.size(); i++) {
		currentSet = mShapeList[i]->getVertexList();
		currentCount = mShapeList[i]->getVertexCount();
		for (int j = 0; j < currentCount; j++) {
			vertexVector.push_back(currentSet[j]);
		}
		totalCount += currentCount;
	}

	Vertex* fullVertexList = new Vertex[totalCount];
	std::copy(vertexVector.begin(), vertexVector.end(), fullVertexList);

	mVertexBuffer->load(fullVertexList, sizeof(Vertex), totalCount, shaderByteCode, shaderSize);
	delete[] fullVertexList;

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

	UINT vertexIndex = 0;

	for (int i = 0; i < mShapeList.size(); i++) {
		AGraphicsEngine::getInstance()->getImmediateDeviceContext()->drawShape(
			mShapeList[i]->getTopology(),
			mShapeList[i]->getVertexCount(),
			vertexIndex
		);
		vertexIndex += mShapeList[i]->getVertexCount();
	}

	mSwapChain->present(false);
}

void AppWindow::onDestroy() {
	AWindow::onDestroy();
	mVertexBuffer->release();
	mConstantBuffer->release();
	mSwapChain->release();

	for (int i = 0; i < mShapeList.size(); i++) {
		delete mShapeList[i];
	}

	mVertexShader->release();
	mPixelShader->release();

	AGraphicsEngine::getInstance()->release();
}