#include"APrimitive.h"

APrimitive::APrimitive() {}

APrimitive::~APrimitive() {
	delete[] mVertexList;
}