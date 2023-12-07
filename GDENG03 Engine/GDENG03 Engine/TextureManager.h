#pragma once
#include<unordered_map>
#include<vector>
#include<string>
#include<filesystem>

class ATexture;

class TextureManager
{
public:
	static TextureManager* getInstance();
	static void initialize();
	static void destroy();
	ATexture* getTexture(const wchar_t* file_path);

private:
	static TextureManager* instance;

	TextureManager();
	~TextureManager();
	TextureManager(TextureManager const&) {}
	TextureManager& operator =(TextureManager const&) {}

	std::unordered_map<std::wstring, ATexture*> mTextureTable;
	std::vector<ATexture*> mTextureList;
};