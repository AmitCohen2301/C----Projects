#pragma once

#include <vector>
#include <queue>
#include "Maze.h"
#include "PacmanAction.h"
#include "Cell.h"

class Maze;
class PacmanAction;

using namespace std;

class NPC_Pacman
{
private:
	int pacmanRow; // Pacman row
	int pacmanCol; // Pacman col
	int pacmanHP; // Pacman HP
	int pacmanDircetionMove; // Pacman direction move
	int numOfCollectedCoins; // Num of collected coins
	Maze* mazePacmanIn; // Maze the pacman in
	bool searchCoinFlag; // Search coin flag
	bool movingFlag; // Moving flag
	bool searchTargetFlag; // Search target flag
	bool fightingFlag; // Fighting flag
	bool winFlag; // Win flag
	bool loseFlag; // Lose flag
	PacmanAction* currentPacmanAction; // Current pacman action
	queue<Cell> grays; // Queue of gray cells
	vector<Cell> blacks; // Vector of black cells

public:
	// Constructors
	NPC_Pacman(int rowToSet, int colToSet, Maze* mazeToSet);

	// Gets
	int getPacmanRow() { return pacmanRow; } // Get pacmanRow
	int getPacmanCol() { return pacmanCol; } // Get pacmanCol
	int getPacmanHP() { return pacmanHP; } // Get pacmanHP
	int getPacmanDircetionMove() { return pacmanDircetionMove; } // Get pacmanDircetionMove
	int getNumOfCollectedCoins() { return numOfCollectedCoins; } // Get numOfCollectedCoins
	Maze* getMazePacmanIn() { return mazePacmanIn; } // Get mazePacmanIn
	bool getSearchCoinFlag() { return searchCoinFlag; } // Get searchCoinFlag
	bool getMovingFlag() { return movingFlag; } // Get movingFlag
	bool getSearchTargetFlag() { return searchTargetFlag; } // Get searchTargetFlag
	bool getFightingFlag() { return fightingFlag; } // Get fightingFlag
	bool getWinFlag() { return winFlag; } // Get winFlag
	bool getLoseFlag() { return loseFlag; } // Get loseFlag
	PacmanAction* getCurrentPacmanAction() { return currentPacmanAction; } // Get currentPacmanAction
	queue<Cell> getGrays() { return grays; } // Get grays
	vector<Cell> getBlacks() { return blacks; } // Get blacks

	// Sets
	void setPacmanRow(int pacmanRowToSet) { pacmanRow = pacmanRowToSet; } // Set pacmanRow
	void setPacmanCol(int pacmanColToSet) { pacmanCol = pacmanColToSet; } // Set pacmanCol
	void setPacmanHP(int pacmanHPToSet) { pacmanHP = pacmanHPToSet; } // Set pacmanHP
	void setPacmanDircetionMove(int pacmanDirectionMoveToSet) { pacmanDircetionMove = pacmanDirectionMoveToSet; } // Set pacmanDircetionMove
	void setNumOfCollectedCoins(int numOfCollectedCoinsToSet) { numOfCollectedCoins = numOfCollectedCoinsToSet; } // Set numOfCollectedCoins
	void setMazePacmanIn(Maze* mazePacmanInToSet) { mazePacmanIn = mazePacmanInToSet; } // Set mazePacmanIn
	void setSearchCoinFlag(bool searchCoinFlagToSet) { searchCoinFlag = searchCoinFlagToSet; } // Set searchCoinFlag
	void setMovingFlag(bool movingFlagToSet) { movingFlag = movingFlagToSet; } // Set movingFlag
	void setSearchTargetFlag(bool searchTargetFlagToSet) { searchTargetFlag = searchTargetFlagToSet; } // Set searchTargetFlag
	void setFightingFlag(bool fightingFlagToSet) { fightingFlag = fightingFlagToSet; } // Set fightingFlag
	void setWinFlag(bool winFlagToSet) { winFlag = winFlagToSet; } // Set winFlag
	void setLoseFlag(bool loseFlagToSet) { loseFlag = loseFlagToSet; } // Set loseFlag
	void setCurrentPacmanAction(PacmanAction* currentPacmanActionToSet) { currentPacmanAction = currentPacmanActionToSet; } // Set currentPacmanAction
	void setGrays(queue<Cell>& graysToSet) { grays = graysToSet; } // Set grays
	void setBlacks(vector<Cell>& blacksToSet) { blacks = blacksToSet; } // Set blacks

	// General functions of NPC
	bool getIfGetToTargetPoint(); // Get if get to target point
	int getNumOfGhostsNearPacman(); // Get num of ghosts near pacman
	void emptyGraysAndBlacks(); // Empty grays & blacks
	bool checkIfGray(Cell* cellToCheck); // Check if cell is gray
	void chooseRandomDirections(int* pDirections); // Choose random directions
	int getFirstDirectionMoveFromPacman(Cell* pCurrent); // Get first direction move from pacman
	int findNewDirectionToRunFromGhost(int direction); // Find new direction to run from ghost
	int checkNeighbour(int neighbourRow, int neighbourCol, Cell* pCurrent, int* pNumOfFoundGhosts, int typeToSearch); // Check neighbour
	int checkAllNeighbours(Cell* pCurrent, int* pNumOfFoundGhosts, int typeToSearch); // Check all neighbours
	int findDirectionToMoveToTypeWithBFS(int typeToSearch); // Find direction to move to type with BFS
	Cell* getCellToMoveTo(); // Get cell to move to
	void collectCoin(); // Collect coin
	void movePacmanToNewCell(Cell* currCellOfPacman, Cell* newCellOfPacman); // Move pacman to new cell
	void doAction(); // Do action
};