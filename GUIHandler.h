#ifndef GUIHANDLER
#define GUIHANDLER
#include "DataTypes.h"
#include "GameState.h"
#include <vector>

class GUIHandler {
public:
	void initGUIHandler(GameState*);

	void displayDebugBoard(std::vector<std::vector<Tile>>*);
	void selectTileAtPosition(Position);
	void displayLegalMovesAtPositions(std::vector<Position>);
	void runDeselection();
};
#endif