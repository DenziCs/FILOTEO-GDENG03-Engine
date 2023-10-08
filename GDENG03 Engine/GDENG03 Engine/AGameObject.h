#pragma once
#include"Vector3.h"
#include<string>

class AVertexShader;
class APixelShader;

class AGameObject
{
public:
	AGameObject(std::string name);
	~AGameObject();

	virtual void update(float delta_time) = 0;
	virtual void draw(int width, int height, AVertexShader* vertex_shader, APixelShader* pixel_shader) = 0;

	void setPosition(float x, float y, float z);
	void setPosition(Vector3 position);
	Vector3 getLocalPosition();

	void setScale(float x, float y, float z);
	void setScale(Vector3 scale);
	Vector3 getLocalScale();

	void setRotation(float x, float y, float z);
	void setRotation(Vector3 rotation);
	Vector3 getLocalRotation();

protected:
	std::string mObjectName;
	Vector3 mLocalPosition;
	Vector3 mLocalScale;
	Vector3 mLocalRotation;
};