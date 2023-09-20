#include"AppWindow.h"

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

	AQuad* quadA = new AQuad(
		Vertex(-0.75f, 0.75f, 0.f),
		Vertex(-0.25f, 0.75f, 0.f),
		Vertex(-0.75f, 0.25f, 0.f),
		Vertex(-0.25f, 0.25f, 0.f)
	);
	mPrimitiveList.push_back(quadA);

	AQuad* quadB = new AQuad(
		Vertex(0.25f, 0.75f, 0.f),
		Vertex(0.75f, 0.75f, 0.f),
		Vertex(0.25f, 0.25f, 0.f),
		Vertex(0.75f, 0.25f, 0.f)
	);
	mPrimitiveList.push_back(quadB);

	AQuad* quadC = new AQuad(
		Vertex(-0.75f, -0.25f, 0.f),
		Vertex(-0.25f, -0.25f, 0.f),
		Vertex(-0.75f, -0.75f, 0.f),
		Vertex(-0.25f, -0.75f, 0.f)
	);
	mPrimitiveList.push_back(quadC);

	mVertexBuffer = AGraphicsEngine::getInstance()->createVertexBuffer();
	void* shaderByteCode = nullptr;
	UINT shaderSize;
	AGraphicsEngine::getInstance()->createShaders();
	AGraphicsEngine::getInstance()->getShaderBufferAndSize(&shaderByteCode, &shaderSize);

	std::vector<Vertex> vertexVector;
	Vertex* currentSet = nullptr;
	int currentCount = 0;
	int totalCount = 0;

	for (int i = 0; i < mPrimitiveList.size(); i++) {
		currentSet = mPrimitiveList[i]->getVertexList(&currentCount);
		for (int j = 0; j < currentCount; j++) {
			vertexVector.push_back(currentSet[j]);
		}
		totalCount += currentCount;
	}

	Vertex* fullVertexList = new Vertex[totalCount];
	std::copy(vertexVector.begin(), vertexVector.end(), fullVertexList);

	mVertexBuffer->load(fullVertexList, sizeof(Vertex), totalCount, shaderByteCode, shaderSize);
	delete[] fullVertexList;
}

void AppWindow::onUpdate() {
	AWindow::onUpdate();
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(mSwapChain, (154.f/256.f), (215.f/256.f), (216.f/256.f), 1.f);

	RECT windowRect = this->getWindowRect();
	UINT width = windowRect.right - windowRect.left;
	UINT height = windowRect.bottom - windowRect.top;
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(width, height);

	AGraphicsEngine::getInstance()->setShaders();
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(mVertexBuffer);
	// AGraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleList(mVertexBuffer->getVertexCount(), 0);

	UINT vertexIndex = 0;
	for (int i = 0; i < mPrimitiveList.size(); i++) {
		mPrimitiveList[i]->drawShape(&vertexIndex);
	}

	mSwapChain->present(false);
}

void AppWindow::onDestroy() {
	AWindow::onDestroy();
	mVertexBuffer->release();
	mSwapChain->release();

	for (int i = 0; i < mPrimitiveList.size(); i++) {
		delete mPrimitiveList[i];
	}

	AGraphicsEngine::getInstance()->release();
}