#ifndef MAIN
#define MAIN

#include "GameState.h"
#include "InputDetector.h"
#include "GameLogic.h"
#include "LegalMoveGenerator.h"
#include "GUIHandler.h"

int main();
void runGameCycle(GameState*, InputDetector*, GameLogic*, GUIHandler*);
#endif
