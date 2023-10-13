#pragma once

class Point
{
public:
	Point();
	Point(int abscissa, int ordinate);
	Point(const Point* point);
	~Point() {}

private:
	int x;
	int y;
};