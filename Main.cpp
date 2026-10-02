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
	std::cout << "Main.cpp: runGameCycle started!\n";

	std::cout << "\n\n GAME BEGINS!";
	Tile* selectedTile = new Tile();
	
	gUIH->displayDebugBoard(gS->getBoardPointer());
	
	Position workingPosition = iD->getDebugUserInputPosition();

	//handleTileClick returns true iff the position was valid
	//TODO: Verify this works!
	if (gL->handleTileClick(workingPosition) != ActionType::INVALID) {//this also runs handleTileClick
		
		//TODO: make logic for this correct
		switch (gS->getCurrentPlayer()) {
			case Color::WHITE: 
				gS->setCurrentPlayer(Color::BLACK);
				break;
			case Color::BLACK: 
				gS->setCurrentPlayer(Color::WHITE);
				break;
		}
	}
	else {
		//TODO: error handling
	}
}