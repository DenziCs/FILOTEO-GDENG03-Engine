#pragma once
#include<memory>
#include"Vector3.h"

class Matrix4x4
{
public:
	Matrix4x4();
	~Matrix4x4();

	void setIdentity();
	void setTranslation(float delta_x, float delta_y, float delta_z);
	void setTranslation(const Vector3& translate_vector);
	void setScale(float factor_x, float factor_y, float factor_z);
	void setScale(const Vector3& scale_vector);
	void setRotationX(float theta);
	void setRotationY(float theta);
	void setRotationZ(float theta);
	void setOrthoProjection(float width, float height, float near_plane, float far_plane);
	void setOrthoProjection(float right, float left, float bottom, float top, float near_plane, float far_plane);

	void operator *=(const Matrix4x4& matrix);
	void setMatrix(const Matrix4x4& matrix);

	float mMatrix[4][4] = {};
};