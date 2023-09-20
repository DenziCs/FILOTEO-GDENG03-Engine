#include"AVertexBuffer.h"
#include"AGraphicsEngine.h"

AVertexBuffer::AVertexBuffer() : mBuffer(0), mLayout(0) {}

AVertexBuffer::~AVertexBuffer() {}

bool AVertexBuffer::load(void* vertex_list, UINT vertex_size, UINT vertex_count, void* shader_byte_code, UINT shader_byte_size) {
	if (mBuffer) mBuffer->Release();
	if (mLayout) mLayout->Release();

	D3D11_BUFFER_DESC buffer_desc = {};
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.ByteWidth = vertex_size * vertex_count;
	buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buffer_desc.CPUAccessFlags = 0;
	buffer_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = vertex_list;

	mVertexSize = vertex_size;
	mVertexCount = vertex_count;
	
	HRESULT result = AGraphicsEngine::getInstance()->mDevice->CreateBuffer(&buffer_desc, &init_data, &mBuffer);
	if (FAILED(result)) return false;

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		"POSITION",
		0,
		DXGI_FORMAT_R32G32B32_FLOAT,
		0,
		0,
		D3D11_INPUT_PER_VERTEX_DATA,
		0
	};
	UINT layoutSize = ARRAYSIZE(layout);
	result = AGraphicsEngine::getInstance()->mDevice->CreateInputLayout(layout, layoutSize, shader_byte_code, shader_byte_size, &mLayout);
	if (FAILED(result)) return false;

	return true;
}

UINT AVertexBuffer::getVertexCount() {
	return mVertexCount;
}

bool AVertexBuffer::release() {
	mLayout->Release();
	mBuffer->Release();
	delete this;
	return true;
}