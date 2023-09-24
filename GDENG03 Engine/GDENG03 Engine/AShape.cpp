#include "AShape.h"

AShape::AShape(Vertex* vertex_list, UINT vertex_count, D3D_PRIMITIVE_TOPOLOGY primitive_topology) {
	mVertexList = new Vertex[vertex_count];
	mVertexCount = vertex_count;
	mTopology = primitive_topology;

	for (int i = 0; i < vertex_count; i++) {
		mVertexList[i] = vertex_list[i];
	}
}

AShape::~AShape() {
	delete[] mVertexList;
}

Vertex* AShape::getVertexList() {
	return mVertexList;
}

UINT AShape::getVertexCount() {
	return mVertexCount;
}

D3D_PRIMITIVE_TOPOLOGY AShape::getTopology() {
	return mTopology;
}