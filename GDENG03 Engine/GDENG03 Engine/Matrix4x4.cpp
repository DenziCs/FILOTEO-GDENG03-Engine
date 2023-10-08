#include"Matrix4x4.h"

Matrix4x4::Matrix4x4() {
}

Matrix4x4::~Matrix4x4() {
}

void Matrix4x4::setIdentity() {
	::memset(mMatrix, 0.f, sizeof(float) * 16);

	for (int i = 0; i < 4; i++) {
		mMatrix[i][i] = 1.f;
	}
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

void Matrix4x4::setScale(float factor_x, float factor_y, float factor_z) {
	setIdentity();

	mMatrix[0][0] = factor_x;
	mMatrix[1][1] = factor_y;
	mMatrix[2][2] = factor_z;
}

void Matrix4x4::setScale(const Vector3& scale_vector) {
	setIdentity();

	mMatrix[0][0] = scale_vector.x;
	mMatrix[1][1] = scale_vector.y;
	mMatrix[2][2] = scale_vector.z;
}

void Matrix4x4::setRotationX(float theta) {
	mMatrix[1][1] = cos(theta);
	mMatrix[1][2] = sin(theta);
	mMatrix[2][1] = -sin(theta);
	mMatrix[2][2] = cos(theta);
}

void Matrix4x4::setRotationY(float theta) {
	mMatrix[0][0] = cos(theta);
	mMatrix[0][2] = -sin(theta);
	mMatrix[2][0] = sin(theta);
	mMatrix[2][2] = cos(theta);
}

void Matrix4x4::setRotationZ(float theta) {
	mMatrix[0][0] = cos(theta);
	mMatrix[0][1] = sin(theta);
	mMatrix[1][0] = -sin(theta);
	mMatrix[1][1] = cos(theta);
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

void Matrix4x4::translate(float delta_x, float delta_y, float delta_z) {
	Matrix4x4 translator;
	translator.setTranslation(delta_x, delta_y, delta_z);
	*this *= translator;
}

void Matrix4x4::translate(const Vector3& translate_vector) {
	Matrix4x4 translator;
	translator.setTranslation(translate_vector);
	*this *= translator;
}

void Matrix4x4::scale(float factor_x, float factor_y, float factor_z) {
	Matrix4x4 scaleMatrix;
	scaleMatrix.setScale(factor_x, factor_y, factor_z);
	*this *= scaleMatrix;
}

void Matrix4x4::scale(const Vector3& scale_vector) {
	Matrix4x4 scaleMatrix;
	scaleMatrix.setScale(scale_vector);
	*this *= scaleMatrix;
}

void Matrix4x4::rotate(int axis, float theta) {
	Matrix4x4 rotationMatrix;
	switch (axis) {
	case 0:
		rotationMatrix.setIdentity();
		rotationMatrix.setRotationX(theta);
		break;
	case 1:
		rotationMatrix.setIdentity();
		rotationMatrix.setRotationY(theta);
		break;
	case 2:
		rotationMatrix.setIdentity();
		rotationMatrix.setRotationZ(theta);
		break;
	default:
		rotationMatrix.setIdentity();
	}

	*this *= rotationMatrix;
}

void Matrix4x4::operator *=(const Matrix4x4& matrix)
{
	Matrix4x4 out;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			out.mMatrix[i][j] =
				mMatrix[i][0] * matrix.mMatrix[0][j] +
				mMatrix[i][1] * matrix.mMatrix[1][j] +
				mMatrix[i][2] * matrix.mMatrix[2][j] +
				mMatrix[i][3] * matrix.mMatrix[3][j];
		}
	}
	setMatrix(out);
}

void Matrix4x4::setMatrix(const Matrix4x4& matrix)
{
	::memcpy(mMatrix, matrix.mMatrix, sizeof(float) * 16);
}