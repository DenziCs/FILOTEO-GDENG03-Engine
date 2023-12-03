#include"SceneTranslator.h"
#include"GameObjectManager.h"
#include"StringUtilities.h"
#include"PhysicsComponent.h"

void SceneTranslator::saveScene(std::string file_path) {
	std::string filePath = "";
	if (file_path.find(".iet") != std::string::npos) filePath = file_path;
	else filePath = file_path + ".iet";

	std::ofstream sceneFile;
	sceneFile.open(filePath, std::ios::out);

	std::cout << filePath << std::endl;

	std::vector<AGameObject*> objectList = GameObjectManager::getInstance()->getAllGameObjects();
	PhysicsComponent* physics = nullptr;
	AComponent* component = nullptr;

	for (int i = 0; i < objectList.size(); i++) {
		sceneFile << objectList[i]->getObjectName() << std::endl;
		sceneFile << "Type: " << objectList[i]->getObjectType() << std::endl;

		Vector3D position = objectList[i]->getLocalPosition();
		sceneFile << "Position: " << position.x << " " << position.y << " " << position.z << std::endl;

		Vector3D rotation = objectList[i]->getLocalRotation();
		sceneFile << "Rotation: " << rotation.x << " " << rotation.y << " " << rotation.z << std::endl;

		Vector3D scale = objectList[i]->getLocalScale();
		sceneFile << "Scale: " << scale.x << " " << scale.y << " " << scale.z << std::endl;

		if (objectList[i]->isActive()) sceneFile << "Enabled: 1" << std::endl;
		else sceneFile << "Enabled: 0" << std::endl;

		component = objectList[i]->findComponentOfType(AComponent::PHYSICS);
		if (component) {
			sceneFile << "Physics: 1" << std::endl;
			physics = (PhysicsComponent*)component;

			/*
			if (physics->isActive()) sceneFile << "Active: 1" << std::endl;
			else sceneFile << "Active: 0" << std::endl;

			if (physics->isStatic()) sceneFile << "Static: 1" << std::endl;
			else sceneFile << "Static: 0" << std::endl;

			if (physics->isGravityEnabled()) sceneFile << "Gravity: 1" << std::endl;
			else sceneFile << "Gravity: 0" << std::endl;
			*/

			sceneFile << "Active: " << physics->isActive() << std::endl;
			sceneFile << "Static: " << physics->isStatic() << std::endl;
			sceneFile << "Gravity: " << physics->isGravityEnabled() << std::endl;
			sceneFile << "Mass: " << physics->getMass() << std::endl;
		}
		else {
			sceneFile << "Physics: 0" << std::endl;
			sceneFile << "Active: 0" << std::endl;
			sceneFile << "Static: 0" << std::endl;
			sceneFile << "Gravity: 0" << std::endl;
			sceneFile << "Mass: 0" << std::endl;
		}

		component = nullptr;
		physics = nullptr;
	}

	sceneFile.close();
}

void SceneTranslator::openScene(std::string file_path) {
	std::string filePath = "";
	if (file_path.find(".iet") != std::string::npos) filePath = file_path;
	else filePath = file_path + ".iet";

	std::ifstream sceneFile;
	sceneFile.open(filePath, std::ios::in);
	if (sceneFile.fail()) return;

	GameObjectManager::getInstance()->deleteAllObjects();

	std::string readLine;
	int index = 0;

	std::string objectName = "";
	AGameObject::ObjectType objectType;
	Vector3D position;
	Vector3D rotation;
	Vector3D scale;

	bool isActive;
	bool hasPhysics;
	bool isPhysicsActive;
	bool isStatic;
	bool isGravityOn;
	float mass;

	while (std::getline(sceneFile, readLine)) {
		switch (index) {
		case 0: {
			objectName = readLine;
			index++;
		} break;

		case 1: {
			std::vector split = StringUtilities::split(readLine, ' ');
			objectType = (AGameObject::ObjectType)std::stoi(split[1]);
			index++;
		} break;

		case 2: {
			std::vector split = StringUtilities::split(readLine, ' ');
			position = Vector3D(std::stof(split[1]), std::stof(split[2]), std::stof(split[3]));
			index++;
		} break;

		case 3: {
			std::vector split = StringUtilities::split(readLine, ' ');
			rotation = Vector3D(std::stof(split[1]), std::stof(split[2]), std::stof(split[3]));
			index++;
		} break;

		case 4: {
			std::vector split = StringUtilities::split(readLine, ' ');
			scale = Vector3D(std::stof(split[1]), std::stof(split[2]), std::stof(split[3]));
			index++;
		} break;

		case 5: {
			std::vector split = StringUtilities::split(readLine, ' ');
			isActive = std::stoi(split[1]);
			index++;
		} break;

		case 6: {
			std::vector split = StringUtilities::split(readLine, ' ');
			hasPhysics = std::stoi(split[1]);
			index++;
		} break;

		case 7: {
			std::vector split = StringUtilities::split(readLine, ' ');
			isPhysicsActive = std::stoi(split[1]);
			index++;
		} break;

		case 8: {
			std::vector split = StringUtilities::split(readLine, ' ');
			isStatic = std::stoi(split[1]);
			index++;
		} break;

		case 9: {
			std::vector split = StringUtilities::split(readLine, ' ');
			isGravityOn = std::stoi(split[1]);
			index++;
		} break;

		case 10: {
			std::vector split = StringUtilities::split(readLine, ' ');
			mass = std::stof(split[1]);
			index = 0;

			GameObjectManager::getInstance()->recreateObject(
				objectName,
				objectType,
				position,
				rotation,
				scale,
				isActive,
				hasPhysics,
				isPhysicsActive,
				isStatic,
				isGravityOn,
				mass
			);
		} break;

		}
	}
}