//this represent one board

#ifndef _GameManager_h_
#define _GameManager_h_

#include <string>
#include <vector>
#include "GameBoard.h"

struct Point {
	int row;
	int col;
};

class GameManager {
public:
	GameManager(std::string fileName);
	GameManager(int level);

	void clickCell(int row, int col, vector<Point>& openedCell);
	void clickCellGame(int row, int col);
	void unClickCell(vector<Point> openedCell);

	int getValue(int row, int col) const;
	void setFlag(int row, int col);
	bool isFlag(int row, int col);
	bool isVisible(int row, int col);
	
	bool isGameEnd();
	bool isWinner();
	void printBoard();
	int getRows() const;
	int getCols() const;
	int gameSolver(int clickCount = 0);
private:
    GameBoard* board;
	bool gameEnd;
	bool won;
	void clickCellHelper(int row, int col, vector<Point>& openedCell);
	void clickCellGameHelper(int row, int col);
	void checkEndGame(bool bombClicked);
	void addPoint(int row, int col, vector<Point>& openedCell);

	void printSolBoard();
	void printDispBoard();
	
};
#endif