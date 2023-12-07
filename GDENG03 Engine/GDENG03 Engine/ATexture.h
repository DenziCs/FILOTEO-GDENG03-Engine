#pragma once
#include"AResource.h"
#include<d3d11.h>

class ATexture : public AResource
{
public:
	ATexture(const wchar_t* file_path);
	~ATexture();
	std::wstring getPath();
	ID3D11ShaderResourceView* getShaderResource();

private:
	ID3D11Resource* mTexture = NULL;
	ID3D11ShaderResourceView* mShaderResource = NULL;
};