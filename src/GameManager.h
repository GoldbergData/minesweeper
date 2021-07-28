//this represent one board

#ifndef _GameManager_h_
#define _GameManager_h_

#include <string>
#include <vector>
#include "GameBoard.h"

class GameManager {
public:
	GameManager(std::string fileName);

	/**
	 * @brief Recursive backtracking method to reveal cells.
	 * 
	 * @param row 
	 * @param col 
	 */
	void clickCell(int row, int col);
	int getValue(int row, int col) const;
	void setFlag(int row, int col);
	bool isVisible(int row, int col);
	bool isGameEnd();
	bool isWinner();
	void printBoard();
	int getRows() const;
	int getCols() const;	
private:
    GameBoard* board;
	bool gameEnd;
	bool won;
	void clickCellHelper(int row, int col);
	void checkEndGame(bool bombClicked);
};
#endif