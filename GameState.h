#ifndef GAMESTATE
#define GAMESTATE
#include <vector>
#include "DataTypes.h"

class GameState {
private:
	std::vector<std::vector<Tile>> board;
	Color currentPlayer;
	std::vector<Move> legalMoves;

	void addMovesInDirection(Position, int, int, Color);
	void addMoveUnderCondition(Position, int, int, bool);

	MoveType determineMoveType(Position);

public: 
	void initGame();
	void cleanUpBoard();

	std::vector<std::vector<Tile>>* getBoardPointer();
	Tile* getTilePointer(Position);
	Color getCurrentPlayer();
	std::vector<Move> getLegalMoves(Position);

	void acceptMove(Move);
	void setCurrentPlayer(const Color&);
	void switchPlayer();
	void setPieceAtPosition(Position, Piece*);
};

#endif

