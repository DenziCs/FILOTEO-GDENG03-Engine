#pragma once
#include<d3d11.h>
#include"Vertex.h"

class ADeviceContext;

class AVertexBuffer
{
public:
	AVertexBuffer();
	~AVertexBuffer();

	bool load(void* vertex_list, UINT vertex_size, UINT vertex_count, void* shader_byte_code, UINT shader_byte_size);
	UINT getVertexCount();
	bool release();

private:
	UINT mVertexSize;
	UINT mVertexCount;
	ID3D11Buffer* mBuffer;
	ID3D11InputLayout* mLayout;

	friend class ADeviceContext;
};