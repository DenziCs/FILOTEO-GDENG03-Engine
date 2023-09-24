#include "Vertex.h"

Vertex::Vertex() {
	position.x = 0;
	position.y = 0;
	position.z = 0;

	color.x = 0;
	color.y = 0;
	color.z = 0;
}

Vertex::Vertex(float x, float y, float z) {
	position.x = x;
	position.y = y;
	position.z = z;

	color.x = 0;
	color.y = 0;
	color.z = 0;
}

Vertex::Vertex(Vector3 vertex_position, Vector3 vertex_color) {
	position.x = vertex_position.x;
	position.y = vertex_position.y;
	position.z = vertex_position.z;

	color.x = vertex_color.x;
	color.y = vertex_color.y;
	color.z = vertex_color.z;
}

Vertex::~Vertex() {}