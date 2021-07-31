/**
 * @file GameManager.h
 * @author Joshua Goldberg (j.goldberg4674@edmail.edcc.edu), Matthew Kim 
 * (m.kim3007@edmail.edcc.edu)
 * @brief The GameManager class processes player input and manages the state of
 * the Minesweeper game. GameManager processes the player clicks of a cell and
 * updates game end to determine a win or a loss at each move. GameManager also
 * calculates the minimum number of moves to win a game. Note: the algorithm uses
 * recursive backtracking, which can be very slow for large grids.
 * 
 * @version 0.1
 * @date 2021-07-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _GameManager_h_
#define _GameManager_h_

#include <string>
#include <vector>
#include "GameBoard.h"

/**
 * @brief Simple utility struct to store coordinates when cells are processed by
 * player clicks.
 * 
 */
struct Point {
	int row;
	int col;
};

class GameManager {
public:
	/**
	 * @brief Construct a new GameManager, which creates an instance of a game
	 * based on difficulty: easy, medium and hard; these are levels and map to
	 * 1, 2, 3, respectively. As the difficulty rises, the board size and 
	 * the number of bombs increase.
	 * 
	 * @param level 1 = easy, 2 = medium; 3 = hard
	 */
	GameManager(int level);

	/**
	 * @brief Processes clicks of the cell on the gameboard. Cells are revealed
	 * until a cell is encountered that has a neighboring bombs. If a bomb is
	 * clicked initially, the bomb is revealed.
	 * 
	 * @param row 
	 * @param col 
	 */
	void clickCellGame(int row, int col);

	/**
	 * @brief Calculates and returns the minimum number of clicks to win the 
	 * game.
	 * 
	 * @param clickCount Starts at zero
	 * @return int 
	 */
	int gameSolver(int clickCount = 0);

	/**
	 * @brief Returns occupant of the cell as an int.
	 * 
	 * @param row 
	 * @param col
	 * @return int 
	 */
	int getValue(int row, int col) const;

	/**
	 * @brief Returns total number of rows of the board. 
	 * 
	 * @return int 
	 */
	int getRows() const;

	/**
	 * @brief Returns total number of columns of the board. 
	 * 
	 * @return int 
	 */
	int getCols() const;

	/**
	 * @brief Sets/unsets the flag of a given cell.
	 * 
	 * @param row 
	 * @param col 
	 */		
	void setFlag(int row, int col);

	/**
	 * @brief Returns if a given cell is visible.
	 * 
	 * @param row 
	 * @param col 
	 * @return true Visible
	 * @return false Not visible
	 */	
	bool isVisible(int row, int col) const;
	
	/**
	 * @brief Returns if a given cell is flagged.
	 * 
	 * @param row 
	 * @param col 
	 * @return true Flagged
	 * @return false Not flagged
	 */
	bool isFlag(int row, int col) const;

	/**
	 * @brief Returns the state of the game.
	 * 
	 * @return true Game is over
	 * @return false Game is not over
	 */
	bool isGameEnd() const;

	/**
	 * @brief Returns if the game has been won or lost.
	 * 
	 * @return true Game won
	 * @return false Game lost
	 */
	bool isWinner() const;
	
	/**
	 * @brief Printer helper for GameBoard. Prints either the solution board or
	 * the display board, which is controlled by displayBoard parameter.
	 * 
	 * The display board represents an unrevealed cell with an X. Revealed empty
	 * cells are dashes ("-"). Bomb locations are marked with a "B" and integer
	 * values 1-8 indicate number of neighboring bombs. Flagged cells are
	 * represented with an F.
	 * 
	 * The solution using identical notation, but all cells are revealed.
	 * 
	 * @param displayBoard 
	 */
	void printBoard(bool displayBoard) const;
private:
    GameBoard* board;
	bool gameEnd;
	bool won;
	/**
	 * @brief Utility method for gameSolver method to explore clicks of cells
	 * when looking for solutions.
	 * 
	 * @param row Clicked cell row index
	 * @param col Clicked cell column index
	 * @param openedCell Stores cells that were opened during solution search
	 */
	void clickCell(int row, int col, vector<Point>& openedCell);

	/**
	 * @brief Utility method to undo clickCell method call.
	 * 
	 * @param openedCell 
	 */
	void unClickCell(vector<Point> openedCell);

	/**
	 * @brief Utility method for gameSolver method to explore clicks of cells
	 * when looking for solutions.
	 * 
	 * @param row Clicked cell row index
	 * @param col Clicked cell column index
	 * @param openedCell Stores cells that were opened during solution search
	 */
	void clickCellHelper(int row, int col, vector<Point>& openedCell);

	/**
	 * @brief Utility method for clickCellGame to enable recursive algorithm to
	 * open cells. 
	 * 
	 * @param row Clicked cell row index
	 * @param col Clicked cell column index
	 */
	void clickCellGameHelper(int row, int col);
	
	/**
	 * @brief Updates game status.
	 * 
	 * @param bombClicked Skips looping through board if bomb was clicked
	 */
	void updateGameEnd(bool bombClicked);

	/**
	 * @brief Utility method for the gameSolver to add cells to openedCell
	 * parameter passed to clickCellHelper method.
	 * 
	 * @param row Clicked cell row index
	 * @param col Clicked cell column index
	 * @param openedCell Stored cells revealed during gameSolver call
	 */
	void addPoint(int row, int col, vector<Point>& openedCell);
};
#endif