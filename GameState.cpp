//Stores and deals out the Game State (including board, turn, castling, EP possibillity, ...)
//Deals out a list of legal moves for a given position

#include "GameState.h"
#include "DataTypes.h"
#include <string>
#include <iostream>
#include <vector>

void GameState::initGame() {
	std::cout << "Initializing Game...\n";

	//initialize metadata
	currentPlayer = { Color::WHITE };

	//initialize board
	//rank 0: Black back rank(!)
	//rank 7: White back rank
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
	for (int i = 0; i < board[6].size(); i++) {
		Piece* p = new Piece();
		p->name = "PAWN";
		p->color= Color::WHITE;
		p->pos = { 6, i };
		p->type = PieceType::PAWN;

		p->hasMoved = false;
		p->hasMovedLastTurn = false;

		board[6][i].piece = p;
	}

	//black pawns
	for (int i = 0; i < board[1].size(); i++) {
		Piece* p = new Piece();
		p->name = "PAWN";
		p->color = Color::BLACK;
		p->pos = { 1, i };
		p->type = PieceType::PAWN;

		p->hasMoved = false;
		p->hasMovedLastTurn = false;

		board[1][i].piece = p;
	}
	
	//standartized vector storing the correct piece order of the back rank
	//so I dont have to type out the order twice in the later piece declarations
	std::vector<PieceType> backRow(8);
	std::vector<std::string> backRowNames(8);

	backRow = { PieceType::ROOK, PieceType::KNIGHT, PieceType::BISHOP, PieceType::QUEEN, 
		PieceType::KING, PieceType::BISHOP, PieceType::KNIGHT, PieceType::ROOK };
	backRowNames = { "ROOK", "KNIGHT", "BISHOP", "QUEEN",
		"KING", "BISHOP", "KNIGHT", "ROOK" };

	//create and place white back rank
	for (int i = 0; i < board[7].size(); i++) {
		Piece* p = new Piece();
		p->name = backRowNames[i];
		p->color = Color::WHITE;
		p->pos = { 7, i };
		p->type = backRow[i];

		p->hasMoved = false;
		p->hasMovedLastTurn = false;

		board[7][i].piece = p;
	}

	//black back rank
	for (int i = 0; i < board[0].size(); i++) {
		Piece* p = new Piece();
		p->name = backRowNames[i];
		p->color = Color::BLACK;
		p->pos = { 0, i };
		p->type = backRow[i];

		p->hasMoved = false;
		p->hasMovedLastTurn = false;

		board[0][i].piece = p;
	}

#if 0
	//debug pieces
	Piece* debugRook = new Piece();
	debugRook->name = "ROOK";
	debugRook->color = Color::WHITE;
	debugRook->pos = { 4, 4 };
	debugRook->type = PieceType::ROOK;
	debugRook->hasMoved = false;
	debugRook->hasMovedLastTurn = false;

	Piece* debugBishop = new Piece();
	debugBishop->name = "BISHOP";
	debugBishop->color = Color::BLACK;
	debugBishop->pos = { 4, 5 };
	debugBishop->type = PieceType::BISHOP;
	debugBishop->hasMoved = false;
	debugBishop->hasMovedLastTurn = false;

	board[4][4].piece = debugRook;
	board[4][5].piece = debugBishop;
#endif

	std::cout << "Initializing Game: success!\n";
}
void GameState::cleanUpBoard() {
	for (int i = 0; i < board.size(); i++) {
		for (Tile& t : board[i]) {
			delete t.piece;
			t.piece = nullptr;
		}
	}
}

std::vector<std::vector<Tile>>* GameState::getBoardPointer() {
	return &board;
}

Tile* GameState::getTilePointer(Position p) {
	if (p.x < 0 || p.x >= 8 || p.y < 0 || p.y >= 8) {
		return nullptr;
	}
	return &board[p.x][p.y];
}

Color GameState::getCurrentPlayer() { return currentPlayer; }

