#include"ACube.h"
#include"AGraphicsEngine.h"
#include"InputManager.h"
#include"SceneCameraManager.h"
#include"ADeviceContext.h"
#include<iostream>

ACube::ACube(std::string name, void* shader_byte_code, size_t shader_size) : AGameObject::AGameObject(name) {
	Vertex* currentVertexList = new Vertex[8];

	currentVertexList[0] = Vertex(
		Vector3(-0.5f, -0.5f, -0.5f),
		Vector3(1.f, 0.f, 0.f),
		Vector3(0.2f, 0.f, 0.f)
	);
	currentVertexList[1] = Vertex(
		Vector3(-0.5f, 0.5f, -0.5f),
		Vector3(0.f, 1.f, 0.f),
		Vector3(0.f, 0.2f, 0.f)
	);
	currentVertexList[2] = Vertex(
		Vector3(0.5f, 0.5f, -0.5f),
		Vector3(0.f, 1.f, 0.f),
		Vector3(0.f, 0.2f, 0.f)
	);
	currentVertexList[3] = Vertex(
		Vector3(0.5f, -0.5f, -0.5f),
		Vector3(1.f, 0.f, 0.f),
		Vector3(0.2f, 0.f, 0.f)
	);
	currentVertexList[4] = Vertex(
		Vector3(0.5f, -0.5f, 0.5f),
		Vector3(0.f, 0.f, 1.f),
		Vector3(0.f, 0.f, 0.2f)
	);
	currentVertexList[5] = Vertex(
		Vector3(0.5f, 0.5f, 0.5f),
		Vector3(1.f, 1.f, 0.f),
		Vector3(0.2f, 0.2f, 0.f)
	);
	currentVertexList[6] = Vertex(
		Vector3(-0.5f, 0.5f, 0.5f),
		Vector3(1.f, 1.f, 0.f),
		Vector3(0.2f, 0.2f, 0.f)
	);
	currentVertexList[7] = Vertex(
		Vector3(-0.5f, -0.5f, 0.5f),
		Vector3(0.f, 0.f, 1.f),
		Vector3(0.f, 0.f, 0.2f)
	);

	mVertexBuffer = AGraphicsEngine::getInstance()->createVertexBuffer();
	mVertexBuffer->load(currentVertexList, sizeof(Vertex), 8, shader_byte_code, shader_size);

	unsigned int indexList[] = {
		0, 1, 2,
		2, 3, 0,
		4, 5, 6,
		6, 7, 4,
		1, 6, 5,
		5, 2, 1,
		7, 0, 3,
		3, 4, 7,
		3, 2, 5,
		5, 4, 3,
		7, 6, 1,
		1, 0, 7
	};

	mIndexBuffer = AGraphicsEngine::getInstance()->createIndexBuffer();
	mIndexBuffer->load(indexList, ARRAYSIZE(indexList));

	constant datablock;
	datablock.coefficient = 0.f; 

	mConstantBuffer = AGraphicsEngine::getInstance()->createConstantBuffer();
	mConstantBuffer->load(&datablock, sizeof(constant));

	delete[] currentVertexList;

	InputManager::getInstance()->addListener(this);
}

ACube::~ACube() {
	mVertexBuffer->release();
	mIndexBuffer->release();
	mConstantBuffer->release();

	InputManager::getInstance()->removeListener(this);
}

void ACube::update(float delta_time) {
	float deltaRotation = mRotationSpeed * delta_time;
	Vector3 newRotation = this->getLocalRotation();
	newRotation += Vector3(deltaRotation, deltaRotation, deltaRotation);
	this->setRotation(newRotation);
}

void ACube::draw(int width, int height, AVertexShader* vertex_shader, APixelShader* pixel_shader) {
	constant shaderNumbers;

	shaderNumbers.worldMatrix = this->getLocalMatrix();
	shaderNumbers.viewMatrix = SceneCameraManager::getInstance()->getSceneCameraViewMatrix();
	shaderNumbers.projectionMatrix = SceneCameraManager::getInstance()->getSceneCameraProjectionMatrix();
	shaderNumbers.coefficient = 0.f;

	mConstantBuffer->update(AGraphicsEngine::getInstance()->getImmediateDeviceContext(), &shaderNumbers);

	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(mConstantBuffer, vertex_shader);
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(mConstantBuffer, pixel_shader);

	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(vertex_shader);
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(pixel_shader);
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(mVertexBuffer);
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setIndexBuffer(mIndexBuffer);

	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->drawIndexedTriangleList(mIndexBuffer->getIndexCount(), 0, 0);
}

void ACube::setTranslationSpeed(float translation_speed) {
	mTranslationSpeed = translation_speed;
}

void ACube::setRotationSpeed(float rotation_speed) {
	mRotationSpeed = rotation_speed;
}

void ACube::setScaleSpeed(float scale_speed) {
	mScaleSpeed = scale_speed;
}

void ACube::onPress(int key) {
	if (key == VK_UP) std::cout << "Up arrow key has been pressed." << std::endl;
	if (key == VK_DOWN) std::cout << "Down arrow key has been pressed." << std::endl;
}

void ACube::onRelease(int key) {
	if (key == VK_UP) std::cout << "Up arrow key has been released." << std::endl;
	if (key == VK_DOWN) std::cout << "Down arrow key has been released." << std::endl;
}

void ACube::onMouseMove(Point delta_position) {}

void ACube::onLMBPress(Point mouse_position) {}

void ACube::onLMBRelease(Point mouse_position) {}

void ACube::onRMBPress(Point mouse_position) {}

void ACube::onRMBRelease(Point mouse_position) {}