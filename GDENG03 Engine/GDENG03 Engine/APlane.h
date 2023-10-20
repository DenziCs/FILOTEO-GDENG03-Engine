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
	void setTranslationSpeed(float translation_speed);
	void setRotationSpeed(float rotation_speed);
	void setScaleSpeed(float scale_speed);

private:
	AVertexBuffer* mVertexBuffer;
	AConstantBuffer* mConstantBuffer;

	float mTranslationSpeed = 1.f;
	float mRotationSpeed = 10.f;
	float mScaleSpeed = 1.f;
};