#include"ATexture.h"
#include<DirectXTex.h>
#include"AGraphicsEngine.h"
#include<iostream>

ATexture::ATexture(const wchar_t* file_path) : AResource::AResource(file_path) {
	DirectX::ScratchImage imageData;
	HRESULT result = DirectX::LoadFromWICFile(file_path, DirectX::WIC_FLAGS_NONE, NULL, imageData);

	if (SUCCEEDED(result)) {
		ID3D11Device* device = AGraphicsEngine::getInstance()->getD3DDevice();
		result = DirectX::CreateTexture(
			device,
			imageData.GetImages(),
			imageData.GetImageCount(),
			imageData.GetMetadata(),
			&mTexture
		);

		D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
		desc.Format = imageData.GetMetadata().format;
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipLevels = (UINT)imageData.GetMetadata().mipLevels;
		desc.Texture2D.MostDetailedMip = 0;

		device->CreateShaderResourceView(mTexture, &desc, &mShaderResource);
	}

	else std::cout << "Could not load texture." << std::endl;
}

ATexture::~ATexture() {
	AResource::~AResource();
	mShaderResource->Release();
	mTexture->Release();
}

std::wstring ATexture::getPath() {
	return this->mFilePath;
}

ID3D11ShaderResourceView* ATexture::getShaderResource() {
	return mShaderResource;
}