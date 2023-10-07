#pragma once
#include"Vertex.h"
#include<d3d11.h>
#include<vector>

class AShape
{
public:
	AShape(Vertex* vertex_list, UINT vertex_count, D3D_PRIMITIVE_TOPOLOGY primitive_topology);
	AShape(Vertex* vertex_list, UINT vertex_count, unsigned int* index_list, UINT index_count);
	~AShape();

	Vertex* getVertexList();
	UINT getVertexCount();
	unsigned int* getIndexList();
	UINT getIndexCount();
	D3D_PRIMITIVE_TOPOLOGY getTopology();

protected:
	Vertex* mVertexList = nullptr;
	UINT mVertexCount;
	unsigned int* mIndexList = nullptr;
	UINT mIndexCount;
	D3D_PRIMITIVE_TOPOLOGY mTopology;
};