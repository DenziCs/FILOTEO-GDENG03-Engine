#include"UnityObject.h"
#include"StringUtilities.h"

UnityObject::UnityObject() {
	mObjectType = 0;
	mObjectID = 0;

	mGameObjectName = "Nameless Object";
	mGameObjectType = 0;
	mIsActive = false;

	mLocalScale.x = 1.f;
	mLocalScale.y = 1.f;
	mLocalScale.z = 1.f;

	mOwnerID = 0;

	mMass = 0.f;
	mUseGravity = false;
	mIsStatic = false;
}

UnityObject::~UnityObject() {}

void UnityObject::addLine(std::string object_info) {
	mInfoLines.push_back(object_info);
}

void UnityObject::retrieveInfo() {
	std::string idLine = mInfoLines[0];
	StringUtilities::removeCharacter(&idLine, ' ');
	std::vector<std::string> idSplitA = StringUtilities::split(idLine, '!');
	std::vector<std::string> idSplitB = StringUtilities::split(idSplitA[2], '&');

	mObjectType = std::stoll(idSplitB[0]);
	mObjectID = std::stoll(idSplitB[1]);

	switch (mObjectType) {

	case 1: {
		for (int i = 2; i < mInfoLines.size(); i++) {
			if (mInfoLines[i].find("component") != std::string::npos) {
				std::string componentLine = mInfoLines[i];
				StringUtilities::removeCharacter(&componentLine, ' ');
				StringUtilities::removeCharacter(&componentLine, '{');
				StringUtilities::removeCharacter(&componentLine, '}');

				std::vector<std::string> component = StringUtilities::split(componentLine, ':');
				mComponentList.push_back(std::stoll(component[2]));

				continue;
			}

			if (mInfoLines[i].find("m_Name") != std::string::npos) {
				std::string nameLine = mInfoLines[i];
				std::vector<std::string> name = StringUtilities::split(nameLine, ':');

				mGameObjectName = name[1];
				mGameObjectName.erase(mGameObjectName.begin());

				continue;
			}

			if (mInfoLines[i].find("m_IsActive") != std::string::npos) {
				std::string activeLine = mInfoLines[i];
				StringUtilities::removeCharacter(&activeLine, ' ');

				std::vector<std::string> active = StringUtilities::split(activeLine, ':');
				mIsActive = std::stoi(active[1]);

				continue;
			}
		}
	} break;

	case 4: {
		for (int i = 2; i < mInfoLines.size(); i++) {
			if (mInfoLines[i].find("m_LocalPosition") != std::string::npos) {
				std::string positionLine = mInfoLines[i];
				StringUtilities::removeCharacter(&positionLine, ' ');
				StringUtilities::removeCharacter(&positionLine, '{');
				StringUtilities::removeCharacter(&positionLine, '}');

				std::vector<std::string> position = StringUtilities::split(positionLine, ':');
				mLocalPosition.x = std::stof(position[2].substr(0, position[2].find(",")));
				mLocalPosition.y = std::stof(position[3].substr(0, position[3].find(",")));
				mLocalPosition.z = std::stof(position[4]);

				continue;
			}

			if (mInfoLines[i].find("m_LocalScale") != std::string::npos) {
				std::string scaleLine = mInfoLines[i];
				StringUtilities::removeCharacter(&scaleLine, ' ');
				StringUtilities::removeCharacter(&scaleLine, '{');
				StringUtilities::removeCharacter(&scaleLine, '}');

				std::vector<std::string> scale = StringUtilities::split(scaleLine, ':');
				mLocalScale.x = std::stof(scale[2].substr(0, scale[2].find(",")));
				mLocalScale.y = std::stof(scale[3].substr(0, scale[3].find(",")));
				mLocalScale.z = std::stof(scale[4]);

				continue;
			}

			if (mInfoLines[i].find("m_LocalEulerAnglesHint") != std::string::npos) {
				std::string rotationLine = mInfoLines[i];
				StringUtilities::removeCharacter(&rotationLine, ' ');
				StringUtilities::removeCharacter(&rotationLine, '{');
				StringUtilities::removeCharacter(&rotationLine, '}');

				std::vector<std::string> rotation = StringUtilities::split(rotationLine, ':');
				mLocalRotation.x = std::stof(rotation[2].substr(0, rotation[2].find(",")));
				mLocalRotation.y = std::stof(rotation[3].substr(0, rotation[3].find(",")));
				mLocalRotation.z = std::stof(rotation[4]);

				continue;
			}

			if (mInfoLines[i].find("m_GameObject") != std::string::npos) {
				std::string ownerLine = mInfoLines[i];
				StringUtilities::removeCharacter(&ownerLine, ' ');
				StringUtilities::removeCharacter(&ownerLine, '{');
				StringUtilities::removeCharacter(&ownerLine, '}');

				std::vector<std::string> owner = StringUtilities::split(ownerLine, ':');
				mOwnerID = std::stoll(owner[2]);
			}
		}
	} break;

	case 33: {
		for (int i = 2; i < mInfoLines.size(); i++) {
			if (mInfoLines[i].find("m_Mesh") != std::string::npos) {
				std::string meshLine = mInfoLines[i];
				StringUtilities::removeCharacter(&meshLine, ' ');
				StringUtilities::removeCharacter(&meshLine, '{');
				StringUtilities::removeCharacter(&meshLine, '}');

				std::vector<std::string> mesh = StringUtilities::split(meshLine, ':');
				long long int meshID = std::stoll(mesh[2].substr(0, mesh[2].find(",")));
				if (meshID == 10202) mGameObjectType = 1;
				else if (meshID == 10209) mGameObjectType = 2;

				continue;
			}

			if (mInfoLines[i].find("m_GameObject") != std::string::npos) {
				std::string ownerLine = mInfoLines[i];
				StringUtilities::removeCharacter(&ownerLine, ' ');
				StringUtilities::removeCharacter(&ownerLine, '{');
				StringUtilities::removeCharacter(&ownerLine, '}');

				std::vector<std::string> owner = StringUtilities::split(ownerLine, ':');
				mOwnerID = std::stoll(owner[2]);
			}
		}
	} break;

	case 54: {
		for (int i = 2; i < mInfoLines.size(); i++) {
			if (mInfoLines[i].find("m_Mass") != std::string::npos) {
				std::string massLine = mInfoLines[i];
				StringUtilities::removeCharacter(&massLine, ' ');

				std::vector<std::string> mass = StringUtilities::split(massLine, ':');
				mMass = std::stof(mass[1]);

				continue;
			}

			if (mInfoLines[i].find("m_UseGravity") != std::string::npos) {
				std::string gravityLine = mInfoLines[i];
				StringUtilities::removeCharacter(&gravityLine, ' ');

				std::vector<std::string> gravity = StringUtilities::split(gravityLine, ':');
				mUseGravity = std::stoi(gravity[1]);

				continue;
			}

			if (mInfoLines[i].find("m_IsKinematic") != std::string::npos) {
				std::string staticLine = mInfoLines[i];
				StringUtilities::removeCharacter(&staticLine, ' ');

				std::vector<std::string> noKine = StringUtilities::split(staticLine, ':');
				mIsStatic = std::stoi(noKine[1]);

				continue;
			}

			if (mInfoLines[i].find("m_GameObject") != std::string::npos) {
				std::string ownerLine = mInfoLines[i];
				StringUtilities::removeCharacter(&ownerLine, ' ');
				StringUtilities::removeCharacter(&ownerLine, '{');
				StringUtilities::removeCharacter(&ownerLine, '}');

				std::vector<std::string> owner = StringUtilities::split(ownerLine, ':');
				mOwnerID = std::stoll(owner[2]);
			}
		}
	} break;

	default: {}
	}
}

long long int UnityObject::getObjectID() {
	return mObjectID;
}

long long int UnityObject::getObjectType() {
	return mObjectType;
}

std::string UnityObject::getGameObjectName() {
	return mGameObjectName;
}

int UnityObject::getGameObjectType() {
	return mGameObjectType;
}

bool UnityObject::isActive() {
	return mIsActive;
}

Vector3D UnityObject::getPosition() {
	return mLocalPosition;
}

Vector3D UnityObject::getRotation() {
	return mLocalRotation;
}

Vector3D UnityObject::getScale() {
	return mLocalScale;
}

std::vector<long long int> UnityObject::getComponentList() {
	return mComponentList;
}

long long int UnityObject::getOwnerID() {
	return mOwnerID;
}

float UnityObject::getMass() {
	return mMass;
}

bool UnityObject::isGravityEnabled() {
	return mUseGravity;
}

bool UnityObject::isStatic() {
	return mIsStatic;
}