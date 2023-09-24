#include "Vertex.h"

Vertex::Vertex() {
	position.x = 0;
	position.y = 0;
	position.z = 0;

	position1.x = 0;
	position1.y = 0;
	position1.z = 0;

	color.x = 0;
	color.y = 0;
	color.z = 0;

	color1.x = 0;
	color1.y = 0;
	color1.z = 0;
}

Vertex::Vertex(float x, float y, float z) {
	position.x = x;
	position.y = y;
	position.z = z;

	position.x = x;
	position.y = y;
	position.z = z;

	color.x = 0;
	color.y = 0;
	color.z = 0;

	color1.x = 0;
	color1.y = 0;
	color1.z = 0;
}

Vertex::Vertex(Vector3 vertex_position, Vector3 vertex_color) {
	position.x = vertex_position.x;
	position.y = vertex_position.y;
	position.z = vertex_position.z;

	position1.x = vertex_position.x;
	position1.y = vertex_position.y;
	position1.z = vertex_position.z;

	color.x = vertex_color.x;
	color.y = vertex_color.y;
	color.z = vertex_color.z;

	color1.x = vertex_color.x;
	color1.y = vertex_color.y;
	color1.z = vertex_color.z;
}

Vertex::Vertex(Vector3 vertex_position_0, Vector3 vertex_position_1, Vector3 vertex_color) {
	position.x = vertex_position_0.x; 
	position.y = vertex_position_0.y; 
	position.z = vertex_position_0.z; 

	position1.x = vertex_position_1.x; 
	position1.y = vertex_position_1.y; 
	position1.z = vertex_position_1.z; 

	color.x = vertex_color.x;
	color.y = vertex_color.y;
	color.z = vertex_color.z;

	color1.x = vertex_color.x;
	color1.y = vertex_color.y;
	color1.z = vertex_color.z;
}

Vertex::Vertex(Vector3 vertex_position_0, Vector3 vertex_position_1, Vector3 vertex_color_0, Vector3 vertex_color_1) {
	position.x = vertex_position_0.x;
	position.y = vertex_position_0.y;
	position.z = vertex_position_0.z;

	position1.x = vertex_position_1.x;
	position1.y = vertex_position_1.y;
	position1.z = vertex_position_1.z;

	color.x = vertex_color_0.x;
	color.y = vertex_color_0.y;
	color.z = vertex_color_0.z;

	color1.x = vertex_color_1.x;
	color1.y = vertex_color_1.y;
	color1.z = vertex_color_1.z;
}

Vertex::~Vertex() {}