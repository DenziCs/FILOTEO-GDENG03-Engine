#pragma once
#include"APrimitive.h"

class ATriangle : public APrimitive
{
public:
	ATriangle(Vertex point1, Vertex point2, Vertex point3);
	~ATriangle();

	Vertex* getVertexList(int* vertex_count) override;
	void drawShape(UINT* vertex_index) override;
};