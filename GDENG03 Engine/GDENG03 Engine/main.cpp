/*
Nathaniel Francis S. Filoteo
GDENG03 XX22
MCO: Comprehensive Exam
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