//Stores and deals out the Game State (including board, turn, castling, EP possibillity, ...)

#include "GameState.h"
#include "DataTypes.h"
#include <string>
#include <iostream>
#include <vector>

void GameState::initBoard() {
	std::cout << "Initializing Board...\n";

	//initialize board (declared in GameState.h)
	int rows = 8;
	int cols = 8;
	board.assign(rows, std::vector<Tile>(cols));

	//Hand Tiles their positions in case we need them
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[0].size(); j++) {
			board[i][j].pos = { i, j };
		}
	}

	//create and place white pawns
	for (int i = 0; i < board[1].size(); i++) {
		Piece* p = new Piece();
		p->color= Color::WHITE;
		p->pos = { 1, i };
		p->type = PieceType::PAWN;

		p->hasMoved = false;
		p->hasMovedLastTurn = false;

		board[1][i].piece = p;
	}

	//black pawns
	for (int i = 0; i < board[6].size(); i++) {
		Piece* p = new Piece();
		p->color = Color::BLACK;
		p->pos = { 6, i };
		p->type = PieceType::PAWN;

		p->hasMoved = false;
		p->hasMovedLastTurn = false;

		board[1][i].piece = p;
	}
	
	//standartized vector storing the correct piece order of the back rank
	//so I dont have to type out the order twice in the later piece declarations
	std::vector<PieceType> backRow(8);
	backRow = { PieceType::ROOK, PieceType::KNIGHT, PieceType::BISHOP, PieceType::QUEEN, 
		PieceType::KING, PieceType::BISHOP, PieceType::KNIGHT, PieceType::ROOK };

	//create and place White Back rank
	for (int i = 0; i < board[0].size(); i++) {
		Piece* p = new Piece();
		p->color = Color::WHITE;
		p->pos = { 0, i };
		p->type = backRow[i];

		p->hasMoved = false;
		p->hasMovedLastTurn = false;
	}

	//Black back rank
	for (int i = 0; i < board[7].size(); i++) {
		Piece* p = new Piece();
		p->color = Color::BLACK;
		p->pos = { 7, i };
		p->type = backRow[i];

		p->hasMoved = false;
		p->hasMovedLastTurn = false;
	}

	std::cout << "Initializing Board: success!\n";
}
void GameState::cleanUpBoard() {
	for (int i = 0; i < board.size(); i++) {
		for (Tile t : board[i]) {
			delete t.piece;
		}
	}
}

std::vector<std::vector<Tile>> GameState::getBoard() {
	return board;
}

Tile GameState::getTile(int x, int y) {
	return board[x][y];
}