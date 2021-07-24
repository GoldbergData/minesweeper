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

GameBoard* GameManager::createSolutionBoard(std::string fileName) {
    solution = new GameBoard(fileName);
}

//solution -> fill with content
GameBoard* GameManager::createDisplayBoard() {
    display = new GameBoard(12, 12);
}

GameManager::GameManager(std::string fileName) {
    createSolutionBoard(fileName);
    createDisplayBoard();

}
bool GameManager::isWinner() {

}

bool GameManager::isGameOver() {

}