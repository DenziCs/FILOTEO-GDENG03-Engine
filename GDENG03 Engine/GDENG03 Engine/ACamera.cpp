#include"ACamera.h"
#include"InputManager.h"
#include<Windows.h>

ACamera::ACamera(std::string name) : AGameObject::AGameObject(name) {
	InputManager::getInstance()->addListener(this);
}

ACamera::~ACamera() {
	InputManager::getInstance()->removeListener(this);
}

void ACamera::update(float delta_time) {
	Vector3 newPosition = this->getLocalPosition();
	float movementSpeed = 10.f;
	float movementScalar;

	if (InputManager::getInstance()->isKeyDown(VK_UP)) {
		movementScalar = delta_time * movementSpeed * 1.f;
		newPosition += (this->mLocalMatrix.getForwardVector() * movementScalar);
		this->setPosition(newPosition);
		updateViewMatrix();
	}

	else if (InputManager::getInstance()->isKeyDown(VK_DOWN)) {
		movementScalar = delta_time * movementSpeed * -1.f;
		newPosition += (this->mLocalMatrix.getForwardVector() * movementScalar);
		this->setPosition(newPosition);
		updateViewMatrix();
	}

	else if (InputManager::getInstance()->isKeyDown(VK_RIGHT)) {
		movementScalar = delta_time * movementSpeed * 1.f;
		newPosition += (this->mLocalMatrix.getRightVector() * movementScalar);
		this->setPosition(newPosition);
		updateViewMatrix();
	}

	else if (InputManager::getInstance()->isKeyDown(VK_LEFT)) {
		movementScalar = delta_time * movementSpeed * -1.f;
		newPosition += (this->mLocalMatrix.getRightVector() * movementScalar);
		this->setPosition(newPosition);
		updateViewMatrix();
	}
}

Matrix4x4 ACamera::getViewMatrix() {
	Matrix4x4 viewMatrix = this->mLocalMatrix;
	viewMatrix.inverse();
	return viewMatrix;
}

void ACamera::onPress(int key) {}

void ACamera::onRelease(int key) {}

void ACamera::onMouseMove(const Point delta_position) {
	Vector3 newRotation = this->getLocalRotation();
	newRotation.x += (float)delta_position.getX();
	newRotation.y += (float)delta_position.getY();
	this->setRotation(newRotation);
}

void ACamera::onLMBPress(const Point mouse_position) {}

void ACamera::onLMBRelease(const Point mouse_position) {}

void ACamera::onRMBPress(const Point mouse_position) {}

void ACamera::onRMBRelease(const Point mouse_position) {}

void ACamera::updateViewMatrix() {
	Matrix4x4 worldCam;
	Vector3 localRotation = this->getLocalRotation();

	worldCam.rotate(0, localRotation.x);
	worldCam.rotate(1, localRotation.y);
	worldCam.rotate(2, localRotation.z);
	worldCam.translate(this->getLocalPosition());

	this->mLocalMatrix = worldCam;
}