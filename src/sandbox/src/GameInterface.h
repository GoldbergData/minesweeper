//this represent one board

#ifndef _GameGui_h_
#define _GameGui_h_

#include <string>
#include <vector>
#include "gwindow.h"

class GameGui {
public:
	GameGui(int windowSize, int squareSize);
    //convert mouse click to row/col
    void update;   
private:
    GWindow* window;
    int windowSize;
    int squareSize;
};
#endif