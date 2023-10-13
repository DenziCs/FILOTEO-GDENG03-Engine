#include"ACube.h"
#include"AGraphicsEngine.h"
#include"InputManager.h"
#include"ADeviceContext.h"
#include<iostream>

__declspec(align(16))
struct constant {
	Matrix4x4 worldMatrix;
	Matrix4x4 viewMatrix;
	Matrix4x4 projectionMatrix;
	float coefficient;
};

ACube::ACube(std::string name, void* shader_byte_code, size_t shader_size) : AGameObject::AGameObject(name) {
	Vertex* currentVertexList = new Vertex[8];

	currentVertexList[0] = Vertex(
		Vector3(-0.5f, -0.5f, -0.5f),
		Vector3(1.f, 0.f, 0.f),
		Vector3(0.f, 0.2f, 0.2f)
	);
	currentVertexList[1] = Vertex(
		Vector3(-0.5f, 0.5f, -0.5f),
		Vector3(0.f, 1.f, 0.f),
		Vector3(1.f, 0.f, 1.f)
	);
	currentVertexList[2] = Vertex(
		Vector3(0.5f, 0.5f, -0.5f),
		Vector3(0.f, 1.f, 0.f),
		Vector3(0.2f, 0.f, 0.2f)
	);
	currentVertexList[3] = Vertex(
		Vector3(0.5f, -0.5f, -0.5f),
		Vector3(1.f, 0.f, 0.f),
		Vector3(0.f, 0.2f, 0.2f)
	);
	currentVertexList[4] = Vertex(
		Vector3(0.5f, -0.5f, 0.5f),
		Vector3(0.f, 0.f, 1.f),
		Vector3(0.2f, 0.2f, 0.f)
	);
	currentVertexList[5] = Vertex(
		Vector3(0.5f, 0.5f, 0.5f),
		Vector3(1.f, 1.f, 0.f),
		Vector3(0.f, 0.f, 0.2f)
	);
	currentVertexList[6] = Vertex(
		Vector3(-0.5f, 0.5f, 0.5f),
		Vector3(1.f, 1.f, 0.f),
		Vector3(0.f, 0.f, 0.2f)
	);
	currentVertexList[7] = Vertex(
		Vector3(-0.5f, -0.5f, 0.5f),
		Vector3(0.f, 0.f, 1.f),
		Vector3(0.2f, 0.2f, 0.f)
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
}

void ACube::update(float delta_time) {
	mElapsedTime += delta_time; 
	mDeltaPosition = mSpeed * delta_time;
}

void ACube::draw(int width, int height, AVertexShader* vertex_shader, APixelShader* pixel_shader) {
	constant shaderNumbers;

	shaderNumbers.coefficient = 0.5f * (sin(mElapsedTime) + 1.f);

	shaderNumbers.worldMatrix.setIdentity();
	shaderNumbers.worldMatrix.scale(this->getLocalScale());
	shaderNumbers.worldMatrix.rotate(0, this->getLocalRotation().x);
	shaderNumbers.worldMatrix.rotate(1, this->getLocalRotation().y);
	shaderNumbers.worldMatrix.rotate(2, this->getLocalRotation().z);

	if (InputManager::getInstance()->isKeyDown('W')) {
		shaderNumbers.worldMatrix.rotate(2, mDeltaPosition);
		shaderNumbers.worldMatrix.rotate(1, mDeltaPosition);
		shaderNumbers.worldMatrix.rotate(0, mDeltaPosition);
		Vector3 newRotation = this->getLocalRotation();
		newRotation += Vector3(mDeltaPosition, mDeltaPosition, mDeltaPosition);
		this->setRotation(newRotation);
	}
	
	if (InputManager::getInstance()->isKeyDown('S')) {
		shaderNumbers.worldMatrix.rotate(2, -mDeltaPosition);
		shaderNumbers.worldMatrix.rotate(1, -mDeltaPosition);
		shaderNumbers.worldMatrix.rotate(0, -mDeltaPosition);
		Vector3 newRotation = this->getLocalRotation();
		newRotation += Vector3(-mDeltaPosition, -mDeltaPosition, -mDeltaPosition);
		this->setRotation(newRotation);
	}

	shaderNumbers.worldMatrix.translate(this->getLocalPosition());

	shaderNumbers.viewMatrix.setIdentity();
	shaderNumbers.projectionMatrix.setOrthographicProjection(width / 400.f, height / 400.f, -4.f, 4.f);

	mConstantBuffer->update(AGraphicsEngine::getInstance()->getImmediateDeviceContext(), &shaderNumbers);

	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(mConstantBuffer, vertex_shader);
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(mConstantBuffer, pixel_shader);

	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(vertex_shader);
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(pixel_shader);
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(mVertexBuffer);
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setIndexBuffer(mIndexBuffer);

	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->drawIndexedTriangleList(mIndexBuffer->getIndexCount(), 0, 0);
}

void ACube::setAnimationSpeed(float speed) {
	mSpeed = speed;
}

void ACube::onPress(int key) {
	if (key == 'W') std::cout << "W key has been pressed." << std::endl;
	if (key == 'S') std::cout << "S key has been pressed." << std::endl;
}

void ACube::onRelease(int key) {
	if (key == 'W') std::cout << "W key has been released." << std::endl;
	if (key == 'S') std::cout << "S key has been released." << std::endl;
}

void ACube::onMouseMove(Point delta_position) {}

void ACube::onLMBPress(Point mouse_position) {}

void ACube::onLMBRelease(Point mouse_position) {}

void ACube::onRMBPress(Point mouse_position) {}

void ACube::onRMBRelease(Point mouse_position) {}