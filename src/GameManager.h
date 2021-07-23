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
	void createSolutionBoard(std::string fileName);
	//solution -> fill with content
	void createDisplayBoard();

    GameBoard* solution;
	GameBoard* display;
};
#endif