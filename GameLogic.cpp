//Gets a clicked tile. Decides Action and updates GameState accordingly
#include "GameLogic.h"
#include "DataTypes.h"
#include <vector>
#include <iostream>

void GameLogic::initGameLogic(GameState* passedGameState) {
	std::cout << "Initializing GameLogic...\n";

	gameStatePointer = passedGameState;
	
	lastActionType = ActionType::FIRST_MOVE;
	lastSelection = { 0, 0 };
			
	std::cout << "Initializing GameLogic: success!\n";
}

//handles tile click arriving here
//TODO: verify the return values here work as intended!
ActionType GameLogic::handleTileClick(Position p) {
	if (p.x < 0 || p.x >= 8 || p.y < 0 || p.y >= 8) {
		return ActionType::INVALID;
	}

	if (lastActionType == ActionType::SELECT) {
		std::cout << "GameLogic.cpp: running potential move\n";
		runPotentialMove(lastSelection, p);
	}
	else {
		std::cout << "GameLogic.cpp: running potential select\n";
		runPotentialSelection(p);
	}

	return lastActionType;
}

void GameLogic::runPotentialSelection(Position p) {
	Tile* workingTilePointer = gameStatePointer->getTilePointer(p);
	Color currentPlayer = gameStatePointer->getCurrentPlayer();

	//check if klicked tile is an owned piece
	if (workingTilePointer->piece == nullptr || workingTilePointer->piece->color != currentPlayer) {
		//No owned piece: deselect/select nothing
		lastActionType = ActionType::DESELECT;
		std::cout << "GameLogic.cpp: Tile deselected, reason: ";
		if (workingTilePointer->piece == nullptr) {
			std::cout << "Piece was nullptr\n";
		}
		else {
			std::cout << "Piece belongs to opponent\n";
		}
	}
	else {
		//Owned piece: select working tile
		lastSelection = workingTilePointer->pos;
		lastActionType = ActionType::SELECT;
		std::cout << "GameLogic.cpp: Tile selected\n";
	}
}

void GameLogic::runPotentialMove(Position lastSelection, Position p) {
	//get legal moves for the current position from gamestate
	std::vector<Move> legal_moves = gameStatePointer->getLegalMoves(lastSelection);
	GameLogic::move_candidate.p_old = lastSelection;
	GameLogic::move_candidate.p_new = p;
	GameLogic::move_candidate.moveType = MoveType::DEBUG;

	bool flag_move_legal = false;

	//search until you find this move in the array
	for (const Move &m : legal_moves) {
		//Only works because we define bool operator== in DataTypes!
		if (m.p_old == lastSelection && m.p_new == p) {
			flag_move_legal = true;
			move_candidate.moveType = m.moveType;
			break;
		}
	}

	//if legal: make move with the piece in lastSelection, deselect it
	if (flag_move_legal) {
		std::cout << "GameLogic.cpp: Making a move, type: ";
		gameStatePointer->acceptMove(move_candidate);
		gameStatePointer->switchPlayer();
		lastActionType = ActionType::MOVE;
	}
	//No legal move? Could have been a select
	else if (gameStatePointer->getTilePointer(p)->piece != nullptr &&
		gameStatePointer->getTilePointer(p)->piece->color == gameStatePointer->getCurrentPlayer()) {
		lastSelection = p;
		lastActionType = ActionType::SELECT;
		std::cout << "GameLogic.cpp: Tile selected (instead of move)\n";
	}
	else {//no owned piece clicked
		lastActionType = ActionType::DESELECT;
		std::cout << "GameLogic.cpp: Tile deselected (instead of move), reason: No legal move, targeted piece: ";
		if (gameStatePointer->getTilePointer(p)->piece == nullptr) {
			std::cout << "Piece was nullptr\n";
		}
		else {
			std::cout << "x: " << gameStatePointer->getTilePointer(p)->piece->pos.x <<
				", y: " << gameStatePointer->getTilePointer(p)->piece->pos.y << std::endl;
		}
	}
}