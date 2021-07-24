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
	friend std::ostream& operator <<(std::ostream& out, const GameBoard& gb);
public:
	//Constructor used to create initial solutions board
	GameBoard(std::string fileName);
	
	int getValue(int row, int col) const;
	std::vector<std::vector<int>>* getBoard() const;
	void setValue(int row, int col, int value);
	void setFlag(int row, int col);
	void revealCell(int row, int col);

	bool isFlag(int row, int col) const;
	bool isVisible(int row, int col) const;
	bool isBomb(int row, int col) const;
	bool isClear(int row, int col) const;
	void printBoard() const;
private:
	std::ifstream readFile(std::string fileName);
	std::vector<std::vector<Cell>>* board;
	int rows;
	int cols;
};
#endif