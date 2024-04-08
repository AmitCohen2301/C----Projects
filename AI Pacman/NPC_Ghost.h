#pragma once

#include <vector>
#include <queue>
#include "Maze.h"
#include "GhostAction.h"
#include "Cell.h"
#include "CompareCells.h"

class Maze;
class GhostAction;

using namespace std;

class NPC_Ghost
{
private:
	int ghostRow; // Ghost row
	int ghostCol; // Ghost Col
	int ghostHP; // Ghost HP
	int ghostDircetionMove; // Ghost direction move
	Maze* mazeGhostIn; // Maze the ghost in
	bool searchPacmanFlag; // Search pacman flag
	bool movingFlag; // Moving flag
	bool fightingFlag; // Fighting flag
	bool winFlag; // Win flag
	bool loseFlag; // Lose flag
	GhostAction* currentGhostAction; // Current ghost action
	vector<Cell> grays; // Grays
	vector<Cell> blacks; // Blacks
	priority_queue <Cell*, vector <Cell*>, CompareCells> priorityQueue; // Priority queue to select next cell

public:
	// Constructors
	NPC_Ghost(int rowToSet, int colToSet, Maze* mazeGhostInToSet);

	// Gets
	int getGhostRow() { return ghostRow; } // Get ghostRow
	int getGhostCol() { return ghostCol; } // Get ghostCol
	int getGhostHP() { return ghostHP; } // Get ghostHP
	int getGhostDircetionMove() { return ghostDircetionMove; } // Get ghostDircetionMove
	Maze* getMazeGhostIn() { return mazeGhostIn; } // Get mazeGhostIn
	bool getSearchPacmanFlag() { return searchPacmanFlag; } // Get searchPacmanFlag
	bool getMovingFlag() { return movingFlag; } // Get movingFlag
	bool getFightingFlag() { return fightingFlag; } // Get fightingFlag
	bool getWinFlag() { return winFlag; } // Get winFlag
	bool getLoseFlag() { return loseFlag; } // Get loseFlag
	GhostAction* getCurrentGhostAction() { return currentGhostAction; } // Get currentGhostAction
	vector<Cell> getGrays() { return grays; } // Get grays
	vector<Cell> getBlacks() { return blacks; } // Get blacks
	priority_queue <Cell*, vector <Cell*>, CompareCells> getPriorityQueue() { return priorityQueue; } // Get priorityQueue

	// Sets
	void setGhostRow(int ghostRowToSet) { ghostRow = ghostRowToSet; } // Set ghostRow
	void setGhostCol(int ghostColToSet) { ghostCol = ghostColToSet; } // Set ghostCol
	void setGhostHP(int ghostHPToSet) { ghostHP = ghostHPToSet; } // Set ghostHP
	void setGhostDircetionMove(int ghostDirectionMoveToSet) { ghostDircetionMove = ghostDirectionMoveToSet; } // Set ghostDircetionMove
	void setMazeGhostIn(Maze* mazeGhostInToSet) { mazeGhostIn = mazeGhostInToSet; } // Set mazeGhostIn
	void setSearchPacmanFlag(bool searchPacmanFlagToSet) { searchPacmanFlag = searchPacmanFlagToSet; } // Set searchPacmanFlag
	void setMovingFlag(bool movingFlagToSet) { movingFlag = movingFlagToSet; } // Set movingFlag
	void setFightingFlag(bool fightingFlagToSet) { fightingFlag = fightingFlagToSet; } // Set fightingFlag
	void setWinFlag(bool winFlagToSet) { winFlag = winFlagToSet; } // Set winFlag
	void setLoseFlag(bool loseFlagToSet) { loseFlag = loseFlagToSet; } // Set loseFlag
	void setCurrentGhostAction(GhostAction* currentGhostActionToSet) { currentGhostAction = currentGhostActionToSet; } // Set currentGhostAction
	void setGrays(vector<Cell>& graysToSet) { grays = graysToSet; } // Set grays
	void setBlacks(vector<Cell>& blacksToSet) { blacks = blacksToSet; } // Set blacks
	void setPriorityQueue(priority_queue <Cell*, vector <Cell*>, CompareCells>& priorityQueueToSet) { priorityQueue = priorityQueueToSet; } // Set priorityQueue

	// General functions of NPC
	void calcAndSetH(); // Calc and set h (Manhattan Distance To Pacman)
	void calcAndSetG(); // Calc and set g (Manhattan Distance To Ghost) according to that ghost
	bool getIfIsPacmanNear(); // Get if is pacman near
	void emptyGraysBlacksAndPriorityQueue(); // Empty grays, blacks & priorityQueue
	int getFirstDirectionMoveFromGhost(Cell* pCurrent); // Get first direction move from ghost
	void checkNeighbourWithAStar(int rowOfNeighbour, int colOfNeighbour, Cell* pCurrent); // Check neighbour
	void checkAllNeighboursWithAStar(int curRow, int curCol, Cell* pCurrent); // Check all neighbours of pCurrent with AStar
	int findDirectionToMoveWithAStar(); // Find direction to move with AStar
	Cell* getCellToMoveTo(); // Get cell to move to
	void moveGhostToNewCell(Cell* currCellOfGhost, Cell* newCellOfGhost); // Move ghost to new cell
	void doAction(); // Do action
};