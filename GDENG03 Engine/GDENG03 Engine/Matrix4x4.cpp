#include"Matrix4x4.h"

Matrix4x4::Matrix4x4() {
}

Matrix4x4::~Matrix4x4() {
}

void Matrix4x4::setIdentity() {
	::memset(mMatrix, 0.f, sizeof(float) * 16);

	/*
	for (int i = 0; i < 4; i++) {
		mMatrix[i][i] = 1.f;
	}
	*/

	mMatrix[0][0] = 1.f;
	mMatrix[1][1] = 1.f;
	mMatrix[2][2] = 1.f;
	mMatrix[3][3] = 1.f;
}

void Matrix4x4::setTranslation(float delta_x, float delta_y, float delta_z) {
	setIdentity();

	mMatrix[3][0] = delta_x;
	mMatrix[3][1] = delta_y;
	mMatrix[3][2] = delta_z;
}

void Matrix4x4::setTranslation(const Vector3& translate_vector) {
	setIdentity();

	mMatrix[3][0] = translate_vector.x;
	mMatrix[3][1] = translate_vector.y;
	mMatrix[3][2] = translate_vector.z;
}

void Matrix4x4::setOrthoProjection(float width, float height, float near_plane, float far_plane) {
	setIdentity();

	mMatrix[0][0] = 2.f / width;
	mMatrix[1][1] = 2.f / height;
	mMatrix[2][2] = 1.f / (far_plane - near_plane);
	mMatrix[3][2] = -near_plane / (far_plane - near_plane);
}

void Matrix4x4::setOrthoProjection(float right, float left, float bottom, float top, float near_plane, float far_plane) {
	setIdentity();

	mMatrix[0][0] = 2.f / (right - left);
	mMatrix[1][1] = 2.f / (top - bottom);
	mMatrix[2][2] = -2.f / (far_plane - near_plane);
	mMatrix[3][0] = -(right + left) / (right - left);
	mMatrix[3][1] = -(top + bottom) / (top - bottom);
	mMatrix[3][2] = -(far_plane + near_plane) / (far_plane - near_plane);
}