#pragma once
#include"AGameObject.h"
#include"TexturedVertexBuffer.h"
#include"AIndexBuffer.h"
#include"AConstantBuffer.h"
#include"Vector2D.h"
#include"ATexture.h"

class TexturedCube : public AGameObject
{
public:
	TexturedCube(std::string name);
	~TexturedCube();

	void update(float delta_time) override;
	void draw(int width, int height) override;

	ATexture* getTexture();
	std::wstring getTexturePath();
	void setTexture(ATexture* texture);
	void setTexture(std::wstring texture_path);

protected:
	ATexture* mTexture;
	std::wstring mTexturePath;

	TexturedVertexBuffer* mVertexBuffer;
	AIndexBuffer* mIndexBuffer;
	AConstantBuffer* mConstantBuffer;

	struct TexturedVertex {
		Vector3D position;
		Vector2D texCoords;
	};
};