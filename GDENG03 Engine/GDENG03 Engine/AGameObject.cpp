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

void AGameObject::updateLocalMatrix(float physics_matrix[16]) {
	Matrix4x4 physicsMatrix;

	physicsMatrix.mMatrix[0][0] = physics_matrix[0];
	physicsMatrix.mMatrix[0][1] = physics_matrix[1];
	physicsMatrix.mMatrix[0][2] = physics_matrix[2];
	physicsMatrix.mMatrix[0][3] = physics_matrix[3];

	physicsMatrix.mMatrix[1][0] = physics_matrix[4];
	physicsMatrix.mMatrix[1][1] = physics_matrix[5];
	physicsMatrix.mMatrix[1][2] = physics_matrix[6];
	physicsMatrix.mMatrix[1][3] = physics_matrix[7];

	physicsMatrix.mMatrix[2][0] = physics_matrix[8];
	physicsMatrix.mMatrix[2][1] = physics_matrix[9];
	physicsMatrix.mMatrix[2][2] = physics_matrix[10];
	physicsMatrix.mMatrix[2][3] = physics_matrix[11];

	physicsMatrix.mMatrix[3][0] = physics_matrix[12];
	physicsMatrix.mMatrix[3][1] = physics_matrix[13];
	physicsMatrix.mMatrix[3][2] = physics_matrix[14];
	physicsMatrix.mMatrix[3][3] = physics_matrix[15];

	updateLocalMatrix();
	mLocalMatrix *= physicsMatrix;
}

Matrix4x4 AGameObject::getLocalMatrix() {
	return mLocalMatrix;
}

float* AGameObject::getPhysicsMatrix() {
	Matrix4x4 physicsMatrix;
	physicsMatrix.setIdentity();

	physicsMatrix.rotate(0, mLocalRotation.x);
	physicsMatrix.rotate(1, mLocalRotation.y);
	physicsMatrix.rotate(2, mLocalRotation.z);
	physicsMatrix.translate(mLocalPosition);

	return physicsMatrix.getMatrix();
}