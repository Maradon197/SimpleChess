//Start of the program flow
//General TODO:
//special moves (EP, Castling)
//promoting pawns
//checks + king cant be captured
//checkmate / game end
//board UI
//timer
//engine/AI

#include "Main.h"
#include "GameState.h"
#include "InputDetector.h"
#include "GameLogic.h"
#include "LegalMoveGenerator.h"
#include "GUIHandler.h"
#include "DataTypes.h"
#include <iostream>

int main() {
	//GameState: Stores game data
	GameState gameState;
	gameState.initGame();

	//InputDetector: Triggers user inferred actions
	InputDetector inputDetector;
	inputDetector.initDetection();

	//GameLogic: Works out the results of interactions
	GameLogic gameLogic;
	gameLogic.initGameLogic(&gameState);

	//GUI Handler: Updates Display
	GUIHandler gUIHandler;
	gUIHandler.initGUIHandler(&gameState);

	runGameCycle(&gameState, &inputDetector, &gameLogic, &gUIHandler);

	return 0;
}

void runGameCycle(GameState* gS, InputDetector* iD, GameLogic* gL, GUIHandler* gUIH) {
	//std::cout << "Main.cpp: runGameCycle started!\n";

	std::cout << "\n\n GAME BEGINS!";
	Tile* selectedTile = new Tile();
	gUIH->displayDebugBoard(gS->getBoardPointer());

	//GAME LOOP
	while (true) {
		
		//I. get input
		Position workingPosition = iD->getDebugUserInputPosition();

		//II. handle input
		if (gL->handleTileClick(workingPosition) != ActionType::INVALID) {//handleTileClick returns true iff the position was valid, this also runs handleTileClick

			//III. display update
			gUIH->displayDebugBoard(gS->getBoardPointer());
		}
		//IV. handle error
		else {
			std::cout << "Main.cpp: Invalid move!" << std::endl;
		}
	}

	//TODO: Game End
}