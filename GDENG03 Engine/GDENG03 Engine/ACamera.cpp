#include"ACamera.h"
#include"InputManager.h"
#include<Windows.h>
#include<iostream>

ACamera::ACamera(std::string name) : AGameObject::AGameObject(name) {
	InputManager::getInstance()->addListener(this);
}

ACamera::~ACamera() {
	InputManager::getInstance()->removeListener(this);
}

void ACamera::update(float delta_time) {
	if (mCameraControlsEnabled) {
		Vector3 newPosition = this->getLocalPosition();
		float movementSpeed = 5.f;
		float movementScalar;

		if (InputManager::getInstance()->isKeyDown(VK_UP)) {
			movementScalar = delta_time * movementSpeed * 1.f;
			newPosition += (this->mLocalMatrix.getForwardVector() * movementScalar);
			this->setPosition(newPosition);
		}

		else if (InputManager::getInstance()->isKeyDown(VK_DOWN)) {
			movementScalar = delta_time * movementSpeed * -1.f;
			newPosition += (this->mLocalMatrix.getForwardVector() * movementScalar);
			this->setPosition(newPosition);
		}

		else if (InputManager::getInstance()->isKeyDown(VK_RIGHT)) {
			movementScalar = delta_time * movementSpeed * 1.f;
			newPosition += (this->mLocalMatrix.getRightVector() * movementScalar);
			this->setPosition(newPosition);
		}

		else if (InputManager::getInstance()->isKeyDown(VK_LEFT)) {
			movementScalar = delta_time * movementSpeed * -1.f;
			newPosition += (this->mLocalMatrix.getRightVector() * movementScalar);
			this->setPosition(newPosition);
		}
	}
}

Matrix4x4 ACamera::getViewMatrix() {
	Matrix4x4 viewMatrix = this->mLocalMatrix;
	viewMatrix.inverse();
	return viewMatrix;
}

void ACamera::setOrthographicProjectionMatrix(float width, float height, float near_plane, float far_plane) {
	mProjectionMatrix.setOrthographicProjection(width, height, near_plane, far_plane);
}

void ACamera::setPerspectiveProjectionMatrix(float field_of_view, float aspect, float near_plane, float far_plane) {
	mProjectionMatrix.setPerspectiveProjection(field_of_view, aspect, near_plane, far_plane);
}

Matrix4x4 ACamera::getProjectionMatrix() {
	return mProjectionMatrix;
}

void ACamera::onPress(int key) {
	switch (key) {
	case VK_UP:
		std::cout << "Up arrow key has been pressed." << std::endl;
		break;
	case VK_DOWN:
		std::cout << "Down arrow key has been pressed." << std::endl;
		break;
	case VK_RIGHT:
		std::cout << "Right arrow key has been pressed." << std::endl;
		break;
	case VK_LEFT:
		std::cout << "Left arrow key has been pressed." << std::endl;
		break;
	}
}

void ACamera::onRelease(int key) {
	switch (key) {
	case VK_UP:
		std::cout << "Up arrow key has been released." << std::endl;
		break;
	case VK_DOWN:
		std::cout << "Down arrow key has been released." << std::endl;
		break;
	case VK_RIGHT:
		std::cout << "Right arrow key has been released." << std::endl;
		break;
	case VK_LEFT:
		std::cout << "Left arrow key has been released." << std::endl;
		break;
	}
}

void ACamera::onMouseMove(const Point delta_position) {
	if (mCameraControlsEnabled) {
		Vector3 newRotation = this->getLocalRotation();
		newRotation.y += (float)delta_position.getX() * 0.01f;
		newRotation.x += (float)delta_position.getY() * 0.01f;
		this->setRotation(newRotation);
	}
}

void ACamera::onLMBPress(const Point mouse_position) {
	std::cout << "Left mouse button has been pressed." << std::endl;
}

void ACamera::onLMBRelease(const Point mouse_position) {
	std::cout << "Left mouse button has been released." << std::endl;
}

void ACamera::onRMBPress(const Point mouse_position) {
	std::cout << "Right mouse button has been pressed. Release to toggle camera controls." << std::endl;
}

void ACamera::onRMBRelease(const Point mouse_position) {
	std::cout << "Right mouse button has been released. ";
	mCameraControlsEnabled = !mCameraControlsEnabled;
	if (mCameraControlsEnabled) std::cout << "Camera controls enabled." << std::endl;
	else std::cout << "Camera controls disabled." << std::endl;
}

void ACamera::draw(int width, int height, AVertexShader* vertex_shader, APixelShader* pixel_shader) {}