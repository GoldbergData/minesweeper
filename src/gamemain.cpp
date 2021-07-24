//this represent one board

#include <string>
#include <vector>
#include <iostream>
#include "GameBoard.h"

using namespace std;

int main() {
    cout << "TRY BOARD CONSTRUCTOR" << endl;
    GameBoard board("board1input.txt");
    cout << board << endl << endl;
    
    /*
    cout << "TRY GETVALUE" << endl;
    cout <<"Value at 1, 1: " << board.getValue(1,1) << endl << endl;

    cout << "TRY SETVALUE" << endl;
    board.setValue(1, 1, 4);
    cout << "Value at 1, 1 set to 4: " << board.getValue(1, 1) << endl << endl;

    cout << "TRY SETFLAG" << endl;
    board.setValue(1, 1, 4);
    cout << "Is there a flag at 1, 1 (before)? ";
    if (board.isFlag(1, 1)) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }
    board.setFlag(1, 1);
    cout << "Is there a flag at 1, 1 (after)? ";
    if (board.isFlag(1, 1)) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }
        
    cout << "TRY ISBOMB" << endl;
    cout << "Is there a bomb at 1, 1? ";
    if (board.isBomb(1, 1)) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }

    cout << "Is there a bomb at 0, 2? ";
    if (board.isBomb(0, 2)) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }

    cout << "TRY ISCLEAR" << endl;
    cout << "Is the space clear at 1, 1? ";
    if (board.isBomb(1, 1)) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }
    cout << "Is the space clear at 0, 0? ";
    if (board.isClear(0, 0)) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }
    */

    return 0;
}

