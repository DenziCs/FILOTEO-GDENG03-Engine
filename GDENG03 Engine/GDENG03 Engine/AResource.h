#pragma once
#include<string>

class AResource
{
public:
	AResource(const wchar_t* file_path);
	virtual ~AResource() {}

protected:
	std::wstring mFilePath;
};