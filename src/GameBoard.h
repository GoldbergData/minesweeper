//this represent one board

#ifndef _GameBoard_h_
#define _GameBoard_h_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

struct Cell {
	int value;
	bool flag;
	bool visible;

	Cell(int value) {
		this->value = value;
		flag = false;
		visible = false;
	}
};

class GameBoard {
public:
	GameBoard(int bNum, int rows, int cols);
	int getValue(int row, int col) const;
	int getRows() const;
	int getCols() const;
	void setValue(int row, int col, int value);
	void setFlag(int row, int col);
	void revealCell(int row, int col);
	void closeCell(int row, int col);
	bool isFlag(int row, int col) const;
	bool isVisible(int row, int col) const;
	bool isBomb(int row, int col) const;
	bool hasNeighborBombs(int row, int col) const;	
	bool isClear(int row, int col) const;
	bool inBounds(int row, int col) const;
	void printBoard(bool displayBoard) const;
private:
	int countNeighborBombs(int row, int col);
	std::vector<std::vector<Cell> >* board;
	int rows;
	int cols;
};
#endif