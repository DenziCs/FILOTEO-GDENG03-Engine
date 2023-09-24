#pragma once
#include"AWindow.h"
#include"AGraphicsEngine.h"
#include"ASwapChain.h"
#include"ADeviceContext.h"
#include"AVertexBuffer.h"
#include"AVertexShader.h"
#include"APixelShader.h"
#include"AShape.h"
#include"Vertex.h"
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
	AVertexShader* mVertexShader;
	APixelShader* mPixelShader;

	std::vector<AShape*> mShapeList;
};