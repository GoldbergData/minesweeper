
#include <string>
#include <vector>
#include "gwindow.h"
#include "gevent.h"
#include "gbutton.h"
#include "gchooser.h"
#include "glabel.h"
#include "gfilechooser.h"
#include "gobjects.h"
#include "GameGui.h"
#include "GameManager.h"

using namespace std;
using namespace sgl;



const vector<string> GameGui::mapFiles = {"board1input.txt"};

GButton* gbSetMap;
GButton* gbReset;
GChooser* gcMapSelect;
GLabel* glInstructions;

GLabel* glMousePos;

GameGui::GameGui(int squareSize) {
    window = new GWindow();
    gameManager = new GameManager("board1input.txt");    
    this->windowSize = gameManager->getRows() * squareSize;
    this->squareSize = squareSize;
    window->setCanvasSize(windowSize + 300, windowSize);  //offset for buttons
    window->setLocation(300, 100);
    window->setBackground("black");   //background color for GUI buttons area
    window->setExitOnClose(true);
    window->setAutoRepaint(false);
    drawGrid();
    redraw();
    createMapChooser();
    createButtons();
}

void GameGui::setMapFile() {
    string fileName = gcMapSelect->getSelectedItem() + ".txt";
    // Todo: need to create deconstructor
    // delete gameManager;
    // gameManager = nullptr;
    gameManager = new GameManager(fileName);
}

void GameGui::createButtons() {
    gbSetMap = new GButton("SET MAP");
    gbSetMap->setClickListener([this] {
        setMapFile();
    });

    gbReset = new GButton("RESET");
    gbReset->setClickListener([this] {
        setMapFile();
    });

    window->addToRegion(gbSetMap, "East");
    window->addToRegion(gbReset, "East");
}

void GameGui::createMapChooser() {
    gcMapSelect = new GChooser(mapFiles);
    glInstructions = new GLabel("Select map to begin:");
    glInstructions->setColor("white");
    window->addToRegion(glInstructions, "East");
    window->addToRegion(gcMapSelect, "East");
}

void GameGui::drawGrid() {
    drawColoredLine(0, 0, 0, windowSize, 2, 0xffffff);
    for (int i = 1; i <= windowSize / squareSize; i++) {
        drawColoredLine(i * squareSize, 0, i * squareSize, windowSize, 2, 0xffffff);
    }

    drawColoredLine(0, 0, windowSize, 0, 2, 0xffffff);
    for (int i = 1; i <= windowSize / squareSize; i++) {
        drawColoredLine(0, i * squareSize, windowSize, i * squareSize, 2, 0xffffff);
    }    
}

void GameGui::drawColoredLine(double startx, double starty, double endx, 
    double endy, double lineWidth, int color) {
    GLine line(startx, starty, endx, endy);
    line.setLineWidth(lineWidth);
    line.setColor(color);
    window->draw(line);
}

void GameGui::update() {
    // while (!gameManager.isGameEnd()) {

    // }
}

string GameGui::switchCellValue(int row, int col) {
    switch (gameManager->getValue(row, col)) {
        case 0: return "-";
        case 1: return "1";
        case 2: return "2";
        case 3: return "3";
        case 4: return "4";
        case 5: return "5";
        case 6: return "6";
        case 7: return "7";
        case 8: return "8";
        case 9: return "B";
        default: return "UNKNOWN";
    }
}

void GameGui::redraw() {
    int offsetX = 10;
    int offsetY = 30;
    for (int i = 0; i < gameManager->getRows(); i++) {
        for (int j = 0; j < gameManager->getCols(); j++) {
            // string cellValue = to_string(gameManager->getValue(i, j));
            string cellValue = switchCellValue(i, j);
            window->drawString(cellValue, offsetX + j * squareSize, 
                offsetY + i * squareSize);
        }      
    }    
}

int GameGui::convertCoord(int coord) {
    int coord = coord == 0 ? 1 : coord;
    return (windowSize / squareSize) - (windowSize / coord);
}

void processMouseEvent(GEvent mouseEvent) {
    int x = mouseEvent.getX();
    int y = mouseEvent.getY();
    int col = convertCoord(x);
    int row = convertCoord(y);
    glMousePos->setLabel("(x = " + std::to_string(x) + ", y = " + std::to_string(y) + ")");
    int type = mouseEvent.getEventType();
    if (type == MOUSE_PRESSED && mouseEvent.isLeftClick()) {
       gameManager->clickCell(row, col);
    }
    
}