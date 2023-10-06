#include "Vector3.h"

Vector3::Vector3() {
	x = 0.f;
	y = 0.f;
	z = 0.f;
}

Vector3::Vector3(float vector_x, float vector_y, float vector_z) {
	x = vector_x;
	y = vector_y;
	z = vector_z;
}

Vector3::Vector3(const Vector3& vector) {
	x = vector.x;
	y = vector.y;
	z = vector.z;
}