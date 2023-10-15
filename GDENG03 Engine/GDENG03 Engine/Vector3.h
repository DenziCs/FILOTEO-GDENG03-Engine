#pragma once

class Vector3
{
public:
	Vector3();
	Vector3(float vector_x, float vector_y, float vector_z);
	Vector3(const Vector3& vector);
	~Vector3() {}

	static Vector3 lerp(const Vector3& vector_a, const Vector3& vector_b, float coefficient);

	void operator =(const Vector3& vector);
	void operator +=(const Vector3& vector);
	Vector3 operator +(Vector3 vector);
	Vector3 operator *(float scalar);

	float x;
	float y;
	float z;
};