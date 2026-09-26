#ifndef GAMESTATE
#define GAMESTATE
#include <vector>
#include "DataTypes.h"

class GameState {
private:
	std::vector<std::vector<Tile>> board;
public: 
	void initBoard();
	void cleanUpBoard();
	std::vector<std::vector<Tile>> getBoard();
	Tile getTile(int x, int y);
};

#endif

