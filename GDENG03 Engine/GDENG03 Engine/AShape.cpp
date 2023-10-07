#include "AShape.h"

AShape::AShape(Vertex* vertex_list, UINT vertex_count, D3D_PRIMITIVE_TOPOLOGY primitive_topology) {
	mVertexList = new Vertex[vertex_count];
	mVertexCount = vertex_count;
	mTopology = primitive_topology;

	for (int i = 0; i < vertex_count; i++) {
		mVertexList[i] = vertex_list[i];
	}

	mIndexCount = 0;
}

AShape::AShape(Vertex* vertex_list, UINT vertex_count, unsigned int* index_list, UINT index_count) {
	mVertexList = new Vertex[vertex_count];
	mVertexCount = vertex_count;
	mTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	mIndexList = new unsigned int[index_count];
	mIndexCount = index_count;
}

AShape::~AShape() {
	delete[] mVertexList;
	if (mIndexList) delete[] mIndexList;
}

Vertex* AShape::getVertexList() {
	return mVertexList;
}

UINT AShape::getVertexCount() {
	return mVertexCount;
}

unsigned int* AShape::getIndexList() {
	return mIndexList;
}

UINT AShape::getIndexCount() {
	return mIndexCount;
}

D3D_PRIMITIVE_TOPOLOGY AShape::getTopology() {
	return mTopology;
}