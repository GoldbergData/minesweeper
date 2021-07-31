/**
 * @file GameManager.cpp
 * @author Joshua Goldberg (j.goldberg4674@edmail.edcc.edu), Matthew Kim 
 * (m.kim3007@edmail.edcc.edu)
 * @brief Implementation of class GameManager.
 * @version 0.1
 * @date 2021-07-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <string>
#include <vector>
#include "GameBoard.h"
#include "GameManager.h"

using namespace std;

GameManager::GameManager(int level) {
    if (level == 2) {
        // Medium difficulty: 3 bombs in 4x4 board
        board = new GameBoard(3, 4, 4);
    } else if (level == 3) {
        // Hard difficulty: 4 bombs in 5x5 board
        board = new GameBoard(4, 5, 5);
    } else {
        // Easy difficulty: 2 bombs in 3x3 board
        board = new GameBoard(2, 3, 3);
    }
    gameEnd = false;
    won = false;
}

void GameManager::addPoint(int row, int col, vector<Point>& openedCell) {
    Point p = {row, col};
    openedCell.push_back(p);
}

void GameManager::clickCell(int row, int col, vector<Point>& openedCell) {
    if (board->inBounds(row, col) && !(board->isVisible(row, col))) {
        bool bombClicked = board->isBomb(row, col);
        clickCellHelper(row, col, openedCell);
        updateGameEnd(bombClicked);
    }
}

void GameManager::clickCellGame(int row, int col) {
    if (board->inBounds(row, col) && !(board->isVisible(row, col))) {
        bool bombClicked = board->isBomb(row, col);
        clickCellGameHelper(row, col);
        updateGameEnd(bombClicked);
    }
}


void GameManager::clickCellHelper(int row, int col, vector<Point>& openedCell) {
    if (board->inBounds(row, col) && !(board->isVisible(row, col))) {
        addPoint(row, col, openedCell);
        board->revealCell(row, col);
        if (board->isClear(row, col)) { //if cell is clear
            for (int i = row - 1; i <= row + 1; i++ ) {
                for (int j = col - 1; j <= col + 1; j++) {
                    if (!(i == row && j == col)) {
                        clickCellHelper(i, j, openedCell);            
                    }
                }
            }
        }
    }
}

void GameManager::clickCellGameHelper(int row, int col) {
    if (board->inBounds(row, col) && !(board->isVisible(row, col))) {
        board->revealCell(row, col);
        if (board->isClear(row, col)) { //if cell is clear
            // Clockwise for conceptual thinking
            for (int i = row - 1; i <= row + 1; i++ ) {
                for (int j = col - 1; j <= col + 1; j++) {
                    if (!(i == row && j == col)) {
                        clickCellGameHelper(i, j);            
                    }
                }
            }
        }
    }
}

void GameManager::unClickCell(vector<Point> openedCell) {
    // Looping through all the open cells for a particular recursive call
    // of gameSolver method
    for (int i = 0; i < openedCell.size(); i++) {
        Point p = openedCell[i];
        int row = p.row;
        int col = p.col;
        // Hides cell
        board->closeCell(row, col);
    }
    gameEnd = false;
        won = false;
}

void GameManager::updateGameEnd(bool bombClicked) {
    // Assume game is over before checking
    gameEnd = true;
    if (!bombClicked) {
        int i = 0;
        int j;
        while (isGameEnd() && i < board->getRows()) {
            j = 0;
            while (isGameEnd() && j < board->getCols()) {
                if (!(board->isVisible(i, j)) && !(board->isBomb(i, j))) {
                    gameEnd = false;
                } 
                j++;
            }
            i++;
        }
        if (i == board->getRows() && j == board->getCols()) {
            won = true;
        }   
    }
}

/**
 * @brief This algorithm uses recursive backtracking to determine the minimum
 * number of clicks to solve a game. Every permutation of clicks is attempted
 * naively.
 * 
 * @param clickCount Initialized to zero by default
 * @return int Minimum number of clicks to win the game
 */
int GameManager::gameSolver(int clickCount) {
    if (isGameEnd()) {
        if (isWinner()) {
            return clickCount;
        } else {
            return getRows() * getCols();
        }
    } else {
        // Revealed/opened cells are tracked in this vector
        vector<Point> openedCell;
        int min = getRows() * getCols(); // Initialize min value
        for (int i = 0; i < getRows(); i++) {
            for (int j = 0; j < getCols(); j++) {
                if (!isVisible(i, j)) {
                    clickCell(i, j, openedCell); // Change to board
                    int moveCount = gameSolver(clickCount + 1);
                    if (moveCount < min) { // Check for minimum path of clicks
                        min = moveCount;
                    }
                    // Undo exploration
                    unClickCell(openedCell);
                }               
            }
        }
        return min;
    }
}

void GameManager::setFlag(int row, int col) {
    board->setFlag(row, col);
}

int GameManager::getValue(int row, int col) const {
    return board->getValue(row, col);
}

bool GameManager::isFlag(int row, int col) const {
    return board->isFlag(row, col);
}

bool GameManager::isVisible(int row, int col) const {
    return board->isVisible(row, col);
}

bool GameManager::isWinner() const {
    return won;
}

bool GameManager::isGameEnd() const {
    return gameEnd;
}

void GameManager::printBoard(bool displayBoard) const {
    board->printBoard(displayBoard);
}

int GameManager::getRows() const {
    return board->getRows();
}

int GameManager::getCols() const {
    return board->getCols();
}