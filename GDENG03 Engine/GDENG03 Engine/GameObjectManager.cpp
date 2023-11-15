#include"GameObjectManager.h"
#include"TimeManager.h"
#include"ACube.h"
#include"APlane.h"
#include"GlobalProperties.h"
#include<iostream>

GameObjectManager* GameObjectManager::instance = nullptr;

GameObjectManager* GameObjectManager::getInstance() {
	return instance;
}

void GameObjectManager::initialize() {
	instance = new GameObjectManager();
}

void GameObjectManager::destroy() {
	instance->mGameObjectTable.clear();

	for (int i = 0; i < instance->mGameObjectList.size(); i++) {
		delete instance->mGameObjectList[i];
	}
}

AGameObject* GameObjectManager::findObjectByName(std::string name) {
	return mGameObjectTable[name];
}

std::vector<AGameObject*> GameObjectManager::getAllGameObjects() {
	return mGameObjectList;
}

int GameObjectManager::getObjectCount() {
	return mGameObjectList.size();
}

int GameObjectManager::getActiveObjectCount() {
	int activeObjectCount = 0;
	for (int i = 0; i < mGameObjectList.size(); i++) {
		if (mGameObjectList[i]->isActive()) activeObjectCount++;
	}
	return activeObjectCount;
}

void GameObjectManager::update() {
	for (int i = 0; i < mGameObjectList.size(); i++) {
		if (mGameObjectList[i]->isActive()) mGameObjectList[i]->update(TimeManager::getDeltaTime());
	}
}

void GameObjectManager::render(int viewport_width, int viewport_height, AVertexShader* vertex_shader, APixelShader* pixel_shader) {
	for (int i = 0; i < mGameObjectList.size(); i++) {
		if (mGameObjectList[i]->isActive()) mGameObjectList[i]->draw(viewport_width, viewport_height, vertex_shader, pixel_shader);
	}
}

void GameObjectManager::addObject(AGameObject* game_object) {
	mGameObjectList.push_back(game_object);
	mGameObjectTable[game_object->getObjectName()] = game_object;
}

void GameObjectManager::createObject(PrimitiveType primitive_type, void* shader_byte_code, size_t shader_size) {
	std::string newName = "";

	switch (primitive_type) {
	case CUBE: {
		int cubeCount = -1;
		AGameObject* cube = nullptr;
		do {
			cubeCount++;
			newName = "Cube " + std::to_string(cubeCount);
			cube = mGameObjectTable[newName];
		}
		while (cube);

		ACube* newCube = new ACube(newName, shader_byte_code, shader_size);
		addObject(newCube);
		std::cout << newCube->getObjectName() << " spawned." << std::endl;
	}
	break;

	case PLANE: {
		int planeCount = -1;
		AGameObject* plane = nullptr;
		do {
			planeCount++;
			newName = "Plane " + std::to_string(planeCount);
			plane = mGameObjectTable[newName];
		}
		while (plane);

		APlane* newPlane = new APlane(newName, shader_byte_code, shader_size);
		addObject(newPlane);
		std::cout << newPlane->getObjectName() << " spawned." << std::endl;
	}
	break;

	}
}

void GameObjectManager::createObject(PrimitiveType primitive_type) {
	std::string newName = "";

	switch (primitive_type) {
	case CUBE: {
		int cubeCount = -1;
		AGameObject* cube = nullptr;
		do {
			cubeCount++;
			newName = "Cube " + std::to_string(cubeCount);
			cube = mGameObjectTable[newName];
		}
		while (cube);

		ACube* newCube = new ACube(newName, mVertexShaderByteCode, mShaderSize);
		addObject(newCube);
		std::cout << newCube->getObjectName() << " spawned." << std::endl;
	}
	break;

	case PLANE: {
		int planeCount = -1;
		AGameObject* plane = nullptr;
		do {
			planeCount++;
			newName = "Plane " + std::to_string(planeCount);
			plane = mGameObjectTable[newName];
		}
		while (plane);

		APlane* newPlane = new APlane(newName, mVertexShaderByteCode, mShaderSize);
		addObject(newPlane);
		std::cout << newPlane->getObjectName() << " spawned." << std::endl;
	}
	break;

	}
}

void GameObjectManager::deleteObject(AGameObject* game_object) {
	std::string key = game_object->getObjectName();
	mGameObjectTable.erase(key);
	mGameObjectList.erase(std::remove(mGameObjectList.begin(), mGameObjectList.end(), game_object), mGameObjectList.end());
	mGameObjectList.shrink_to_fit();
	delete game_object;
}

void GameObjectManager::deleteObjectByName(std::string name) {
	AGameObject* object = findObjectByName(name);
	if (object) deleteObject(object);
}

void GameObjectManager::setSelectedObject(std::string name) {
	if (mCurrentSelectedObject) mCurrentSelectedObject->deselect();
	AGameObject* object = findObjectByName(name);
	if (object) {
		mCurrentSelectedObject = object;
		object->select();
	}
}

void GameObjectManager::setSelectedObject(AGameObject* game_object) {
	if (mCurrentSelectedObject) mCurrentSelectedObject->deselect();
	mCurrentSelectedObject = game_object;
	game_object->select();
}

AGameObject* GameObjectManager::getSelectedObject() {
	return mCurrentSelectedObject;
}

void GameObjectManager::deselectObject() {
	if (mCurrentSelectedObject) {
		mCurrentSelectedObject->deselect();
		mCurrentSelectedObject = nullptr;
	}
}

void GameObjectManager::setVertexShaderProperties(void* shader_byte_code, size_t shader_size) {
	mVertexShaderByteCode = shader_byte_code;
	mShaderSize = shader_size;
}

GameObjectManager::GameObjectManager() {
	mCurrentSelectedObject = nullptr;
}

GameObjectManager::~GameObjectManager() {
	delete instance;
}