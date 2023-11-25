#pragma once
#include"AGameObject.h"
#include"AVertexBuffer.h"
#include"AConstantBuffer.h"

class APlane : public AGameObject
{
public:
	APlane(std::string name, void* shader_byte_code, size_t shader_size);
	~APlane();

	void update(float delta_time) override;
	void draw(int width, int height, AVertexShader* vertex_shader, APixelShader* pixel_shader) override;

private:
	AVertexBuffer* mVertexBuffer;
	AConstantBuffer* mConstantBuffer;
};