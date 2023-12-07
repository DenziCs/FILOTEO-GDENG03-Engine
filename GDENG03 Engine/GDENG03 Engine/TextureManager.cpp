#include"TextureManager.h"
#include"ATexture.h"
#include<iostream>

TextureManager* TextureManager::instance = nullptr;

TextureManager* TextureManager::getInstance() {
	return instance;
}

void TextureManager::initialize() {
	instance = new TextureManager();
}

void TextureManager::destroy() {
	delete instance;
}

ATexture* TextureManager::getTexture(const wchar_t* file_path) {
	std::wstring fullPath = std::filesystem::absolute(file_path);

	if (!mTextureTable[file_path]) {
		ATexture* texture = new ATexture(fullPath.c_str());
		mTextureTable[file_path] = texture;
		mTextureList.push_back(texture);
	}

	return mTextureTable[file_path];
}

TextureManager::TextureManager() {}

TextureManager::~TextureManager() {
	mTextureTable.clear();

	while (!mTextureList.empty()) {
		ATexture* texture = mTextureList[0];
		mTextureList.erase(std::remove(mTextureList.begin(), mTextureList.end(), texture), mTextureList.end());
		mTextureList.shrink_to_fit();
		delete texture;

		std::cout << "Textures left: " << mTextureList.size() << std::endl;
	}
}