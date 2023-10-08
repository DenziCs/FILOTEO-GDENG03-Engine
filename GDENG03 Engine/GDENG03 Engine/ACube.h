#pragma once
#include"AGameObject.h"
#include"AVertexBuffer.h"
#include"AIndexBuffer.h"
#include"AConstantBuffer.h"
#include"Matrix4x4.h"

class ACube : public AGameObject
{
public:
	ACube(std::string name, void* shader_byte_code, size_t shader_size);
	ACube(std::string name, AVertexBuffer* vertex_buffer, AIndexBuffer* index_buffer, AConstantBuffer* constant_buffer);
	~ACube();

	void update(float delta_time) override;
	void draw(int width, int height, AVertexShader* vertex_shader, APixelShader* pixel_shader) override;
	void setAnimationSpeed(float speed);

private:
	AVertexBuffer* mVertexBuffer;
	AIndexBuffer* mIndexBuffer;
	AConstantBuffer* mConstantBuffer;

	float mElapsedTime = 0.f;
	float mDeltaPosition = 0.f;
	float mDeltaTime = 0.f;
	float mSpeed = 10.f;
};