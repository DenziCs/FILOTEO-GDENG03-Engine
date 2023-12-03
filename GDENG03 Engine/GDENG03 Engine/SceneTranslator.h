#pragma once
#include<string>
#include<iostream>
#include<fstream>

class SceneTranslator
{
public:
	static void saveScene(std::string file_path);
	static void openScene(std::string file_path);
};