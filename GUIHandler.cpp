//Updates the GUI with requests from the other classes
#include "GUIHandler.h"
#include "GameState.h"
#include "DataTypes.h"
#include <iostream>

void GUIHandler::initGUIHandler() {
	std::cout << "Initializing GUIHandler...\n";

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Tile t = GameState::getTile(i, j);
			std::cout << t.piece << "      ";
		}
		std::cout << std::endl;
	}
}