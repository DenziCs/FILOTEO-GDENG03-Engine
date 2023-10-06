#pragma once

class Vector3
{
public:
	Vector3();
	Vector3(float vector_x, float vector_y, float vector_z);
	Vector3(const Vector3& vector);
	~Vector3() {}

	float x;
	float y;
	float z;
};