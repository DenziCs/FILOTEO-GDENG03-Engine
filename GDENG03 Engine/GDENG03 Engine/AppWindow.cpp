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

	Vertex* currentVertexList = new Vertex[4];

	currentVertexList[0] = Vertex(-0.75f, 0.75f, 0.f);
	currentVertexList[1] = Vertex(-0.25f, 0.75f, 0.f);
	currentVertexList[2] = Vertex(-0.75f, 0.25f, 0.f);
	currentVertexList[3] = Vertex(-0.25f, 0.25f, 0.f);
	AShape* quadA = new AShape(currentVertexList, 4, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	mShapeList.push_back(quadA);

	currentVertexList[0] = Vertex(0.25f, 0.75f, 0.f);
	currentVertexList[1] = Vertex(0.75f, 0.75f, 0.f);
	currentVertexList[2] = Vertex(0.25f, 0.25f, 0.f);
	currentVertexList[3] = Vertex(0.75f, 0.25f, 0.f);
	AShape* quadB = new AShape(currentVertexList, 4, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	mShapeList.push_back(quadB);

	currentVertexList[0] = Vertex(-0.75f, -0.25f, 0.f);
	currentVertexList[1] = Vertex(-0.25f, -0.25f, 0.f);
	currentVertexList[2] = Vertex(-0.75f, -0.75f, 0.f);
	currentVertexList[3] = Vertex(-0.25f, -0.75f, 0.f);
	AShape* quadC = new AShape(currentVertexList, 4, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	mShapeList.push_back(quadC);

	delete[] currentVertexList;

	mVertexBuffer = AGraphicsEngine::getInstance()->createVertexBuffer();
	void* shaderByteCode = nullptr;
	size_t shaderSize;
	AGraphicsEngine::getInstance()->createShaders();
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
}

void AppWindow::onUpdate() {
	AWindow::onUpdate();
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(mSwapChain, (154.f/256.f), (215.f/256.f), (216.f/256.f), 1.f);

	RECT windowRect = this->getWindowRect();
	UINT width = windowRect.right - windowRect.left;
	UINT height = windowRect.bottom - windowRect.top;
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(width, height);

	AGraphicsEngine::getInstance()->setShaders();
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(mVertexShader);
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
	mSwapChain->release();

	for (int i = 0; i < mShapeList.size(); i++) {
		delete mShapeList[i];
	}

	AGraphicsEngine::getInstance()->release();
}