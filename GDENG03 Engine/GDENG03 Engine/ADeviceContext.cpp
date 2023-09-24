#include"ADeviceContext.h"
#include"ASwapChain.h"
#include"AVertexBuffer.h"
#include"AVertexShader.h"
#include"APixelShader.h"

ADeviceContext::ADeviceContext(ID3D11DeviceContext* device_context) {
	mDeviceContext = device_context;
}

ADeviceContext::~ADeviceContext() {}

void ADeviceContext::clearRenderTargetColor(ASwapChain* swap_chain, float red, float green, float blue, float alpha) {
	FLOAT clearColor[] = { red, green, blue, alpha };
	mDeviceContext->ClearRenderTargetView(swap_chain->mRenderTargetView, clearColor);
	mDeviceContext->OMSetRenderTargets(1, &(swap_chain->mRenderTargetView), NULL);
}

void ADeviceContext::setVertexBuffer(AVertexBuffer* vertex_buffer) {
	UINT stride = vertex_buffer->mVertexSize;
	UINT offset = 0;
	mDeviceContext->IASetVertexBuffers(0, 1, &(vertex_buffer->mBuffer), &stride, &offset);
	mDeviceContext->IASetInputLayout(vertex_buffer->mLayout);
}

void ADeviceContext::setViewportSize(UINT width, UINT height) {
	D3D11_VIEWPORT viewport = {};
	viewport.Width = width;
	viewport.Height = height;
	viewport.MinDepth = 0.f;
	viewport.MaxDepth = 1.f;
	mDeviceContext->RSSetViewports(1, &viewport);
}

void ADeviceContext::setVertexShader(AVertexShader* vertex_shader) {
	mDeviceContext->VSSetShader(vertex_shader->mVertexShader, nullptr, 0);
}

void ADeviceContext::setPixelShader(APixelShader* pixel_shader) {
	mDeviceContext->PSSetShader(pixel_shader->mPixelShader, nullptr, 0);
}

void ADeviceContext::drawTriangleList(UINT vertex_count, UINT initial_vertex_index) {
	mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	mDeviceContext->Draw(vertex_count, initial_vertex_index);
}

void ADeviceContext::drawTriangleStrip(UINT vertex_count, UINT initial_vertex_index) {
	mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	mDeviceContext->Draw(vertex_count, initial_vertex_index);
}

void ADeviceContext::drawShape(D3D_PRIMITIVE_TOPOLOGY topology_type, UINT vertex_count, UINT initial_vertex_index) {
	mDeviceContext->IASetPrimitiveTopology(topology_type);
	mDeviceContext->Draw(vertex_count, initial_vertex_index);
}

bool ADeviceContext::release() {
	mDeviceContext->Release();
	delete this;
	return true;
}