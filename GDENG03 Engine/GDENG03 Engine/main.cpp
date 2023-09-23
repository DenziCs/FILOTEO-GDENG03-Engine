/*
Nathaniel Francis S. Filoteo
GDENG03 X22
HO -- Exploring the Pixel Shader and Basic Animation with the Constant Buffer
*/

#include"AppWindow.h"

int main() {
	AppWindow game;

	if (game.initialize()) {
		while (game.isRunning()) {
			game.broadcast();
		}
	}

	return 0;
}