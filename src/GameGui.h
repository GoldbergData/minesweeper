//this represent one board

#ifndef _GameGui_h_
#define _GameGui_h_

#include <string>
#include <vector>
#include "gwindow.h"
#include "gradiobutton.h"
#include "gbutton.h"
#include "GameManager.h"

using namespace sgl;

class GameGui {
public:
	GameGui();
    void createButtons();
    void createMapChooser();
    void redraw();
    void eventLoop();
private:
    GWindow* window;
    GameManager* gManager;
    int squareSize;
    std::string difficulty;
    void checkDifficulty();
    void initializeGame();
    void configureWindow();
    std::string switchCellValue(int row, int col);
    void processMouseEvent(int row, int col, GEvent mouseEvent);
    void createSingleRadio(std::string text, GRadioButton*& nameOut);
    void createRadioButtons();
    int convertCoord(int coord);
    bool inBounds(int row, int col);
    void concludeGame();
};
#endif