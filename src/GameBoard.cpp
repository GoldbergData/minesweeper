/**
 * @file GameBoard.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-07-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

//Joshua Goldberg, Matthew Kim

//this class is the implementation...

#include <string>
#include <vector>
#include "GameBoard.h"

using namespace std;

GameBoard::GameBoard(int rows, int cols) {
    this->rows = rows;
    this->cols = cols;
    board = new vector<vector<int>>;
    for (int i = 0; i < rows; i++) {
        vector<int> newRowCellObjects(cols, 0); //12 col vector
        board->push_back(newRowCellObjects); //5x
    }
}

int GameBoard::getValue(int row, int col) const {
    return (*board)[row][col];
}

void GameBoard::setValue(int row, int col, int value) {
    (*board)[row][col] = value;
}

void GameBoard::setFlag(int row, int col) {
    setValue(row, col, -1);
}

bool GameBoard::isBomb(int row, int col) const {
    return getValue(row, col) == 9;
}

bool GameBoard::isClear(int row, int col) const {
    return getValue(row, col) == 0;
}

ostream& operator <<(ostream& out, const GameBoard& gb) {
    for (int i = 0; i < gb.board->size(); i++) {
        for (int j = 0; j < (*gb.board)[i].size(); i++) {
            out << gb.getValue(i, j);
        }
        out << endl;
    }
    return out;
}