#include"ASwapChain.h"
#include"AGraphicsEngine.h"

ASwapChain::ASwapChain() {}

ASwapChain::~ASwapChain() {}

bool ASwapChain::initialize(HWND window_handle, UINT window_width, UINT window_height) {
	ID3D11Device* device = AGraphicsEngine::getInstance()->mDevice;

	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = window_width;
	desc.BufferDesc.Height = window_height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = window_handle;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;

	HRESULT result = AGraphicsEngine::getInstance()->mdxgiFactory->CreateSwapChain(device, &desc, &mSwapChain);
	if (FAILED(result)) return false;

	ID3D11Texture2D* buffer = NULL;
	result = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);
	if (FAILED(result)) return false;

	result = device->CreateRenderTargetView(buffer, NULL, &mRenderTargetView);
	buffer->Release();
	if (FAILED(result)) return false;

	return true;
}

bool ASwapChain::release() {
	mSwapChain->Release();
	delete this;
	return true;
}

bool ASwapChain::present(bool vsync) {
	mSwapChain->Present(vsync, NULL);
	return true;
}