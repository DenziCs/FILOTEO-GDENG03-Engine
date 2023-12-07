#include"TexturedCube.h"
#include"AGraphicsEngine.h"
#include"SceneCameraManager.h"
#include"ADeviceContext.h"
#include"TextureManager.h"
#include"ShaderNames.h"

TexturedCube::TexturedCube(std::string name) : AGameObject::AGameObject(name, TEXTURED_CUBE) {
	void* shaderByteCode = nullptr;
	size_t shaderSize;
	AGraphicsEngine::getInstance()->compileVertexShader(L"TexturedVertexShader.hlsl", "vsmain", &shaderByteCode, &shaderSize);

	Vector3D positionList[] = {
		{ Vector3D(-0.5f,-0.5f,-0.5f)},
		{ Vector3D(-0.5f, 0.5f, -0.5f) },
		{ Vector3D(0.5f, 0.5f, -0.5f) },
		{ Vector3D(0.5f, -0.5f, -0.5f) },

		{ Vector3D(0.5f, -0.5f, 0.5f) },
		{ Vector3D(0.5f, 0.5f, 0.5f) },
		{ Vector3D(-0.5f, 0.5f, 0.5f)},
		{ Vector3D(-0.5f, -0.5f, 0.5f) }
	};

	Vector2D texcoordList[] = {
		{ Vector2D(0.0f, 0.0f) },
		{ Vector2D(0.0f, 1.0f) },
		{ Vector2D(1.0f, 0.0f) },
		{ Vector2D(1.0f, 1.0f) }
	};

	TexturedVertex vertexList[] = {
		{ positionList[0], texcoordList[1] },
		{ positionList[1], texcoordList[0] },
		{ positionList[2], texcoordList[2] },
		{ positionList[3], texcoordList[3] },

		{ positionList[4], texcoordList[1] },
		{ positionList[5], texcoordList[0] },
		{ positionList[6], texcoordList[2] },
		{ positionList[7], texcoordList[3] },

		{ positionList[1], texcoordList[1] },
		{ positionList[6], texcoordList[0] },
		{ positionList[5], texcoordList[2] },
		{ positionList[2], texcoordList[3] },

		{ positionList[7], texcoordList[1] },
		{ positionList[0], texcoordList[0] },
		{ positionList[3], texcoordList[2] },
		{ positionList[4], texcoordList[3] },

		{ positionList[3], texcoordList[1] },
		{ positionList[2], texcoordList[0] },
		{ positionList[5], texcoordList[2] },
		{ positionList[4], texcoordList[3] },

		{ positionList[7], texcoordList[1] },
		{ positionList[6], texcoordList[0] },
		{ positionList[1], texcoordList[2] },
		{ positionList[0], texcoordList[3] }
	};


	mVertexBuffer = AGraphicsEngine::getInstance()->createTexturedVertexBuffer();
	mVertexBuffer->load(vertexList, sizeof(TexturedVertex), ARRAYSIZE(vertexList), shaderByteCode, shaderSize);

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

	this->mVertexShader = AGraphicsEngine::getInstance()->createVertexShader(shaderByteCode, shaderSize);
	AGraphicsEngine::getInstance()->releaseCompiledVertexShader();

	AGraphicsEngine::getInstance()->compilePixelShader(L"TexturedPixelShader.hlsl", "psmain", &shaderByteCode, &shaderSize);
	this->mPixelShader = AGraphicsEngine::getInstance()->createPixelShader(shaderByteCode, shaderSize);
	AGraphicsEngine::getInstance()->releaseCompiledPixelShader();

	mTexture = TextureManager::getInstance()->getTexture(L"C:/Users/Aorus/source/repos/FILOTEO-GDENG03-Engine/GDENG03 Engine/GDENG03 Engine/Assets/Textures/wood.jpg");
}

TexturedCube::~TexturedCube() {
	mVertexBuffer->release();
	mIndexBuffer->release();
	mConstantBuffer->release();
}

void TexturedCube::update(float delta_time) {
	AGameObject::update(delta_time);
}

void TexturedCube::draw(int width, int height) {
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setTexture(mTexture);

	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(this->mVertexShader);
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(this->mPixelShader);

	constant shaderNumbers;

	if (this->findComponentOfType(AComponent::PHYSICS)) {
		shaderNumbers.worldMatrix = this->getPhysicsMatrix();
	}

	else shaderNumbers.worldMatrix = this->getLocalMatrix();

	shaderNumbers.viewMatrix = SceneCameraManager::getInstance()->getSceneCameraViewMatrix();
	shaderNumbers.projectionMatrix = SceneCameraManager::getInstance()->getSceneCameraProjectionMatrix();
	shaderNumbers.coefficient = 0.f;

	mConstantBuffer->update(AGraphicsEngine::getInstance()->getImmediateDeviceContext(), &shaderNumbers);

	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(mConstantBuffer, this->mVertexShader);
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(mConstantBuffer, this->mPixelShader);

	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(mVertexBuffer);
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->setIndexBuffer(mIndexBuffer);

	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->drawIndexedTriangleList(mIndexBuffer->getIndexCount(), 0, 0);
}

ATexture* TexturedCube::getTexture() {
	return mTexture;
}

std::wstring TexturedCube::getTexturePath() {
	return mTexturePath;
}

void TexturedCube::setTexture(ATexture* texture) {
	mTexture = texture;
}

void TexturedCube::setTexture(std::wstring texture_path) {
	mTexture = TextureManager::getInstance()->getTexture(texture_path.c_str());
	mTexturePath = texture_path;
}