/**
 * @file GameGui.h
 * @author Joshua Goldberg (j.goldberg4674@edmail.edcc.edu), Matthew Kim 
 * (m.kim3007@edmail.edcc.edu)
 * @brief The GameGui class is the creates and controls the user interface for
 * the Minesweeper game. Players can choose between easy, medium, and hard 
 * difficulty, which increases the board size and number of bombs in progressive 
 * order. Players can also reset the game after they have won or lost.
 * @version 0.1
 * @date 2021-07-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */

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
    /**
     * @brief Construct a new GameGui, which generates the window and 
     * initializes the Minesweeper game. Window sizes is determined innately 
     * by the size of the Minesweeper board.
     * 
     */
	GameGui();

    /**
     * @brief Draws Minesweeper graphics.
     * 
     */
    void redraw();
    
    /**
     * @brief Handles the game loop. Even if a game ends, the player has the 
     * option to reset the game and continue playing.
     * 
     */
    void eventLoop();
private:
    GWindow* window;
    GameManager* gManager;
    int squareSize;
    std::string difficulty;
    
    /**
     * @brief Determines game difficulty based on radio button selection. The
     * default is easy.
     * 
     */
    void checkDifficulty();

    /**
     * @brief Constructs a new GameManager to initialize a new game. It also
     * re-configures the game's window and draws the gameboard.
     * 
     */
    void initializeGame();

    /**
     * @brief Sets the interface window size and background graphics.
     * 
     */
    void configureWindow();
    
    /**
     * @brief Utility method to help with printing the content of a cell in the
     * gameboard.
     * 
     * @param row 
     * @param col 
     * @return std::string 
     */
    std::string switchCellValue(int row, int col);

    void processMouseEvent(int row, int col, GEvent mouseEvent);
    void createResetButton();    
    void createSingleRadio(std::string text, GRadioButton*& nameOut);
    void createRadioButtons();
    
    /**
     * @brief Converts coordinates of window to row/column indices of the
     * gameboard.
     * 
     * @param coord Window coordinate
     * @return int Row or column value
     */
    int convertCoord(int coord);

    /**
     * @brief Utility method to check whether the player's click is inbounds
     * of the gameboard.
     * 
     * @param row Clicked row
     * @param col Clicked column
     * @return true Inbounds
     * @return false Out-of-bounds
     */
    bool inBounds(int row, int col);
    
    /**
     * @brief Simple print to indicate game is over and whether user has won.
     * 
     */
    void concludeGame();
};
#endif