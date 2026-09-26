//Start of the program flow
//init GameState
//		|
//		|(tile positions)
//		|
//init InputDetector
//		|
//		|(tile clicks)
//		|
//init GameLogic
//		|
//		|(command) 
//		|
//init LegalMoveGenerator
//		|
//		|(move or command)
//		|
//init GUI Handler
//		|
//		|(UI Update)
//		|
//User! (wait... do we have to init the user as well??)

#include "GameState.h"
#include "InputDetector.h"
#include "GameLogic.h"
#include "LegalMoveGenerator.h"
#include "GUIHandler.h"
#include "DataTypes.h"
#include <iostream>

int main() {
	//init GameState
	GameState gameState;
	gameState.initBoard();

	//init InputDetector
	InputDetector inputDetector;
	inputDetector.initDetection();

	//init GameLogic
	GameLogic gameLogic;
	gameLogic.initGameLogic();

	//init LegalMoveGenerator
	LegalMoveGenerator legalMoveGenerator;
	legalMoveGenerator.initLegalMoveGenerator();

	//init GUI Handler
	GUIHandler gUIHandler;
	gUIHandler.initGUIHandler();
	return 0;
}