MoveType GameState::determineMoveType(Position target) {
	Tile* tile = getTilePointer(target);
	if (tile == nullptr) {
		return MoveType::DEBUG;
	}
	if (tile->piece == nullptr) {
		return MoveType::SIMPLE_MOVE;
	}
	else if (tile->piece->color != currentPlayer) {
		return MoveType::CAPTURE;
	}
	else {
		return MoveType::DEBUG;
	}
}

void GameState::setCurrentPlayer(const Color &color) { currentPlayer = color; }
	
void GameState::switchPlayer() {
	switch (currentPlayer) {
	case Color::WHITE:
		setCurrentPlayer(Color::BLACK);
		break;
	case Color::BLACK:
		setCurrentPlayer(Color::WHITE);
		break;
	}
}

void GameState::setPieceAtPosition(Position pos, Piece* p) {
	board[pos.x][pos.y].piece = p;
}

std::vector<Move> GameState::getLegalMoves(Position pos) {
	
	//nullptr check for position
	Tile* tile = getTilePointer(pos);
	if (tile == nullptr || tile->piece == nullptr) {
		legalMoves.clear();
		return legalMoves;
	}

	//find piece at the requested position and prepare vector for usage
	Piece* p = tile->piece;
	legalMoves.clear();
	if (p == nullptr) {return legalMoves;}

	//to use in the switch for adding moves to the return vector
	Color working_color = p->color;
	Move working_move;
	working_move.p_old = pos;

	//add legal moves to the vector
	switch (p->type) {

	case PieceType::ROOK:
		//cardinal directions
		addMovesInDirection(pos, 1, 0,	working_color);
		addMovesInDirection(pos, -1, 0, working_color);
		addMovesInDirection(pos, 0, 1,	working_color);
		addMovesInDirection(pos, 0, -1, working_color);
		break;

	case PieceType::BISHOP:
		//diagonals
		addMovesInDirection(pos, 1, 1,	working_color);
		addMovesInDirection(pos, 1, -1, working_color);
		addMovesInDirection(pos, -1, 1, working_color);
		addMovesInDirection(pos, -1, -1,working_color);
		break;

	case PieceType::QUEEN:
		//cardinal directions
		addMovesInDirection(pos, 1, 0,	working_color);
		addMovesInDirection(pos, -1, 0, working_color);
		addMovesInDirection(pos, 0, 1,	working_color);
		addMovesInDirection(pos, 0, -1, working_color);

		//diagonals
		addMovesInDirection(pos, 1, 1,	working_color);
		addMovesInDirection(pos, 1, -1, working_color);
		addMovesInDirection(pos, -1, 1,	working_color);
		addMovesInDirection(pos, -1, -1,working_color);
		break;

	
	case PieceType::KNIGHT:
		addMoveUnderCondition(pos, +2, +1, true);
		addMoveUnderCondition(pos, +2, -1, true);
		addMoveUnderCondition(pos, -2, +1, true);
		addMoveUnderCondition(pos, -2, -1, true);
		addMoveUnderCondition(pos, +1, +2, true);
		addMoveUnderCondition(pos, +1, -2, true);
		addMoveUnderCondition(pos, -1, +2, true);
		addMoveUnderCondition(pos, -1, -2, true);
		break;

	case PieceType::PAWN:

		//white pawns move up the board (-1), black down (+1)
		int direction;
		p->color == Color::WHITE ? direction = -1 : direction = 1;

		//I. Moving down the file
		
		working_move.p_new.x = pos.x + direction;
		working_move.p_new.y = pos.y;
		working_move.moveType = determineMoveType(working_move.p_new);

		if (getTilePointer(working_move.p_new)->piece == nullptr) {//tile is empty?
			legalMoves.push_back(working_move);

			if (p->hasMoved == false) {//not moved yet: pawn can move 1 more square!
				working_move.p_new.x = pos.x + (2 * direction);
				working_move.p_new.y = pos.y;
				working_move.moveType = determineMoveType(working_move.p_new);

				if (getTilePointer(working_move.p_new)->piece == nullptr) {//tile is empty?
					legalMoves.push_back(working_move);
				}
			}
		}

		//II. Capturing left or right
		addMoveUnderCondition(pos, direction, -1, determineMoveType({pos.x + direction, pos.y - 1}) == MoveType::CAPTURE);
		addMoveUnderCondition(pos, direction, +1, determineMoveType({pos.x + direction, pos.y + 1}) == MoveType::CAPTURE);

		//TODO: En passant & Promotion
		break;

	case PieceType::KING:
		addMoveUnderCondition(pos, +1, +1, true);
		addMoveUnderCondition(pos, +1, 0, true);
		addMoveUnderCondition(pos, +1, -1, true);
		addMoveUnderCondition(pos, 0, +1, true);
		addMoveUnderCondition(pos, 0, -1, true);
		addMoveUnderCondition(pos, -1, +1, true);
		addMoveUnderCondition(pos, -1, 0, true);
		addMoveUnderCondition(pos, -1, -1, true);
		break;
	}

	return legalMoves;
}

