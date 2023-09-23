#pragma once
#include<d3d11.h>
#include<d3dcompiler.h>

class ASwapChain;
class ADeviceContext;
class AVertexBuffer;
class AVertexShader;

class AGraphicsEngine
{
public:
	AGraphicsEngine();
	~AGraphicsEngine();

	bool initialize();
	bool release();

	ASwapChain* createSwapChain();
	AVertexBuffer* createVertexBuffer();
	AVertexShader* createVertexShader(const void* shader_byte_code, size_t byte_code_size);
	ADeviceContext* getImmediateDeviceContext();

	bool compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	void releaseCompiledVertexShader();

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

	ID3DBlob* mCustomVertexBlob = nullptr;
	ID3DBlob* mCustomPixelBlob = nullptr;

	friend class ASwapChain;
	friend class AVertexBuffer;
	friend class AVertexShader;
};