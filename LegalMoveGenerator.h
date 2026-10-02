#ifndef LEGALMOVEGENERATOR
#define LEGALMOVEGENERATOR

#include "DataTypes.h"
#include <vector>

class LegalMoveGenerator {
public: 
	void initLegalMoveGenerator();
	std::vector<Position> calculateLegalMoves();
};
#endif