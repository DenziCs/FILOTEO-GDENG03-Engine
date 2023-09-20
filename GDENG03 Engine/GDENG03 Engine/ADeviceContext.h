#pragma once
#include<d3d11.h>

class ASwapChain;
class AVertexBuffer;

class ADeviceContext
{
public:
	ADeviceContext(ID3D11DeviceContext* device_context);
	~ADeviceContext();

	void clearRenderTargetColor(ASwapChain* swap_chain, float red, float green, float blue, float alpha);
	void setVertexBuffer(AVertexBuffer* vertex_buffer);
	void setViewportSize(UINT width, UINT height);
	void drawTriangleList(UINT vertex_count, UINT initial_vertex_index);
	void drawTriangleStrip(UINT vertex_count, UINT initial_vertex_index);
	bool release();

protected:
	ID3D11DeviceContext* mDeviceContext;
};