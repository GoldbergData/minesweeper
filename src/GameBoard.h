//this represent one board

#ifndef _GameBoard_h_
#define _GameBoard_h_

#include <string>
#include <vector>
#include <iostream>

class GameBoard {
	friend std::ostream& operator <<(std::ostream& out, const GameBoard& gb);
public:
	GameBoard(int rows, int cols);
	
	int getValue(int row, int col) const;
	void setValue(int row, int col, int value);
	void setFlag(int row, int col);
	bool isBomb(int row, int col) const; 
	bool isClear(int row, int col) const;
	void printBoard() const;
private:
	std::vector<std::vector<int>>* board;
	int rows;
	int cols;
};
#endif