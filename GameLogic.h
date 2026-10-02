#ifndef GAMELOGIC
#define GAMELOGIC
		
#include "DataTypes.h"
#include "GameState.h"

class GameLogic {
private:
	ActionType lastActionType;
	Position lastSelection;
	GameState* gameStatePointer;

	Move move_candidate;

	void runPotentialSelection(Position);
	void runPotentialMove(Position, Position);
public: 
	void initGameLogic(GameState*);
	//returns 0 if position is invalid
	ActionType handleTileClick(Position);
};

#endif