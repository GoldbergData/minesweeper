
#include <string>
#include <vector>
#include "gwindow.h"
#include "gevent.h"
#include "gradiobutton.h"
#include "gbutton.h"
#include "gchooser.h"
#include "glabel.h"
#include "gfilechooser.h"
#include "gobjects.h"
#include "GameGui.h"
#include "GameManager.h"

using namespace std;
using namespace sgl;

GLabel* glBackgrounds;
GRadioButton* grbEasy;
GRadioButton* grbMedium;
GRadioButton* grbHard;

GButton* gbReset;
GLabel* glInstructions;

GLabel* glMousePos;

// GameGui::GameGui() {
//     window = new GWindow();
//     gManager = new GameManager("board1input.txt");
//     squareSize = 50;    
//     windowSize = gManager->getRows() * squareSize;
//     window->setCanvasSize(windowSize + 300, windowSize);  //offset for buttons
//     window->setLocation(300, 100);
//     window->setBackground("black");   //background color for GUI buttons area
//     window->setExitOnClose(true);
//     window->setAutoRepaint(false);
//     drawGrid();
//     redraw();
//     //createMapChooser();
//     //createButtons();
// }

GameGui::GameGui() : squareSize(50) {
    window = new GWindow();
    createButtons();
    createRadioButtons();
    initializeGame();
}

void GameGui::configureWindow() {
    windowSizeX = gManager->getCols() * squareSize;
    windowSizeY = gManager->getRows() * squareSize;
    window->setCanvasSize(windowSizeX + 300, windowSizeY);  //offset for buttons
    window->setLocation(300, 100);
    window->setBackground("black");   //background color for GUI buttons area
    window->setExitOnClose(true);
    window->setAutoRepaint(false);    
}

void GameGui::initializeGame() {
    checkDifficulty();
    if (difficulty == "hard") {
        gManager = new GameManager(3);
    } else if (difficulty == "med") {
        gManager = new GameManager(2); 
    } else {
        gManager = new GameManager(1); 
    }
    //cout << "minimum clicks to win: " << gManager->gameSolver() << endl;
    configureWindow();
    redraw();
    eventLoop();
}

void GameGui::checkDifficulty() {
    if (grbEasy->isSelected()) {
        difficulty = "easy";
    } else if (grbMedium->isSelected()) {
        difficulty = "med";
    } else {
        difficulty = "hard";
    }
}

void GameGui::createButtons() {
    gbReset = new GButton("Reset");
    window->addToRegion(gbReset, "East");
    gbReset->setClickListener([this] {
        initializeGame();
    });
}

void GameGui::createSingleRadio(string text, GRadioButton*& nameOut) {
    GRadioButton* button = new GRadioButton(text);
    button->setActionCommand(text);
    button->setColor("white");
    window->addToRegion(button, "East");
    nameOut = button;
 }

void GameGui::createRadioButtons() {
    //label
    glBackgrounds = new GLabel("Difficulty:");
    glBackgrounds->setColor("white");
    window->addToRegion(glBackgrounds, "East");
    //buttons
    createSingleRadio("Easy", grbEasy);
    createSingleRadio("Medium", grbMedium);
    createSingleRadio("Hard", grbHard);
    grbEasy->setSelected(true);
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
    int offsetX = 10;
    int offsetY = 30;
    for (int i = 0; i < gManager->getRows(); i++) {
        for (int j = 0; j < gManager->getCols(); j++) {
            string cellValue = switchCellValue(i, j);
            if (gManager->isVisible(i, j)) {
                window->setFillColor("#000000");
                window->fillRect(j * squareSize, i * squareSize, squareSize, squareSize);                
                window->drawString(cellValue, offsetX + j * squareSize, 
                    offsetY + i * squareSize);
            } else if (gManager->isFlag(i, j)) {
                window->setFillColor("#6E6E6E");
                window->fillRect(j * squareSize, i * squareSize, squareSize, squareSize);    
                window->drawString("F", offsetX + j * squareSize, 
                    offsetY + i * squareSize);
            } else {
                window->setFillColor("#6E6E6E");
                window->fillRect(j * squareSize, i * squareSize, squareSize, squareSize);
            }
        }      
    }    
    window->repaint();
}

int GameGui::convertCoord(int coord) {
    return (coord / squareSize);
}

bool GameGui::inBounds(int row, int col) {
    return row < gManager->getRows() && col < gManager->getCols();
}

void GameGui::processMouseEvent(int row, int col, GEvent mouseEvent) {
    if (inBounds(row, col)) { //if within bounds of the grid
        if (mouseEvent.isLeftClick()) { //run clickCell if left mouse click
            gManager->clickCellGame(row, col);
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
    cout << "start eventLoop" << endl;
    while (!gManager->isGameEnd()) {
        cout << "in game" << endl;
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