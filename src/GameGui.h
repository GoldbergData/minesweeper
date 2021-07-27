//this represent one board

#ifndef _GameGui_h_
#define _GameGui_h_

#include <string>
#include <vector>
#include "gwindow.h"
#include "GameManager.h"

using namespace sgl;

class GameGui {
public:
	GameGui(int squareSize);
    void setMapFile();
    void createButtons();
    void createMapChooser();
    void drawGrid();
    void drawColoredLine(double startx, double starty, double endx, double endy,
                              double lineWidth, int color);
    void update();
    void redraw();
private:
    GWindow* window;
    GameManager* gameManager;

    std::string switchCellValue(int row, int col);
    int convertCoord(int coord);

    int windowSize;
    int squareSize;
    static const std::vector<std::string> mapFiles;
};
#endif