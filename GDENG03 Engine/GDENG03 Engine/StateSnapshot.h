#pragma once
#include"AGameObject.h"

class StateSnapshot
{
public:
	StateSnapshot(AGameObject* affected_object);
	~StateSnapshot();

	AGameObject* getObject();
	std::string getObjectName();
	bool getEnabledState();
	Vector3D getStoredPosition();
	Vector3D getStoredRotation();
	Vector3D getStoredScale();

private:
	AGameObject* mObject;
	std::string mObjectName;
	bool mIsEnabled;
	Vector3D mLocalPosition;
	Vector3D mLocalRotation;
	Vector3D mLocalScale;
};