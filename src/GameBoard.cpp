/**
 * @file GameBoard.h
 * @author Joshua Goldberg (j.goldberg4674@edmail.edcc.edu), Matthew Kim 
 * (m.kim3007@edmail.edcc.edu)
 * @brief Implementation of class GameBoard.
 * 
 * @version 0.1
 * @date 2021-07-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <time.h>
#include "GameBoard.h"
#include "lib132.h"

using namespace std;

//Constructor used to create initial solutions board
GameBoard::GameBoard(int bNum, int rows, int cols) : board(nullptr), rows(rows), cols(cols) {
    board = new vector<vector<Cell> >;

    //create game board of 0's
    for (int i = 0; i < rows; i++) {
        vector<Cell> rowVector;
        for (int j = 0; j < cols; j++) {
            rowVector.push_back(Cell(0));
        }
        board->push_back(rowVector);
    }
    // Random seed so different board is generated when constructor is called
    srand(time(0));

    //randomly place bombs
    for(int i = 0; i < bNum; i++) { //# of bombs on board
        int row = rand() % rows;
        int col = rand() % cols;
        while (getValue(row, col) != 0) { //checks if the space is empty
            row = rand() % rows;
            col = rand() % cols;
        }
        setValue(row, col, 9);
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!isBomb(i, j)) {
                int countBombs = countNeighborBombs(i, j);
                setValue(i, j, countBombs);
            }
        }
    }
}

int GameBoard::countNeighborBombs(int row, int col) {
    int sum = 0;
    for (int i = row - 1; i <= row + 1; i++ ) {
        for (int j = col - 1; j <= col + 1; j++) {
            if (inBounds(i, j) && !(i == row && j == col) && isBomb(i, j)) {
                sum++;
            }
        }
    }
    return sum;
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

void GameBoard::closeCell(int row, int col) {
    (*board)[row][col].visible = false;
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
    return (row >= 0 && row < rows) && (col >= 0 && col < cols);
}

void GameBoard::printBoard(bool displayBoard) const {
    cout << (displayBoard ? "Display Board:" : "Solution Board:") << endl;
    for (int i = 0; i < getRows(); i++) {
        for (int j = 0; j < getCols(); j++) {
            if (displayBoard && !isVisible(i, j)) {
                if (isFlag(i, j)) {
                    cout << "F ";
                } else {
                    cout << "X ";
                }
            } else {
                if (isBomb(i, j)) {
                    cout << "B ";
                } else if (isClear(i, j)) {
                    cout << "- ";
                } else {
                    cout << getValue(i, j) << " ";
                }
            }
        }
        cout << endl;
    }
}
