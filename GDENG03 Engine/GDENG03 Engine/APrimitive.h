#pragma once
#include<vector>
#include"Vertex.h"
#include"AVertexBuffer.h"

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