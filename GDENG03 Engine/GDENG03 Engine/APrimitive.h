#pragma once
#include"Vertex.h"
#include<d3d11.h>
#include<vector>

class APrimitive
{
public:
	APrimitive();
	~APrimitive();

	virtual Vertex* getVertexList(int* vertex_count) = 0;
	virtual void drawShape(UINT* vertex_index) = 0;

protected:
	Vertex* mVertexList = nullptr;
};