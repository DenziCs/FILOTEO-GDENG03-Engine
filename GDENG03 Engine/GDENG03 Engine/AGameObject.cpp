#include"AGameObject.h"

AGameObject::AGameObject(std::string name) {
	mObjectName = name;
	mLocalPosition = Vector3D(0.f, 0.f, 0.f);
	mLocalRotation = Vector3D(0.f, 0.f, 0.f);
	mLocalScale = Vector3D(1.f, 1.f, 1.f);
	mLocalMatrix.setIdentity();
}

AGameObject::~AGameObject() {}

std::string AGameObject::getObjectName() {
	return mObjectName;
}

bool AGameObject::isActive() {
	return mIsActive;
}

void AGameObject::setActive(bool is_object_active) {
	mIsActive = is_object_active;
}

void AGameObject::select() {
	mIsSelected = true;
}

void AGameObject::deselect() {
	mIsSelected = false;
}

void AGameObject::setPosition(float x, float y, float z) {
	mLocalPosition.x = x;
	mLocalPosition.y = y;
	mLocalPosition.z = z;

	updateLocalMatrix();
}

void AGameObject::setPosition(Vector3D position) {
	mLocalPosition = position;

	updateLocalMatrix();
}

Vector3D AGameObject::getLocalPosition() {
	return mLocalPosition;
}

void AGameObject::setScale(float x, float y, float z) {
	mLocalScale.x = x;
	mLocalScale.y = y;
	mLocalScale.z = z;

	updateLocalMatrix();
}

void AGameObject::setScale(Vector3D scale) {
	mLocalScale = scale;

	updateLocalMatrix();
}

Vector3D AGameObject::getLocalScale() {
	return mLocalScale;
}

void AGameObject::setRotation(float x, float y, float z) {
	mLocalRotation.x = x;
	mLocalRotation.y = y;
	mLocalRotation.z = z;

	updateLocalMatrix();
}

void AGameObject::setRotation(Vector3D rotation) {
	mLocalRotation = rotation;

	updateLocalMatrix();
}

Vector3D AGameObject::getLocalRotation() {
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