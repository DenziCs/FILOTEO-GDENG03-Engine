#include"AQuad.h"
#include"AGraphicsEngine.h"
#include"ADeviceContext.h"

AQuad::AQuad(Vertex point1, Vertex point2, Vertex point3, Vertex point4) : APrimitive() {
	this->mVertexList = new Vertex[4];

	this->mVertexList[0] = point1;
	this->mVertexList[1] = point2;
	this->mVertexList[2] = point3;
	this->mVertexList[3] = point4;
}

AQuad::~AQuad() {}

Vertex* AQuad::getVertexList(int* vertex_count) {
	*vertex_count = 4;
	return this->mVertexList;
}

void AQuad::drawShape(UINT* vertex_index) {
	AGraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleStrip(4, *vertex_index);
	*vertex_index += 4;
}