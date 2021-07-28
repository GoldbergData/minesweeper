
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
    gManager = new GameManager("board1input.txt");    
    this->windowSize = gManager->getRows() * squareSize;
    this->squareSize = squareSize;
    window->setCanvasSize(windowSize + 300, windowSize);  //offset for buttons
    window->setLocation(300, 100);
    window->setBackground("black");   //background color for GUI buttons area
    window->setExitOnClose(true);
    window->setAutoRepaint(false);
    drawGrid();
    redraw();
    //createMapChooser();
    //createButtons();
}

void GameGui::setMapFile() {
    string fileName = gcMapSelect->getSelectedItem() + ".txt";
    // Todo: need to create deconstructor
    // delete gameManager;
    // gameManager = nullptr;
    gManager = new GameManager(fileName);
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

string GameGui::switchCellValue(int row, int col) {
    switch (gManager->getValue(row, col)) {
        case 0: return "";
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
    window->clearCanvasPixels();
    drawGrid();
    int offsetX = 10;
    int offsetY = 30;
    for (int i = 0; i < gManager->getRows(); i++) {
        for (int j = 0; j < gManager->getCols(); j++) {
            // string cellValue = to_string(gameManager->getValue(i, j));
            string cellValue = switchCellValue(i, j);
            if (gManager->isVisible(i, j)) {
                window->drawString(cellValue, offsetX + j * squareSize, 
                    offsetY + i * squareSize);
            } else {
                window->drawString("", offsetX + j * squareSize, 
                    offsetY + i * squareSize);
            }
        }      
    }    
    window->repaint();
}

int GameGui::convertCoord(int coord) {
    return (coord / squareSize);
}

bool GameGui::inBounds(int row, int col) {
    return row < (windowSize / squareSize) && col < (windowSize / squareSize);
}

void GameGui::processMouseEvent(int row, int col, GEvent mouseEvent) {
    if (inBounds(row, col)) { //if within bounds of the grid
        if (mouseEvent.isLeftClick()) { //run clickCell if left mouse click
            gManager->clickCell(row, col);
        } else if (mouseEvent.isRightClick()) { //run setFlag if right mouse clic
            gManager->setFlag(row, col);
        }
        redraw(); //redraw the grid
    }    
}

void GameGui::concludeGame() {
    if (gManager->isWinner()) {
        cout << "You win!" << endl;
    } else {
        cout << "You lose!" << endl;
    }
}

void GameGui::eventLoop() {
    while (!gManager->isGameEnd()) {
        GEvent event = waitForClick();
        if (event.getEventClass() == MOUSE_EVENT) {
            GMouseEvent mouseEvent(event);
            int col = convertCoord(mouseEvent.getX());
            int row = convertCoord(mouseEvent.getY());
            processMouseEvent(row, col, mouseEvent);
        } else if (event.getEventClass() == WINDOW_EVENT) {
            if (event.getEventType() == WINDOW_CLOSED) {
                break; //ends game when window is closed
            }
        }
    }
    concludeGame();
}