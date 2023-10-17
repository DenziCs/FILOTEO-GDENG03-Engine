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

	updateLocalMatrix();
}

void AGameObject::setPosition(Vector3 position) {
	mLocalPosition = position;

	updateLocalMatrix();
}

Vector3 AGameObject::getLocalPosition() {
	return mLocalPosition;
}

void AGameObject::setScale(float x, float y, float z) {
	mLocalScale.x = x;
	mLocalScale.y = y;
	mLocalScale.z = z;

	updateLocalMatrix();
}

void AGameObject::setScale(Vector3 scale) {
	mLocalScale = scale;

	updateLocalMatrix();
}

Vector3 AGameObject::getLocalScale() {
	return mLocalScale;
}

void AGameObject::setRotation(float x, float y, float z) {
	mLocalRotation.x = x;
	mLocalRotation.y = y;
	mLocalRotation.z = z;

	updateLocalMatrix();
}

void AGameObject::setRotation(Vector3 rotation) {
	mLocalRotation = rotation;

	updateLocalMatrix();
}

Vector3 AGameObject::getLocalRotation() {
	return mLocalRotation;
}

void AGameObject::updateLocalMatrix() {
	Matrix4x4 newLocalMatrix;
	newLocalMatrix.setIdentity();

	newLocalMatrix.scale(mLocalScale);
	newLocalMatrix.rotate(0, mLocalRotation.x);
	newLocalMatrix.rotate(1, mLocalRotation.y);
	newLocalMatrix.rotate(2, mLocalRotation.z);
	newLocalMatrix.translate(mLocalPosition);

	mLocalMatrix = newLocalMatrix;
}

Matrix4x4 AGameObject::getLocalMatrix() {
	return mLocalMatrix;
}