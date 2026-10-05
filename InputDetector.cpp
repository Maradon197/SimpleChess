//detects User Input and passes it to GameLogic

#include "InputDetector.h"
#include <iostream>
#include <limits>

void InputDetector::initDetection() {
	std::cout << "Initializing InputDetector: success!\n";
}

Position InputDetector::getDebugUserInputPosition() {
	int x, y;//1st target coordinates
	std::cout << "InputDetector.cpp: Input tile coordinates from x: (0-7), y: (0-7)\n";
	std::cin >> x >> y;

	if (!std::cin) {
		std::cin.clear();  // Clear the fail state
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Flush the buffer
		return { -1, -1 };
	}

	//check for extra input on the same line
	char extra;
	if (std::cin.get(extra) && extra != '\n') {//peek at the next symbol in the buffer
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  //flush buffer
		return { -1, -1 };
	}

	Position p;
	p.x = x;
	p.y = y;

	return p;
}
//TODO: Add real input detection