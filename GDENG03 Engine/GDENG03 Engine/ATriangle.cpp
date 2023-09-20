#include"ATriangle.h"
#include"AGraphicsEngine.h"
#include"ADeviceContext.h"

ATriangle::ATriangle(Vertex point1, Vertex point2, Vertex point3) : APrimitive() {
	this->mVertexList = new Vertex[3];

	this->mVertexList[0] = point1;
	this->mVertexList[1] = point2;
	this->mVertexList[2] = point3;
}

ATriangle::~ATriangle() {}

Vertex* ATriangle::getVertexList(int* vertex_count) {
	*vertex_count = 3;
	return this->mVertexList;
}

void ATriangle::drawShape(UINT* vertex_index) {
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleList(3, *vertex_index);
	*vertex_index += 3;
}