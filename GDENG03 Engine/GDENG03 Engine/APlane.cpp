#include"APlane.h"
#include"AGraphicsEngine.h"
#include"InputManager.h"
#include"SceneCameraManager.h"
#include"ADeviceContext.h"

APlane::APlane(std::string name, void* shader_byte_code, size_t shader_size) : AGameObject::AGameObject(name) {
	Vertex* currentVertexList = new Vertex[4];

	currentVertexList[0] = Vertex(
		Vector3(-0.5f, 0.f, 0.5f),
		Vector3(1.f, 0.f, 0.f),
		Vector3(0.2f, 0.f, 0.f)
	);
	currentVertexList[1] = Vertex(
		Vector3(0.5f, 0.f, 0.5f),
		Vector3(0.f, 1.f, 0.f),
		Vector3(0.f, 0.2f, 0.f)
	);
	currentVertexList[2] = Vertex(
		Vector3(-0.5f, 0.f, -0.5f),
		Vector3(0.f, 0.f, 1.f),
		Vector3(0.f, 0.f, 0.2f)
	);
	currentVertexList[3] = Vertex(
		Vector3(0.5f, 0.f, -0.5f),
		Vector3(1.f, 1.f, 0.f),
		Vector3(0.2f, 0.2f, 0.f)
	);

	mVertexBuffer = AGraphicsEngine::getInstance()->createVertexBuffer();
	mVertexBuffer->load(currentVertexList, sizeof(Vertex), 4, shader_byte_code, shader_size);

	constant datablock;
	datablock.coefficient = 0.f;

	mConstantBuffer = AGraphicsEngine::getInstance()->createConstantBuffer();
	mConstantBuffer->load(&datablock, sizeof(constant));

	delete[] currentVertexList;
}

APlane::~APlane() {
	mVertexBuffer->release();
	mConstantBuffer->release();
}

