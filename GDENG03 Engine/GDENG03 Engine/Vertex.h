#pragma once
#include"Vector3.h"

class Vertex
{
public:
	Vertex();
	Vertex(float x, float y, float z);
	Vertex(Vector3 vertex_position, Vector3 vertex_color);
	~Vertex();

	Vector3 position;
	Vector3 color;
};