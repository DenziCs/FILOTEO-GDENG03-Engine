#include"APlane.h"
#include"AGraphicsEngine.h"
#include"InputManager.h"
#include"SceneCameraManager.h"
#include"ADeviceContext.h"

APlane::APlane(std::string name, void* shader_byte_code, size_t shader_size) : AGameObject::AGameObject(name) {
	Vertex* currentVertexList = new Vertex[4];

	currentVertexList[0] = Vertex(
		Vector3D(-0.5f, 0.f, 0.5f),
		Vector3D(1.f, 0.f, 0.f),
		Vector3D(0.2f, 0.f, 0.f)
	);
	currentVertexList[1] = Vertex(
		Vector3D(0.5f, 0.f, 0.5f),
		Vector3D(0.f, 1.f, 0.f),
		Vector3D(0.f, 0.2f, 0.f)
	);
	currentVertexList[2] = Vertex(
		Vector3D(-0.5f, 0.f, -0.5f),
		Vector3D(0.f, 0.f, 1.f),
		Vector3D(0.f, 0.f, 0.2f)
	);
	currentVertexList[3] = Vertex(
		Vector3D(0.5f, 0.f, -0.5f),
		Vector3D(1.f, 1.f, 0.f),
		Vector3D(0.2f, 0.2f, 0.f)
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
				Vector3D newRotation = this->getLocalRotation();
				newRotation += Vector3D(deltaRotation, deltaRotation, deltaRotation);
				this->setRotation(newRotation);
			}

			else if (InputManager::getInstance()->isKeyDown(VK_DOWN)) {
				float deltaRotation = -mRotationSpeed * delta_time;
				Vector3D newRotation = this->getLocalRotation();
				newRotation += Vector3D(deltaRotation, deltaRotation, deltaRotation);
				this->setRotation(newRotation);
			}

			else if (InputManager::getInstance()->isKeyDown('I')) {
				Vector3D newRotation = this->getLocalRotation();
				newRotation += Vector3D(mRotationSpeed * delta_time, 0.f, 0.f);
				this->setRotation(newRotation);
			}

			else if (InputManager::getInstance()->isKeyDown('K')) {
				Vector3D newRotation = this->getLocalRotation();
				newRotation += Vector3D(-mRotationSpeed * delta_time, 0.f, 0.f);
				this->setRotation(newRotation);
			}

			else if (InputManager::getInstance()->isKeyDown('L')) {
				Vector3D newRotation = this->getLocalRotation();
				newRotation += Vector3D(0.f, -mRotationSpeed * delta_time, 0.f);
				this->setRotation(newRotation);
			}

			else if (InputManager::getInstance()->isKeyDown('J')) {
				Vector3D newRotation = this->getLocalRotation();
				newRotation += Vector3D(0.f, mRotationSpeed * delta_time, 0.f);
				this->setRotation(newRotation);
			}

			else if (InputManager::getInstance()->isKeyDown('O')) {
				Vector3D newRotation = this->getLocalRotation();
				newRotation += Vector3D(0.f, 0.f, -mRotationSpeed * delta_time);
				this->setRotation(newRotation);
			}

			else if (InputManager::getInstance()->isKeyDown('U')) {
				Vector3D newRotation = this->getLocalRotation();
				newRotation += Vector3D(0.f, 0.f, mRotationSpeed * delta_time);
				this->setRotation(newRotation);
			}
		}

		else if (InputManager::getInstance()->isKeyDown('T')) {
			float translationScalar = mTranslationSpeed * delta_time;

			if (InputManager::getInstance()->isKeyDown('I')) {
				Vector3D newPosition = this->getLocalPosition();
				newPosition += this->mLocalMatrix.getUpVector() * translationScalar;
				this->setPosition(newPosition);
			}

			else if (InputManager::getInstance()->isKeyDown('K')) {
				Vector3D newPosition = this->getLocalPosition();
				newPosition += this->mLocalMatrix.getUpVector() * -translationScalar;
				this->setPosition(newPosition);
			}

			else if (InputManager::getInstance()->isKeyDown('L')) {
				Vector3D newPosition = this->getLocalPosition();
				newPosition += this->mLocalMatrix.getRightVector() * translationScalar;
				this->setPosition(newPosition);
			}

			else if (InputManager::getInstance()->isKeyDown('J')) {
				Vector3D newPosition = this->getLocalPosition();
				newPosition += this->mLocalMatrix.getRightVector() * -translationScalar;
				this->setPosition(newPosition);
			}

			else if (InputManager::getInstance()->isKeyDown('U')) {
				Vector3D newPosition = this->getLocalPosition();
				newPosition += this->mLocalMatrix.getForwardVector() * translationScalar;
				this->setPosition(newPosition);
			}

			else if (InputManager::getInstance()->isKeyDown('M')) {
				Vector3D newPosition = this->getLocalPosition();
				newPosition += this->mLocalMatrix.getForwardVector() * -translationScalar;
				this->setPosition(newPosition);
			}
		}

		else if (InputManager::getInstance()->isKeyDown('Y')) {
			if (InputManager::getInstance()->isKeyDown(VK_UP)) {
				float deltaScale = mScaleSpeed * delta_time;
				Vector3D newScale = this->getLocalScale();
				newScale += Vector3D(deltaScale, deltaScale, deltaScale);
				this->setScale(newScale);
			}

			else if (InputManager::getInstance()->isKeyDown(VK_DOWN)) {
				float deltaScale = -mScaleSpeed * delta_time;
				Vector3D newScale = this->getLocalScale();
				newScale += Vector3D(deltaScale, deltaScale, deltaScale);
				if (newScale.x > 0.f && newScale.y > 0.f && newScale.z > 0.f) this->setScale(newScale);
			}

			else if (InputManager::getInstance()->isKeyDown('I')) {
				Vector3D newScale = this->getLocalScale();
				newScale += Vector3D(0.f, mScaleSpeed * delta_time, 0.f);
				this->setScale(newScale);
			}

			else if (InputManager::getInstance()->isKeyDown('K')) {
				Vector3D newScale = this->getLocalScale();
				newScale += Vector3D(0.f, -mScaleSpeed * delta_time, 0.f);
				if (newScale.y > 0.f) this->setScale(newScale);
			}

			else if (InputManager::getInstance()->isKeyDown('L')) {
				Vector3D newScale = this->getLocalScale();
				newScale += Vector3D(mScaleSpeed * delta_time, 0.f, 0.f);
				this->setScale(newScale);
			}

			else if (InputManager::getInstance()->isKeyDown('J')) {
				Vector3D newScale = this->getLocalScale();
				newScale += Vector3D(-mScaleSpeed * delta_time, 0.f, 0.f);
				if (newScale.x > 0.f) this->setScale(newScale);
			}

			else if (InputManager::getInstance()->isKeyDown('U')) {
				Vector3D newScale = this->getLocalScale();
				newScale += Vector3D(0.f, 0.f, mScaleSpeed * delta_time);
				this->setScale(newScale);
			}

			else if (InputManager::getInstance()->isKeyDown('M')) {
				Vector3D newScale = this->getLocalScale();
				newScale += Vector3D(0.f, 0.f, -mScaleSpeed * delta_time);
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