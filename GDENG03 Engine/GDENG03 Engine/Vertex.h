#pragma once
#include"Vector3.h"

class Vertex
{
public:
	Vertex();
	Vertex(Vector3 vertex_position_0, Vector3 vertex_color_0, Vector3 vertex_color_1);
	~Vertex();

	Vector3 position;
	Vector3 color;
	Vector3 color1;
};