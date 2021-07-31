/**
 * @file GameBoard.h
 * @author Joshua Goldberg (j.goldberg4674@edmail.edcc.edu), Matthew Kim 
 * (m.kim3007@edmail.edcc.edu)
 * @brief The GameBoard class represents a board for the Minesweeper game. GameBoard
 * maintains the state of the gameboard (what occupies each cell: a bomb, empty, 
 * or the count of neighbor bombs) and allows state changes. GameBoard also tracks
 * if a cell on the board has been flagged. Other characteristics of the gameboard 
 * can also be retrieved, such as the dimensions.
 * 
 * @version 0.1
 * @date 2021-07-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _GameBoard_h_
#define _GameBoard_h_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

/**
 * @brief A simple struct to represent the contents of a cell. Occupants of a 
 * cell, which is stored in the value field, are as follows:
 * 	- 0: empty cell
 * 	- 1-8: cell has neighbor bombs denoted by number
 * 	- 9: cell has bomb
 * 
 */
struct Cell {
	int value;
	bool flag;
	bool visible;

	Cell(int value) {
		this->value = value;
		/**
		 * @brief If a cell has been flagged, this is set to true.
		 * 
		 */
		flag = false;
		/**
		 * @brief If a cell has been revealed, this is set to true.
		 * 
		 */
		visible = false;
	}
};

class GameBoard {
public:
	/**
	 * @brief Construct a new Game Board object. The constructor takes the number
	 * of bombs and the number of rows and columns of the board. The number of
	 * bombs passed to the constructor will be placed in random locations.
	 * 
	 * @param bNum Number of bombs to generate on the board.
	 * @param rows Total rows of board.
	 * @param cols Total columns of board.
	 */
	GameBoard(int bNum, int rows, int cols);

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
	 * @brief Reveals a cell's contents by setting the visible field in the
	 * cell to true.
	 * 
	 * @param row 
	 * @param col 
	 */
	void revealCell(int row, int col);

	/**
	 * @brief Hides a cell's contents by setting the visible field in the
	 * cell to false.
	 * 
	 * @param row 
	 * @param col 
	 */
	void closeCell(int row, int col);

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
	 * @brief Returns if a given cell is visible.
	 * 
	 * @param row 
	 * @param col 
	 * @return true Visible
	 * @return false Not visible
	 */	
	bool isVisible(int row, int col) const;

	/**
	 * @brief Returns if a given cell is bomb.
	 * 
	 * @param row 
	 * @param col 
	 * @return true Bomb
	 * @return false Not bomb
	 */	
	bool isBomb(int row, int col) const;

	/**
	 * @brief Returns if the given cell has neighboring bombs.
	 * 
	 * @param row 
	 * @param col 
	 * @return true Neighbor bombs
	 * @return false No neighbor bombs
	 */
	bool hasNeighborBombs(int row, int col) const;

	/**
	 * @brief Returns if the given cell is clear, which means no neighboring 
	 * bombs.
	 * 
	 * @param row 
	 * @param col 
	 * @return true Clear
	 * @return false Not clear
	 */	
	bool isClear(int row, int col) const;

	/**
	 * @brief Returns if the given cell is out of bounds of the board.
	 * 
	 * @param row 
	 * @param col 
	 * @return true Inbounds
	 * @return false Out-of-bounds
	 */	
	bool inBounds(int row, int col) const;

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
	/**
	 * @brief Helper function to count neighboring bombs for a given cell.
	 * 
	 * @param row 
	 * @param col 
	 * @return int Number of neighboring bombs.
	 */
	int countNeighborBombs(int row, int col);
	std::vector<std::vector<Cell> >* board;
	int rows;
	int cols;

	/**
	 * @brief Set the value of a given cell when the board is initialized in the
	 * constructor.
	 * 
	 * @param row 
	 * @param col 
	 * @param value 
	 */
	void setValue(int row, int col, int value);	
};
#endif