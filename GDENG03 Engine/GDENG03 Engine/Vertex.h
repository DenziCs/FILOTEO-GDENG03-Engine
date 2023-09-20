#pragma once
#include"Vector3.h"

class Vertex
{
public:
	Vertex();
	Vertex(float x, float y, float z);
	~Vertex();
	Vector3 position;
};