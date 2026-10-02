//detects User Input and passes it to GameLogic

#include "InputDetector.h"
#include <iostream>

void InputDetector::initDetection() {
	std::cout << "Initialized InputDetector...\n";
}

Position InputDetector::getDebugUserInputPosition() {
	int x, y;//1st target coordinates
	std::cout << "Input tile coordinates from x: (0-7), y: (0-7)\n";
	std::cin >> x >> y;

	if (!std::cin) {
		return { -1, -1 };
	}

	Position p;
	p.x = x;
	p.y = y;

	return p;
}
//TODO: Add real input detection