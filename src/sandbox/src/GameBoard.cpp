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
#include <iostream>
#include <fstream>
#include "GameBoard.h"

using namespace std;

ifstream GameBoard::readFile(string fileName) {
    ifstream input;
    input.open(fileName);
    string line;
    getline(input, line);
    rows = stoi(line);
    getline(input, line);
    cols = stoi(line);
    return input;
}

//Constructor used to create initial solutions board
GameBoard::GameBoard(string fileName) : board(nullptr), rows(0), cols(0) {
    ifstream input = readFile(fileName);
    string line;
    board = new vector<vector<Cell> >;
    for (int i = 0; i < rows; i++) {
        getline(input, line);
        vector<Cell> rowVector;
        for (int j = 0; j < cols; j++) {
            int num = stoi(line.substr(j, 1));
            rowVector.push_back(Cell(num));
        }
        board->push_back(rowVector);
    }
    input.close();
}

int GameBoard::getValue(int row, int col) const {
    return (*board)[row][col].value;
}

int GameBoard::getRows() const {
    return rows;
}

int GameBoard::getCols() const {
    return cols;
}

void GameBoard::setValue(int row, int col, int value) {
    (*board)[row][col].value = value;
}

void GameBoard::setFlag(int row, int col) {
    (*board)[row][col].flag = !(*board)[row][col].flag;
}

void GameBoard::revealCell(int row, int col) {
    (*board)[row][col].visible = true;
}

bool GameBoard::isFlag(int row, int col) const {
    return (*board)[row][col].flag;
}

bool GameBoard::isVisible(int row, int col) const {
    return (*board)[row][col].visible;
}

bool GameBoard::isBomb(int row, int col) const {
    return (*board)[row][col].value == 9;
}

bool GameBoard::hasNeighborBombs(int row, int col) const {
    return !isClear(row, col) && !isBomb(row, col);
}

bool GameBoard::isClear(int row, int col) const {
    return (*board)[row][col].value == 0;
}

bool GameBoard::inBounds(int row, int col) const {
    return (row >= 0 && row < getRows()) && (col >= 0 && col < getCols());
}

ostream& operator <<(ostream& out, const GameBoard& gb) {
    out << "Solution Board:" << endl;
    for (int i = 0; i < gb.board->size(); i++) {
        for (int j = 0; j < (*gb.board)[i].size(); j++) {
                if (gb.isBomb(i, j)) {
                    out << "B" << " ";
                } else if (gb.isClear(i, j)) {
                    out << "-" << " ";
                } else {
                    out << gb.getValue(i, j) << " ";
                }
        }
        out << endl;
    }
    out << endl;
    out << "Display Board:" << endl;
    for (int i = 0; i < gb.board->size(); i++) {
        for (int j = 0; j < (*gb.board)[i].size(); j++) {
            if (!gb.isVisible(i, j)) {
                if (gb.isFlag(i, j)) {
                    out << "F ";
                } else {
                    out << "X ";
                }
            } else {
                if (gb.isBomb(i, j)) {
                    out << "B" << " ";
                } else if (gb.isClear(i, j)) {
                    out << "-" << " ";
                } else {
                    out << gb.getValue(i, j) << " ";
                }
            }
        }
        out << endl;
    }
    return out;
}