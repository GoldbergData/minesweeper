// //this represent one board

// #include <string>
// #include <vector>
// #include <iostream>
// #include "GameManager.h"

// using namespace std;

// void runGame(GameManager* manager) {
//     int x;
//     int y;
//     string line;
//     manager->printBoard();
//     cout << endl;

//     cout << "Reveal location x: ";
//     getline(cin, line);
//     x = stoi(line);
//     cout << endl;

//     cout << "Reveal location y: ";
//     getline(cin, line);
//     y = stoi(line);
//     cout << endl;

//     manager->clickCell(x, y);
// }

// int main() {
//     GameManager* manager = new GameManager("board1input.txt");

//     while (!manager->isGameEnd()) {
//         runGame(manager);
//     }

//     manager->printBoard();
    
//     if (manager->isWinner()) {
//         cout << "You won!";
//     } else {
//         cout << "You lose!";
//     }

//     cout << endl;

//     return 0;
// }

