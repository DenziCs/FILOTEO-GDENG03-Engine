#include"AGameObject.h"

AGameObject::AGameObject(std::string name) {
	mObjectName = name;
	mLocalPosition = Vector3(0.f, 0.f, 0.f);
	mLocalRotation = Vector3(0.f, 0.f, 0.f);
	mLocalScale = Vector3(1.f, 1.f, 1.f);
	mLocalMatrix.setIdentity();
}

AGameObject::~AGameObject() {}

void AGameObject::setPosition(float x, float y, float z) {
	mLocalPosition.x = x;
	mLocalPosition.y = y;
	mLocalPosition.z = z;
}

void AGameObject::setPosition(Vector3 position) {
	mLocalPosition = position;
}

Vector3 AGameObject::getLocalPosition() {
	return mLocalPosition;
}

void AGameObject::setScale(float x, float y, float z) {
	mLocalScale.x = x;
	mLocalScale.y = y;
	mLocalScale.z = z;
}

void AGameObject::setScale(Vector3 scale) {
	mLocalScale = scale;
}

Vector3 AGameObject::getLocalScale() {
	return mLocalScale;
}

void AGameObject::setRotation(float x, float y, float z) {
	mLocalRotation.x = x;
	mLocalRotation.y = y;
	mLocalRotation.z = z;
}

void AGameObject::setRotation(Vector3 rotation) {
	mLocalRotation = rotation;
}

Vector3 AGameObject::getLocalRotation() {
	return mLocalRotation;
}