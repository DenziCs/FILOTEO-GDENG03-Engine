#pragma once
#include<string>
#include<vector>
#include"Vector3D.h"

class UnityObject
{
public:
	UnityObject();
	~UnityObject();

	void addLine(std::string object_info);
	void retrieveInfo();

	long long int getObjectID();
	long long int getObjectType();
	std::string getGameObjectName();
	int getGameObjectType();
	bool isActive();
	Vector3D getPosition();
	Vector3D getRotation();
	Vector3D getScale();
	std::vector<long long int> getComponentList();
	long long int getOwnerID();
	float getMass();
	bool isGravityEnabled();
	bool isStatic();

private:
	std::vector<std::string> mInfoLines;

	long long int mObjectType;
	long long int mObjectID;

	std::string mGameObjectName;
	int mGameObjectType;
	bool mIsActive;

	Vector3D mLocalPosition;
	Vector3D mLocalRotation;
	Vector3D mLocalScale;

	std::vector<long long int> mComponentList;
	long long int mOwnerID;

	float mMass;
	bool mUseGravity;
	bool mIsStatic;
};