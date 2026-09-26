#ifndef DATATYPES
#define DATATYPES

enum class PieceType{ PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING};
enum class Color{ BLACK, WHITE};

struct Position {
	int x;
	int y;
};

struct Piece {
	PieceType type;
	Color color;
	Position pos;
	bool hasMoved;			//for castling: neither king nor rook must have moved
	bool hasMovedLastTurn;	//for EP: Pawns can only capture EP (en passant) if their target has moved last turn
};

struct Tile {
	Position pos;
	Piece* piece;
};

#endif