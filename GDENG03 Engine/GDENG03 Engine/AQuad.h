#pragma once
#include "APrimitive.h"

class AQuad : public APrimitive
{
public:
	AQuad(Vertex point1, Vertex point2, Vertex point3, Vertex point4);
	~AQuad();

	Vertex* getVertexList(int* vertex_count) override;
	void drawShape(UINT* vertex_index) override;
};