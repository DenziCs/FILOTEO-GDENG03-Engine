#pragma once
#include"AGameObject.h"

class StateSnapshot
{
public:
	StateSnapshot(AGameObject* affected_object);
	~StateSnapshot();

	AGameObject* getObject();
	std::string getObjectName();
	Vector3D getStoredPosition();
	Vector3D getStoredRotation();
	Vector3D getStoredScale();

private:
	AGameObject* mObject;
	std::string mObjectName;
	Vector3D mLocalPosition;
	Vector3D mLocalRotation;
	Vector3D mLocalScale;
};