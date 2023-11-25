#pragma once
#include"Vector3D.h"
#include"Matrix4x4.h"
#include<string>

class AVertexShader;
class APixelShader;

class AGameObject
{
public:
	AGameObject(std::string name);
	~AGameObject();

	virtual void update(float delta_time);
	virtual void draw(int width, int height, AVertexShader* vertex_shader, APixelShader* pixel_shader) = 0;

	std::string getObjectName();
	bool isActive();
	void setActive(bool is_object_active);
	void select();
	void deselect();

	void setTranslationSpeed(float translation_speed);
	void setRotationSpeed(float rotation_speed);
	void setScaleSpeed(float scale_speed);

	void setPosition(float x, float y, float z);
	void setPosition(Vector3D position);
	Vector3D getLocalPosition();

	void setScale(float x, float y, float z);
	void setScale(Vector3D scale);
	Vector3D getLocalScale();

	void setRotation(float x, float y, float z);
	void setRotation(Vector3D rotation);
	Vector3D getLocalRotation();

	void updateLocalMatrix();
	void updateLocalMatrix(float physics_matrix[16]);
	Matrix4x4 getLocalMatrix();
	float* getPhysicsMatrix();

	__declspec(align(16))
		struct constant {
		Matrix4x4 worldMatrix;
		Matrix4x4 viewMatrix;
		Matrix4x4 projectionMatrix;
		float coefficient;
	};

protected:
	std::string mObjectName;
	Vector3D mLocalPosition;
	Vector3D mLocalScale;
	Vector3D mLocalRotation;
	Matrix4x4 mLocalMatrix;

	bool mIsActive = true;
	bool mIsSelected = false;

	float mTranslationSpeed = 5.f;
	float mRotationSpeed = 1.f;
	float mScaleSpeed = 1.f;
};