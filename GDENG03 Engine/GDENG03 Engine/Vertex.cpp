#include "Vertex.h"

Vertex::Vertex() {
	position.x = 0;
	position.y = 0;
	position.z = 0;
}

Vertex::Vertex(float x, float y, float z) {
	position.x = x;
	position.y = y;
	position.z = z;
}

Vertex::~Vertex() {}