#pragma once

// Constants of cell IDs
const int SPACE = 0; // ID of space
const int WALL = 1; // ID of wall
const int COIN = 2; // ID of coin
const int TARGET = 3; // ID of target
const int PACMAN = 4; // ID of pacman
const int GHOST = 5; // ID of ghost

class Cell
{
private:
	int cellRow; // Cell row
	int cellCol; // Cell col
	int cellType; // Cell type
	bool thereIsCoin; // There is coin
	bool wasCoinAtBegin; // Was coin at begin
	int numOfGhostsInCell; // Num of ghosts in cell
	bool isCellIsTarget; // Is cell is target
	bool isPacmanInCell; // Is pacman in cell
	bool isPacmanStartedInCell; // Is pacman started in cell
	int h; // Manhattan Distance To Pacman
	int g; // Manhattan Distance To Ghost
	Cell* parent; // Parent of cell
	const char* TYPES[6] = { "SPACE", "WALL", "COIN", "TARGET", "PACMAN", "GHOST" };

public:
	// Constructors
	Cell(); // Empty constructor

	// Gets
	int getCellRow() { return cellRow; } // Get cellRow
	int getCellCol() { return cellCol; } // Get cellCol
	int getCellType() { return cellType; } // Get cellType
	bool getThereIsCoin() { return thereIsCoin; } // Get thereIsCoin
	bool getWasCoinAtBegin() { return wasCoinAtBegin; } // Get wasCoinAtBegin
	int getNumOfGhostsInCell() { return numOfGhostsInCell; }// Get numOfGhostsInCell
	bool getIsCellIsTarget() { return isCellIsTarget; } // Get isCellIsTarget
	bool getIsPacmanInCell() { return isPacmanInCell; } // Get isPacmanInCell
	bool getIsPacmanStartedInCell() { return isPacmanStartedInCell; } // Get isPacmanStartedInCell
	int getH() { return h; } // Get h (Manhattan Distance To Pacman)
	int getG() { return g; } // Get g (Manhattan Distance To Ghost)
	Cell* getParent() { return parent; } // Get parent
	const char* getTypeInWords(int type) { return TYPES[type]; } // Get type in words

	// Sets
	void setCellRow(int cellRowToSet) { cellRow = cellRowToSet; } // Set cellRow
	void setCellCol(int cellColToSet) { cellCol = cellColToSet; } // Set cellCol
	void setCellType(int cellTypeToSet) { cellType = cellTypeToSet;; } // Set cellType
	void setThereIsCoin(bool thereIsCoinToSet) { thereIsCoin = thereIsCoinToSet; } // Set thereIsCoin
	void setWasCoinAtBegin(bool wasCoinAtBeginToSet) { wasCoinAtBegin = wasCoinAtBeginToSet; } // Set wasCoinAtBegin
	void setNumOfGhostsInCell(int numOfGhostsInCellToSet) { numOfGhostsInCell = numOfGhostsInCellToSet; }// Set numOfGhostsInCell
	void setIsCellIsTarget(bool isCellIsTargetToSet) { isCellIsTarget = isCellIsTargetToSet; } // Set isCellIsTarget
	void setIsPacmanInCell(bool isPacmanInCellToSet) { isPacmanInCell = isPacmanInCellToSet; } // Set isPacmanInCell
	void setIsPacmanStartedInCell(bool isPacmanStartedInCellToSet) { isPacmanStartedInCell = isPacmanStartedInCellToSet; } // Set isPacmanStartedInCell
	void setParent(Cell* p) { parent = p; } // Set parent
	void setH(int hToSet) { h = hToSet; } // Set h (Manhattan Distance To Pacman)
	void setG(int gToSet) { g = gToSet; } // Set g (Manhattan Distance To Ghost)

	// General functions
	void setParametersForFirstTime(int rowToSet, int colToSet, int cellTypeToSet); // Set row, col and cellType for first time
	void restoreCellToBegining(); // Restore cell to begining
	void initCoinFirstTime(); // Init coin first time
	bool isThereIsGhostInCell(); // Is there is ghost in cell
	void addPacmanToCell(); // Add pacman to cell
	void removePacmanFromCell(); // Remove pacman from cell
	void addGhostToCell(); // Add ghost to cell
	void removeGhostFromCell(); // Remove ghost from cell
	bool operator==(const Cell& other); // Check if cells are the same
};