void APlane::update(float delta_time) {
	if (this->mIsSelected) {
		if (InputManager::getInstance()->isKeyDown('R')) {
			if (InputManager::getInstance()->isKeyDown(VK_UP)) {
				float deltaRotation = mRotationSpeed * delta_time;
				Vector3 newRotation = this->getLocalRotation();
				newRotation += Vector3(deltaRotation, deltaRotation, deltaRotation);
				this->setRotation(newRotation);
			}

			else if (InputManager::getInstance()->isKeyDown(VK_DOWN)) {
				float deltaRotation = -mRotationSpeed * delta_time;
				Vector3 newRotation = this->getLocalRotation();
				newRotation += Vector3(deltaRotation, deltaRotation, deltaRotation);
				this->setRotation(newRotation);
			}

			else if (InputManager::getInstance()->isKeyDown('I')) {
				Vector3 newRotation = this->getLocalRotation();
				newRotation += Vector3(mRotationSpeed * delta_time, 0.f, 0.f);
				this->setRotation(newRotation);
			}

			else if (InputManager::getInstance()->isKeyDown('K')) {
				Vector3 newRotation = this->getLocalRotation();
				newRotation += Vector3(-mRotationSpeed * delta_time, 0.f, 0.f);
				this->setRotation(newRotation);
			}

			else if (InputManager::getInstance()->isKeyDown('L')) {
				Vector3 newRotation = this->getLocalRotation();
				newRotation += Vector3(0.f, -mRotationSpeed * delta_time, 0.f);
				this->setRotation(newRotation);
			}

			else if (InputManager::getInstance()->isKeyDown('J')) {
				Vector3 newRotation = this->getLocalRotation();
				newRotation += Vector3(0.f, mRotationSpeed * delta_time, 0.f);
				this->setRotation(newRotation);
			}

			else if (InputManager::getInstance()->isKeyDown('O')) {
				Vector3 newRotation = this->getLocalRotation();
				newRotation += Vector3(0.f, 0.f, -mRotationSpeed * delta_time);
				this->setRotation(newRotation);
			}

			else if (InputManager::getInstance()->isKeyDown('U')) {
				Vector3 newRotation = this->getLocalRotation();
				newRotation += Vector3(0.f, 0.f, mRotationSpeed * delta_time);
				this->setRotation(newRotation);
			}
		}

		else if (InputManager::getInstance()->isKeyDown('T')) {
			if (InputManager::getInstance()->isKeyDown('I')) {
				Vector3 newPosition = this->getLocalPosition();
				newPosition += Vector3(0.f, mTranslationSpeed * delta_time, 0.f);
				this->setPosition(newPosition);
			}

			else if (InputManager::getInstance()->isKeyDown('K')) {
				Vector3 newPosition = this->getLocalPosition();
				newPosition += Vector3(0.f, -mTranslationSpeed * delta_time, 0.f);
				this->setPosition(newPosition);
			}

			else if (InputManager::getInstance()->isKeyDown('L')) {
				Vector3 newPosition = this->getLocalPosition();
				newPosition += Vector3(mTranslationSpeed * delta_time, 0.f, 0.f);
				this->setPosition(newPosition);
			}

			else if (InputManager::getInstance()->isKeyDown('J')) {
				Vector3 newPosition = this->getLocalPosition();
				newPosition += Vector3(-mTranslationSpeed * delta_time, 0.f, 0.f);
				this->setPosition(newPosition);
			}

			else if (InputManager::getInstance()->isKeyDown('U')) {
				Vector3 newPosition = this->getLocalPosition();
				newPosition += Vector3(0.f, 0.f, mTranslationSpeed * delta_time);
				this->setPosition(newPosition);
			}

			else if (InputManager::getInstance()->isKeyDown('M')) {
				Vector3 newPosition = this->getLocalPosition();
				newPosition += Vector3(0.f, 0.f, -mTranslationSpeed * delta_time);
				this->setPosition(newPosition);
			}
		}

		else if (InputManager::getInstance()->isKeyDown('Y')) {
			if (InputManager::getInstance()->isKeyDown(VK_UP)) {
				float deltaScale = mScaleSpeed * delta_time;
				Vector3 newScale = this->getLocalScale();
				newScale += Vector3(deltaScale, deltaScale, deltaScale);
				this->setScale(newScale);
			}

			else if (InputManager::getInstance()->isKeyDown(VK_DOWN)) {
				float deltaScale = -mScaleSpeed * delta_time;
				Vector3 newScale = this->getLocalScale();
				newScale += Vector3(deltaScale, deltaScale, deltaScale);
				if (newScale.x > 0.f && newScale.y > 0.f && newScale.z > 0.f) this->setScale(newScale);
			}

			else if (InputManager::getInstance()->isKeyDown('I')) {
				Vector3 newScale = this->getLocalScale();
				newScale += Vector3(0.f, mScaleSpeed * delta_time, 0.f);
				this->setScale(newScale);
			}

			else if (InputManager::getInstance()->isKeyDown('K')) {
				Vector3 newScale = this->getLocalScale();
				newScale += Vector3(0.f, -mScaleSpeed * delta_time, 0.f);
				if (newScale.y > 0.f) this->setScale(newScale);
			}

			else if (InputManager::getInstance()->isKeyDown('L')) {
				Vector3 newScale = this->getLocalScale();
				newScale += Vector3(mScaleSpeed * delta_time, 0.f, 0.f);
				this->setScale(newScale);
			}

			else if (InputManager::getInstance()->isKeyDown('J')) {
				Vector3 newScale = this->getLocalScale();
				newScale += Vector3(-mScaleSpeed * delta_time, 0.f, 0.f);
				if (newScale.x > 0.f) this->setScale(newScale);
			}

			else if (InputManager::getInstance()->isKeyDown('U')) {
				Vector3 newScale = this->getLocalScale();
				newScale += Vector3(0.f, 0.f, mScaleSpeed * delta_time);
				this->setScale(newScale);
			}

			else if (InputManager::getInstance()->isKeyDown('M')) {
				Vector3 newScale = this->getLocalScale();
				newScale += Vector3(0.f, 0.f, -mScaleSpeed * delta_time);
				if (newScale.z > 0.f) this->setScale(newScale);
			}
		}
	}
}

void APlane::draw(int width, int height, AVertexShader* vertex_shader, APixelShader* pixel_shader) {
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

	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleStrip(mVertexBuffer->getVertexCount(), 0);
}

void APlane::setTranslationSpeed(float translation_speed) {
	mTranslationSpeed = translation_speed;
}

void APlane::setRotationSpeed(float rotation_speed) {
	mRotationSpeed = rotation_speed;
}

void APlane::setScaleSpeed(float scale_speed) {
	mScaleSpeed = scale_speed;
}