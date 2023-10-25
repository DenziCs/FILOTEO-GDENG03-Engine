#pragma once

class GlobalProperties
{
public:
	static void setActiveCubes(bool flag);
	static void setBackgroundColor(float red, float green, float blue);

	static bool IS_CUBE_MOVEMENT_ON;
	static float BACKGROUND_COLOR[3];
};