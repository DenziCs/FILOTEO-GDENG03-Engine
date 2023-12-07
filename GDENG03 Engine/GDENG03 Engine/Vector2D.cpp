#include"Vector2D.h"

Vector2D::Vector2D() {
	x = 0;
	y = 0;
}

Vector2D::Vector2D(float vector_x, float vector_y) {
	x = vector_x;
	y = vector_y;
}

Vector2D::Vector2D(const Vector2D& vector) {
	x = vector.x;
	y = vector.y;
}

Vector2D Vector2D::lerp(const Vector2D& vector_a, const Vector2D& vector_b, float coefficient) {
	Vector2D resultVector;

	resultVector.x = vector_a.x * (1.f - coefficient) + vector_b.x * coefficient;
	resultVector.y = vector_a.y * (1.f - coefficient) + vector_b.y * coefficient;

	return resultVector;
}

void Vector2D::operator =(const Vector2D& vector) {
	x = vector.x;
	y = vector.y;
}

void Vector2D::operator +=(const Vector2D& vector) {
	x += vector.x;
	y += vector.y;
}

Vector2D Vector2D::operator +(Vector2D vector) {
	return Vector2D(x + vector.x, y + vector.y);
}

Vector2D Vector2D::operator *(float scalar) {
	return Vector2D(scalar * x, scalar * y);
}