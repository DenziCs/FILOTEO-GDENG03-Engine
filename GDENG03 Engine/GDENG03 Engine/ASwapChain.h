#pragma once
#include<d3d11.h>

class ADeviceChain;

class ASwapChain
{
public:
	ASwapChain();
	~ASwapChain();

	bool initialize(HWND window_handle, UINT window_width, UINT window_height);
	bool release();
	bool present(bool vsync);

protected:
	IDXGISwapChain* mSwapChain;
	ID3D11RenderTargetView* mRenderTargetView;

	friend class ADeviceContext;
};