#include"ACube.h"
#include"AGraphicsEngine.h"
#include"ADeviceContext.h"

__declspec(align(16))
struct constant {
	Matrix4x4 worldMatrix;
	Matrix4x4 viewMatrix;
	Matrix4x4 projectionMatrix;
	float coefficient;
};

ACube::ACube(std::string name, void* shader_byte_code, size_t shader_size) : AGameObject::AGameObject(name) {
}

ACube::ACube(std::string name, AVertexBuffer* vertex_buffer, AIndexBuffer* index_buffer, AConstantBuffer* constant_buffer) : AGameObject::AGameObject(name) {
	mVertexBuffer = vertex_buffer;
	mIndexBuffer = index_buffer;
	mConstantBuffer = constant_buffer;
}

void ACube::update(float delta_time) {
	mElapsedTime += delta_time; 
	mDeltaPosition = mSpeed * delta_time; 
}

void ACube::draw(int width, int height, AVertexShader* vertex_shader, APixelShader* pixel_shader) {
	constant shaderNumbers;

	shaderNumbers.coefficient = mElapsedTime; 

	shaderNumbers.worldMatrix.setIdentity();

	shaderNumbers.worldMatrix.rotate(2, mDeltaPosition);
	shaderNumbers.worldMatrix.rotate(1, mDeltaPosition);
	shaderNumbers.worldMatrix.rotate(0, mDeltaPosition);

	shaderNumbers.viewMatrix.setIdentity();
	shaderNumbers.projectionMatrix.setOrthoProjection(
		width / 400.f,
		height / 400.f,
		-4.f,
		4.f
	);

	mConstantBuffer->update(AGraphicsEngine::getInstance()->getImmediateDeviceContext(), &shaderNumbers);
}

void ACube::setAnimationSpeed(float speed) {
	mSpeed = speed;
}