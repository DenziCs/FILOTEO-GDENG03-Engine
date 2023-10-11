#pragma once
#include"AWindow.h"
#include"AGraphicsEngine.h"
#include"InputManager.h"
#include"ASwapChain.h"
#include"ADeviceContext.h"
#include"AVertexBuffer.h"
#include"AIndexBuffer.h"
#include"AConstantBuffer.h"
#include"AVertexShader.h"
#include"APixelShader.h"
#include"AShape.h"
#include"AGameObject.h"
#include"ACube.h"
#include"Vertex.h"
#include"Matrix4x4.h"
#include<vector>

class AppWindow : public AWindow
{
public:
	AppWindow();
	~AppWindow();

	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

private:
	ASwapChain* mSwapChain;
	AVertexBuffer* mVertexBuffer;
	AIndexBuffer* mIndexBuffer;
	AConstantBuffer* mConstantBuffer;
	AVertexShader* mVertexShader;
	APixelShader* mPixelShader;

	std::vector<AGameObject*> mObjectList;
};