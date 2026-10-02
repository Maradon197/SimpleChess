#ifndef DATATYPES
#define DATATYPES
#include <string>

enum class PieceType{ PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };
enum class Color{ BLACK, WHITE };//used for both pieces and player moving rights
enum class ActionType{ SELECT, DESELECT, MOVE, FIRST_MOVE, INVALID };
enum class MoveType{ SIMPLE_MOVE, CAPTURE, CASTLE, EN_PASSANT, DEBUG };

struct Position {
	int x{};
	int y{};

	//defining == operator to use for checking wether positions match
	bool operator==(const Position& pos) const{
		return (x == pos.x && y == pos.y);
	}
};

struct Piece {
	std::string name{};
	PieceType type{};
	Color color{};
	Position pos{};
	bool hasMoved = false;			//for castling: neither king nor rook must have moved
	bool hasMovedLastTurn = false;	//for EP: Pawns can only capture EP (en passant) if their target has moved last turn
};

struct Tile {
	Position pos{};
	Piece* piece = nullptr;
};

struct Move {
	Position p_old{};
	Position p_new{};
	MoveType moveType{};
};

#endif