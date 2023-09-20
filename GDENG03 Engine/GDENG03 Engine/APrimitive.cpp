#include"APrimitive.h"
#include<iostream>

APrimitive::APrimitive() {}

APrimitive::~APrimitive() {
	delete[] mVertexList;
}