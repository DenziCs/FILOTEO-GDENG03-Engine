#pragma once
#include<d3d11.h>
#include<d3dcompiler.h>

class ASwapChain;
class ADeviceContext;
class AVertexBuffer;

class AGraphicsEngine
{
public:
	AGraphicsEngine();
	~AGraphicsEngine();

	bool initialize();
	bool release();

	ASwapChain* createSwapChain();
	AVertexBuffer* createVertexBuffer();
	ADeviceContext* getImmediateDeviceContext();

	bool createShaders();
	bool setShaders();
	void getShaderBufferAndSize(void** bytecode, UINT* size);

public:
	static AGraphicsEngine* getInstance();

protected:
	ID3D11Device* mDevice;
	D3D_FEATURE_LEVEL* mFeatureLevel;
	ADeviceContext* mImmediateContext;

	IDXGIDevice* mdxgiDevice;
	IDXGIAdapter* mdxgiAdapter;
	IDXGIFactory* mdxgiFactory;
	ID3D11DeviceContext* mInnerImmContext;

	ID3DBlob* mVertexBlob = nullptr;
	ID3DBlob* mPixelBlob = nullptr;
	ID3D11VertexShader* mVertexShader = nullptr;
	ID3D11PixelShader* mPixelShader = nullptr;

	friend class ASwapChain;
	friend class AVertexBuffer;
};