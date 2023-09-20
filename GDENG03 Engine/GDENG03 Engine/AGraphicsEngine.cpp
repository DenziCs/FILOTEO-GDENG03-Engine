#include"AGraphicsEngine.h"
#include"ASwapChain.h"
#include"AVertexBuffer.h"
#include"ADeviceContext.h"

AGraphicsEngine::AGraphicsEngine() {
}

AGraphicsEngine::~AGraphicsEngine() {
}

bool AGraphicsEngine::initialize() {
	D3D_DRIVER_TYPE driverTypes[] = {
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT typeCount = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_0
	};
	UINT featLvCount = ARRAYSIZE(featureLevels);

	HRESULT result = 0;
	for (UINT iType = 0; iType < typeCount;) {
		result = D3D11CreateDevice(
			NULL,
			driverTypes[iType],
			NULL,
			NULL,
			featureLevels,
			featLvCount,
			D3D11_SDK_VERSION,
			&mDevice,
			mFeatureLevel,
			&mInnerImmContext
		);
		if (SUCCEEDED(result)) break;

		++iType;
	}
	if (FAILED(result)) return false;

	mImmediateContext = new ADeviceContext(mInnerImmContext);
	mDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&mdxgiDevice);
	mdxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&mdxgiAdapter);
	mdxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&mdxgiFactory);

	return true;
}

bool AGraphicsEngine::release() {
	mdxgiDevice->Release();
	mdxgiAdapter->Release();
	mdxgiFactory->Release();

	mImmediateContext->release();
	mDevice->Release();

	return true;
}

ASwapChain* AGraphicsEngine::createSwapChain() {
	return new ASwapChain();
}

AVertexBuffer* AGraphicsEngine::createVertexBuffer() {
	return new AVertexBuffer();
}

ADeviceContext* AGraphicsEngine::getImmediateDeviceContext() {
	return mImmediateContext;
}

bool AGraphicsEngine::createShaders() {
	ID3DBlob* errblob = nullptr;
	D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "vsmain", "vs_5_0", NULL, NULL, &mVertexBlob, &errblob);
	D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "psmain", "ps_5_0", NULL, NULL, &mPixelBlob, &errblob);
	mDevice->CreateVertexShader(mVertexBlob->GetBufferPointer(), mVertexBlob->GetBufferSize(), nullptr, &mVertexShader);
	mDevice->CreatePixelShader(mPixelBlob->GetBufferPointer(), mPixelBlob->GetBufferSize(), nullptr, &mPixelShader);

	return true;
}

bool AGraphicsEngine::setShaders() {
	mInnerImmContext->VSSetShader(mVertexShader, nullptr, 0);
	mInnerImmContext->PSSetShader(mPixelShader, nullptr, 0);

	return true;
}

void AGraphicsEngine::getShaderBufferAndSize(void** bytecode, UINT* size) {
	*bytecode = this->mVertexBlob->GetBufferPointer();
	*size = (UINT)this->mVertexBlob->GetBufferSize();
}

AGraphicsEngine* AGraphicsEngine::getInstance() {
	static AGraphicsEngine engine;
	return &engine;
}