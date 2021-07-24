//this represent one board

#ifndef _GameManager_h_
#define _GameManager_h_

#include <string>
#include <vector>
#include "GameBoard.h"

class GameManager {
public:
	GameManager(std::string fileName);
	bool isWinner();
	bool isGameOver();
private:
	GameBoard* createSolutionBoard(std::string fileName);
	//solution -> fill with content
	GameBoard* createDisplayBoard();

    GameBoard* solution;
	GameBoard* display;
};
#endif