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
	~ACube();

	void update(float delta_time) override;
	void draw(int width, int height, AVertexShader* vertex_shader, APixelShader* pixel_shader) override;

private:
	AVertexBuffer* mVertexBuffer;
	AIndexBuffer* mIndexBuffer;
	AConstantBuffer* mConstantBuffer;

	float mDeltaTime = 0.f;
	float mElapsedTime = 0.f;
};