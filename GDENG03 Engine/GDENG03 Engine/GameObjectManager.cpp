#include"GameObjectManager.h"
#include"TimeManager.h"
#include"ACube.h"
#include"APlane.h"
#include"GlobalProperties.h"
#include<iostream>
#include"PhysicsComponent.h"
#include"SystemManager.h"
#include"PhysicsSystem.h"

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

void GameObjectManager::draw(int viewport_width, int viewport_height) {
	for (int i = 0; i < mGameObjectList.size(); i++) {
		if (mGameObjectList[i]->isActive()) mGameObjectList[i]->draw(viewport_width, viewport_height);
	}
}

void GameObjectManager::addObject(AGameObject* game_object) {
	mGameObjectList.push_back(game_object);
	mGameObjectTable[game_object->getObjectName()] = game_object;
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

		ACube* newCube = new ACube(newName);
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

		APlane* newPlane = new APlane(newName);
		addObject(newPlane);
		std::cout << newPlane->getObjectName() << " spawned." << std::endl;
	}
	break;

	case PHYSICS_CUBE: {
		int cubeCount = -1;
		AGameObject* cube = nullptr;
		do {
			cubeCount++;
			newName = "Physics Cube " + std::to_string(cubeCount);
			cube = mGameObjectTable[newName];
		}
		while (cube);

		ACube* newCube = new ACube(newName);
		newCube->setPosition(0.f, 10.f, 0.f);
		addObject(newCube);
		std::cout << newCube->getObjectName() << " spawned." << std::endl;

		PhysicsComponent* component = new PhysicsComponent(newName + " Physics");
		newCube->attachComponent(component);
		component->getRigidBody()->enableGravity(true);
		std::cout << component->getComponentName() << " attached." << std::endl;
	}
	break;

	case PHYSICS_PLANE: {
		int planeCount = -1;
		AGameObject* plane = nullptr;
		do {
			planeCount++;
			newName = "Physics Plane " + std::to_string(planeCount);
			plane = mGameObjectTable[newName];
		}
		while (plane);

		APlane* newPlane = new APlane(newName);
		newPlane->setPosition(0.f, 0.f, 0.f);
		newPlane->setScale(10.f, 1.f, 10.f);
		addObject(newPlane);
		std::cout << newPlane->getObjectName() << " spawned." << std::endl;

		PhysicsComponent* component = new PhysicsComponent(newName + " Physics");
		newPlane->attachComponent(component);
		component->getRigidBody()->setType(BodyType::STATIC);
		std::cout << component->getComponentName() << " attached." << std::endl;
	}
	break;

	}
}

void GameObjectManager::deleteObject(AGameObject* game_object) {
	if (game_object == mCurrentSelectedObject) deselectObject();

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

void GameObjectManager::saveInitialStates() {
	for (int i = 0; i < mGameObjectList.size(); i++) {
		if (mGameObjectList[i]->isActive()) mGameObjectList[i]->saveInitialState();
	}
}

void GameObjectManager::restoreInitialStates() {
	for (int i = 0; i < mGameObjectList.size(); i++) {
		if (mGameObjectList[i]->isActive()) mGameObjectList[i]->restoreInitialState();
	}
}

GameObjectManager::GameObjectManager() {
	mCurrentSelectedObject = nullptr;
}

GameObjectManager::~GameObjectManager() {
	delete instance;
}