//Helper function for getLegalMoves
void GameState::addMovesInDirection(Position pos, int dx, int dy, Color working_color) {
	Position working_position = pos;
	Move working_move;
	working_move.p_old = pos;

	//increment in dx, dy direction...
	while (true) {
		working_position.x += dx;
		working_position.y += dy;

		//...until board edges are hit
		if (working_position.x < 0 || working_position.x >= board.size() || working_position.y < 0 || working_position.y >= board[0].size()) {
			break;
		}

		Piece* workingPiecePointer = GameState::getTilePointer(working_position)->piece;

		if (workingPiecePointer != nullptr) {//square not empty: halt
			if (workingPiecePointer->color == working_color) {//friendly piece: cant capture
				break;
			}
			else {//enemy piece: can capture but stop
				working_move.moveType = MoveType::CAPTURE;
				working_move.p_new = working_position;
				legalMoves.push_back(working_move);
				break;
			}
		}
		else {//square empty: continue
			working_move.moveType = MoveType::SIMPLE_MOVE;
			working_move.p_new = working_position;
			legalMoves.push_back(working_move);
		}
	}
}

//Helper function for getLegalMoves
void GameState::addMoveUnderCondition(Position pos, int dx, int dy, bool condition) {
	Move working_move;
	working_move.p_old = pos;
	working_move.p_new.x = pos.x + dx;
	working_move.p_new.y = pos.y + dy;

	if (condition && getTilePointer(working_move.p_new) != nullptr) {
		working_move.moveType = determineMoveType(working_move.p_new);

		if (working_move.moveType != MoveType::DEBUG) {	//this checks wether we would capture a friendly piece
														//strictly speaking this wouldn't be necessary because we check for friendly captures 
														//in the selection logic as well... but we want to display the legal moves array some day
			legalMoves.push_back(working_move);
		}
	}
}

void GameState::acceptMove(Move move) {
	Piece* used_piece = getTilePointer(move.p_old)->piece;
	switch (move.moveType) {
		case MoveType::CAPTURE:
			std::cout << "capture\n";
		case MoveType::SIMPLE_MOVE:
			std::cout << "simple move\n";
			setPieceAtPosition(move.p_old, nullptr);
			setPieceAtPosition(move.p_new, used_piece);

		case MoveType::CASTLE:
		case MoveType::EN_PASSANT:
			//TODO: Special Moves!
			break;
		case MoveType::DEBUG:
		default:
			std::cout << "GameState.acceptMove: Invalid move passed!\n";
			break;
	}

	std::cout << "Move made from: " << move.p_old.x << ", " << move.p_old.y <<
		" to: " << move.p_new.x << ", " << move.p_new.y << "!" << std::endl;
}

