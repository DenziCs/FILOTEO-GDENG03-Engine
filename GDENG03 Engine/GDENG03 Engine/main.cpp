/*
Nathaniel Francis S. Filoteo
GDENG03 X22
HO -- Input System and Scene Camera
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