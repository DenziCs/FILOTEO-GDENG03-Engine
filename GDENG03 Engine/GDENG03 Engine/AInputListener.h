#pragma once

class AInputListener
{
public:
	virtual void onPress(int key) = 0;
	virtual void onRelease(int key) = 0;
};