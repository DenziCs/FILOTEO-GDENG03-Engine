#pragma once
#include"AGameObject.h"
#include<string>
#include<vector>
#include<unordered_map>
#include"AVertexShader.h"
#include"APixelShader.h"

class GameObjectManager
{
public:

	enum PrimitiveType {
		CUBE,
		PLANE,
		PHYSICS_CUBE,
		PHYSICS_PLANE
	};

	static GameObjectManager* getInstance();
	static void initialize();
	static void destroy();

	AGameObject* findObjectByName(std::string name);
	std::vector<AGameObject*> getAllGameObjects();
	int getObjectCount();
	int getActiveObjectCount();
	void update();
	void draw(int viewport_width, int viewport_height);
	void addObject(AGameObject* game_object);
	void createObject(PrimitiveType primitive_type);
	void deleteObject(AGameObject* game_object);
	void deleteObjectByName(std::string name);

	void setSelectedObject(std::string name);
	void setSelectedObject(AGameObject* game_object);
	AGameObject* getSelectedObject();
	void deselectObject();

	void saveInitialStates();
	void restoreInitialStates();

private:
	GameObjectManager();
	~GameObjectManager();
	GameObjectManager(GameObjectManager const&) {};
	GameObjectManager& operator =(GameObjectManager const&) {};
	static GameObjectManager* instance;

	std::vector<AGameObject*> mGameObjectList;
	std::unordered_map<std::string, AGameObject*> mGameObjectTable;

	AGameObject* mCurrentSelectedObject = nullptr;
};