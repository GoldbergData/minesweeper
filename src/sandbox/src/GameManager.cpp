/**
 * @file GameManager.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-07-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

//this class is the implementation...

#include <string>
#include <vector>
#include "GameBoard.h"
#include "GameManager.h"

using namespace std;

GameManager::GameManager(std::string fileName) {
    board = new GameBoard(fileName);
    gameEnd = false;
    won = false;
}

int GameManager::getValue(int row, int col) const {
    return board->getValue(row, col);
}

void GameManager::setFlag(int row, int col) {
    board->setFlag(row, col);
}

void GameManager::clickCell(int row, int col) {
    if (board->inBounds(row, col)) {
        if (!(board->isVisible(row, col))) {
            bool bombClicked = board->isBomb(row, col);
            bool clearCell = board->isClear(row, col);
            if (clearCell) {
                clickCellHelper(row, col);
            } else {
                // If player clicks on a bomb or a cell with neigh bombs
                board->revealCell(row, col);
            }
            checkEndGame(bombClicked);
        }
    }
}

void GameManager::clickCellHelper(int row, int col) {
    if (board->inBounds(row, col) && !(board->isVisible(row, col))) {
        // cout << "DEBUG row: " << row << endl;
        // cout << "DEBUG col: " << col << endl;
        if (!(board->isBomb(row, col))) {
            // Refactor: remove redundant call of revealCell()
            board->revealCell(row, col);
        }
        if (board->isClear(row, col)) {
            // Clockwise for conceptual thinking
            clickCellHelper(row - 1, col);
            clickCellHelper(row - 1, col + 1);
            clickCellHelper(row, col + 1);
            clickCellHelper(row + 1, col + 1);
            clickCellHelper(row + 1, col);
            clickCellHelper(row + 1, col - 1);
            clickCellHelper(row, col - 1);
        }
    }
}

void GameManager::checkEndGame(bool bombClicked) {
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

bool GameManager::isWinner() {
    return won;
}

bool GameManager::isGameEnd() {
    return gameEnd;
}

void GameManager::printBoard() {
    cout << (*board);
}