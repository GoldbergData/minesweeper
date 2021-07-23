//this represent one board


#include <string>
#include <vector>
#include <iostream>
#include "GameBoard.h"

using namespace std;

int main() {
    GameBoard board(12, 12);
    cout << board;
}