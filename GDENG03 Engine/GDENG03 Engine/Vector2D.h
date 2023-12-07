#pragma once

class Vector2D
{
public:
	Vector2D();
	Vector2D(float vector_x, float vector_y);
	Vector2D(const Vector2D& vector);
	~Vector2D() {}

	static Vector2D lerp(const Vector2D& vector_a, const Vector2D& vector_b, float coefficient);

	void operator =(const Vector2D& vector);
	void operator +=(const Vector2D& vector);
	Vector2D operator +(Vector2D vector);
	Vector2D operator *(float scalar);

	float x;
	float y;
};