#pragma once
#include"Vertex.h"
#include<d3d11.h>
#include<vector>

class AShape
{
public:
	AShape(Vertex* vertex_list, UINT vertex_count, D3D_PRIMITIVE_TOPOLOGY primitive_topology);
	~AShape();

	Vertex* getVertexList();
	UINT getVertexCount();
	D3D_PRIMITIVE_TOPOLOGY getTopology();

protected:
	Vertex* mVertexList = nullptr;
	UINT mVertexCount;
	D3D_PRIMITIVE_TOPOLOGY mTopology;
};