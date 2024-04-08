#pragma once

#include "NPC_Pacman.h"
#include "NPC_Ghost.h"
#include "Cell.h"

class NPC_Pacman;
class NPC_Ghost;

using namespace std;

// Constants of Maze
const int MAZE_ROWS_SIZE = 50; // Size of rows in maze
const int MAZE_COLS_SIZE = 50; // Size of cols in maze
const int NUM_OF_COINS = 5; // Num of coins in maze
const int WALL_CHANCE_IN_ODD_ROW = 2; // Chance that the cell will be wall in odd row (out of 10)
const int SPACE_CHANCE_IN_EVEN_ROW = 4; // Chance that the cell will be space in even row (out of 10)
const int MILLISECONDS_DELAY_BETWEEN_SET_OF_ACTIONS = 250; // Milliseconds delay between set of actions
const int PACMAN_START_ROW = MAZE_ROWS_SIZE / 2; // Pacman start row
const int PACMAN_START_COL = MAZE_COLS_SIZE / 2; // Pacman start col
const int GHOST_1_START_ROW = 1; // Ghost 1 start row
const int GHOST_1_START_COL = 1; // Ghost 1 start col
const int GHOST_2_START_ROW = 1; // Ghost 2 start row
const int GHOST_2_START_COL = MAZE_COLS_SIZE - 2; // Ghost 2 start col
const int GHOST_3_START_ROW = MAZE_ROWS_SIZE - 2; // Ghost 3 start row
const int GHOST_3_START_COL = MAZE_COLS_SIZE / 2; // Ghost 3 start col
const int PACMAN_FIRST_HP = 4; // Pacman first HP
const int GHOST_FIRST_HP = 3; // Ghost first HP
const int NOT_FOUND_DIRECTION_YET = -2; // NOT FOUND DIRECTION YET
const int NO_DIRECTION_TO_MOVE = -1; // NO DIRECTION TO MOVE
const int STAY = 0; // STAY
const int UP = 1; // UP
const int DOWN = 2; // DOWN
const int LEFT = 3; // LEFT
const int RIGHT = 4; // RIGHT
const int GET_TO_TARGET = 5; // GET TO TARGET

class Maze
{
private:
	bool runPacmanFlag; // Run Pacman flag
	bool restartMazeFlag; // Restart maze flag
	bool restartSameMazeFlag; // Restart same maze flag
	bool needToRestartMazeFlag; // Need to restart maze flag
	NPC_Pacman* pacman; // Pacman
	NPC_Ghost* ghost1; // Ghost1
	NPC_Ghost* ghost2; // Ghost2
	NPC_Ghost* ghost3; // Ghost3
	int targetRow; // Target row
	int targetCol; // Target col
	Cell* maze; // Maze
	const char* DIRECTIONS[5] = { "STAY", "UP", "DOWN", "LEFT", "RIGHT" };

public:
	// Constructors
	Maze(); // Empty constructor

	// Gets
	bool getRunPacmanFlag() { return runPacmanFlag; } // Get runPacmanFlag
	bool getRestartMazeFlag() { return restartMazeFlag; } // Get restartMazeFlag
	bool getRestartSameMazeFlag() { return restartSameMazeFlag; } // Get restartSameMazeFlag
	bool getNeedToRestartMazeFlag() { return needToRestartMazeFlag; } // Get needToRestartMazeFlag
	NPC_Pacman* getPacman() { return pacman; } // Get pacman
	NPC_Ghost* getGhost1() { return ghost1; } // Get ghost1
	NPC_Ghost* getGhost2() { return ghost2; } // Get ghost2
	NPC_Ghost* getGhost3() { return ghost3; } // Get ghost3
	int getTargetRow() { return targetRow; } // Get targetRow
	int getTargetCol() { return targetCol; } // Get targetCol
	Cell* getMaze() { return maze; } // Get maze
	const char* getDirectionInWords(int direction) { return DIRECTIONS[direction]; } // Get direction in words

	// Sets
	void setRunPacmanFlag(bool runPacmanFlagToSet) { runPacmanFlag = runPacmanFlagToSet; } // Set runPacmanFlag
	void setRestartMazeFlag(bool restartMazeFlagToSet) { restartMazeFlag = restartMazeFlagToSet; } // Set restartMazeFlag
	void setRestartSameMazeFlag(bool restartSameMazeFlagToSet) { restartSameMazeFlag = restartSameMazeFlagToSet; } // Set restartSameMazeFlag
	void setNeedToRestartMazeFlag(bool needToRestartMazeFlagToSet) { needToRestartMazeFlag = needToRestartMazeFlagToSet; } // Set needToRestartMazeFlag
	void setPacman(NPC_Pacman* pacmanToSet) { pacman = pacmanToSet; } // Set pacman
	void getGhost1(NPC_Ghost* ghost1ToSet) { ghost1 = ghost1ToSet; } // Set ghost1
	void getGhost2(NPC_Ghost* ghost2ToSet) { ghost2 = ghost2ToSet; } // Set ghost2
	void getGhost3(NPC_Ghost* ghost3ToSet) { ghost3 = ghost3ToSet; } // Set ghost3
	void setTargetRow(int targetRowToSet) { targetRow = targetRowToSet; } // Set targetRow
	void setTargetCol(int targetColToSet) { targetCol = targetColToSet; } // Set targetCol
	void setMaze(Cell* mazeToSet) { maze = mazeToSet; } // Set maze

	// General functions
	void deleteAndeMakeMaze(); // Delete old maze and make new one
	void initFrame(); // Init the frame
	void initCellsThatNotFrame(); // Init the cells that not frame
	void restoreCellsToBegining(); // Restore cells to begining
	void calcAndSetTarget(); // Calc and set target
	void buildMaze(); // Build the maze
	void initPacman(); // Init pacman
	void initGhosts(); // Init ghosts
	void putCoinsInMaze(); // Put coins in maze
	bool checkIfCellInGrays(Cell* upNeighbour, queue<Cell>* grays); // Check if cell in grays
	bool checkIfThereIsPathToPacman(Cell& cellToCheck); // Check if there is path to pacman
	bool getMazeIsValid(); // Get maze is valid
	void initNewMaze(); // Init new maze
	void initSameMaze(); // Init same maze
	void runPacman(); // Run pacman
	bool needToDrawFace(int cellType); // Need to draw face
	void drawMaze(); // Draw the maze
	void printMazeInWords(); // Print maze in words
};