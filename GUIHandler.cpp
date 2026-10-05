//Updates the GUI with requests from the other classes
#include "GUIHandler.h"
#include "GameState.h"
#include "DataTypes.h"
#include <vector>
#include <string>
#include <iostream>

void GUIHandler::initGUIHandler(GameState* gameState) {
	std::cout << "Initializing GUIHandler...\n";
}

void GUIHandler::displayDebugBoard(std::vector<std::vector<Tile>>* board) {
	std::cout << "\n\n BOARD INTERNAL STATE: \n\n";

	//iterate over all board elements. the "->" operator dereferences the matrix pointer automatically
	for (int i = 0; i < board->size(); i++) {
		for (int j = 0; j < (*board)[i].size(); j++) {
			//the piece at this position is allowed to be empty 
			//so we would get a Nullpointer Exception
			if ((*board)[i][j].piece == nullptr) {
				std::cout << "EMPTY";
			}
			else {//board[i][j] is not empty
				std::cout << (*board)[i][j].piece->name;
			}
			std::cout << "   ";
		}
		std::cout << std::endl; 
		std::cout << std::endl;
	}
}

void GUIHandler::selectTileAtPosition(Position pos) {

}

void GUIHandler::displayLegalMovesAtPositions(std::vector<Position> pos) {

}

void GUIHandler::runDeselection() {

}