#include "Maze.h"
#include <iostream>
#include "glut.h"
#include <chrono>
#include <thread>

Maze::Maze() // Empty constructor
{
	runPacmanFlag = false;
	restartMazeFlag = false;
	restartSameMazeFlag = false;
	needToRestartMazeFlag = true;
	targetRow = 0;
	targetCol = 0;
	pacman = nullptr;
	ghost1 = nullptr;
	ghost2 = nullptr;
	ghost3 = nullptr;
	maze = nullptr;
}

void Maze::deleteAndeMakeMaze() // Delete old maze and make new one
{
	delete[] maze; // Delete old maze
	maze = new Cell[MAZE_ROWS_SIZE * MAZE_COLS_SIZE]; // Make new maze
}

void Maze::initFrame() // Init the frame
{
	for (int colNo = 0; colNo < MAZE_COLS_SIZE; colNo++) // Init the first and last rows to be walls
	{
		maze[colNo].setParametersForFirstTime(0, colNo, WALL); // First row
		maze[((MAZE_ROWS_SIZE - 1) * MAZE_COLS_SIZE) + colNo].setParametersForFirstTime(MAZE_ROWS_SIZE - 1, colNo, WALL); // Last row
	}
	for (int rowNo = 0; rowNo < MAZE_ROWS_SIZE; rowNo++) // Init the first and last cols to be walls
	{
		maze[rowNo * MAZE_COLS_SIZE].setParametersForFirstTime(rowNo, 0, WALL); // First col
		maze[(rowNo * MAZE_COLS_SIZE) + (MAZE_COLS_SIZE - 1)].setParametersForFirstTime(rowNo, MAZE_COLS_SIZE - 1, WALL); // Last col
	}
}

void Maze::initCellsThatNotFrame() // Init the cells that not frame
{
	for (int rowNo = 1; rowNo < MAZE_ROWS_SIZE - 1; rowNo++) // Move on every row (except first and last - that frame)
		for (int colNo = 1; colNo < MAZE_COLS_SIZE - 1; colNo++) // Move on every col (except first and last - that frame)
		{
			if (rowNo % 2 == 1) // Row is odd
			{
				if (rand() % 10 < WALL_CHANCE_IN_ODD_ROW) // Cell need to be WALL
					maze[rowNo * MAZE_COLS_SIZE + colNo].setParametersForFirstTime(rowNo, colNo, WALL);
				else // Cell need to be SPACE
					maze[rowNo * MAZE_COLS_SIZE + colNo].setParametersForFirstTime(rowNo, colNo, SPACE);
			}
			else // Row is even
			{
				if (rand() % 10 < SPACE_CHANCE_IN_EVEN_ROW) // Cell need to be SPACE
					maze[rowNo * MAZE_COLS_SIZE + colNo].setParametersForFirstTime(rowNo, colNo, SPACE);
				else // Cell need to be WALL
					maze[rowNo * MAZE_COLS_SIZE + colNo].setParametersForFirstTime(rowNo, colNo, WALL);
			}
		}
}

void Maze::restoreCellsToBegining() // Restore cells to begining
{
	initFrame(); // Init the frame cells

	// Restore the maze cells without the frame
	for (int rowNo = 1; rowNo < MAZE_ROWS_SIZE - 1; rowNo++) // Move on every row (except first and last - that frame)
		for (int colNo = 1; colNo < MAZE_COLS_SIZE - 1; colNo++) // Move on every col (except first and last - that frame)
			maze[rowNo * MAZE_COLS_SIZE + colNo].restoreCellToBegining(); // Restore cell
}

void Maze::calcAndSetTarget() // Calc and set target
{
	do { // Calc targetRow & targetCol
		targetRow = (rand() % (MAZE_ROWS_SIZE - 2)) + 1; // Range: between 1 to MAZE_ROWS_SIZE-2 (In order the target not on frame)
		targetCol = (rand() % (MAZE_COLS_SIZE - 2)) + 1; // Range: between 1 to MAZE_COLS_SIZE-2 (In order the target not on frame)
	} while ((targetRow == PACMAN_START_ROW) && (targetCol == PACMAN_START_COL)); // Check the START != TARGET

	maze[(targetRow * MAZE_COLS_SIZE) + targetCol].setCellType(TARGET); // Set the cell type as TARGET
	maze[(targetRow * MAZE_COLS_SIZE) + targetCol].setIsCellIsTarget(true); // Set the cell as TARGET
}

void Maze::buildMaze() // Build the maze
{
	deleteAndeMakeMaze(); // Delete old maze and make new one
	initFrame(); // Init the frame to be walls
	initCellsThatNotFrame(); // Init the cells that not frame
	calcAndSetTarget(); // Calc and set target
}

void Maze::initPacman() // Init pacman
{
	delete pacman;
	pacman = new NPC_Pacman(PACMAN_START_ROW, PACMAN_START_COL, this);
	maze[(PACMAN_START_ROW * MAZE_COLS_SIZE) + PACMAN_START_COL].addPacmanToCell(); // Add pacman to cell
	maze[(PACMAN_START_ROW * MAZE_COLS_SIZE) + PACMAN_START_COL].setIsPacmanStartedInCell(true); // Set pacmen started in cell
}

void Maze::initGhosts() // Init ghosts
{
	// Ghost1
	delete ghost1;
	ghost1 = new NPC_Ghost(GHOST_1_START_ROW, GHOST_1_START_COL, this);
	maze[(GHOST_1_START_ROW * MAZE_COLS_SIZE) + GHOST_1_START_COL].addGhostToCell(); // Add ghost1 to cell

	// Ghost2
	delete ghost2;
	ghost2 = new NPC_Ghost(GHOST_2_START_ROW, GHOST_2_START_COL, this);
	maze[(GHOST_2_START_ROW * MAZE_COLS_SIZE) + GHOST_2_START_COL].addGhostToCell(); // Add ghost2 to cell

	// Ghost3
	delete ghost3;
	ghost3 = new NPC_Ghost(GHOST_3_START_ROW, GHOST_3_START_COL, this);
	maze[(GHOST_3_START_ROW * MAZE_COLS_SIZE) + GHOST_3_START_COL].addGhostToCell(); // Add ghost3 to cell
}

void Maze::putCoinsInMaze() // Put coins in maze
{
	int coinRow, coinCol;
	for (int coinNo = 0; coinNo < NUM_OF_COINS; coinNo++) // Put num of coins
	{
		do
		{
			coinRow = (rand() % (MAZE_ROWS_SIZE - 2)) + 1; // Range: between 1 to MAZE_ROWS_SIZE-2 (In order the coin not on frame)
			coinCol = (rand() % (MAZE_COLS_SIZE - 2)) + 1; // Range: between 1 to MAZE_COLS_SIZE-2 (In order the coin not on frame)
		} while ((maze[coinRow * MAZE_COLS_SIZE + coinCol].getCellType() != WALL) && (maze[coinRow * MAZE_COLS_SIZE + coinCol].getCellType() != SPACE)); // Random cell is WALL or SPACE
		maze[coinRow * MAZE_COLS_SIZE + coinCol].initCoinFirstTime();
	}
}

bool Maze::checkIfCellInGrays(Cell* cellToCheck, queue<Cell>* grays) // Check if cell in grays
{
	queue<Cell> tmp;
	Cell* cellInGrays;
	bool foundInGrays = false;
	while (!grays->empty()) // There is grays to check
	{
		cellInGrays = &(grays->front());
		grays->pop();
		tmp.push(*cellInGrays);
		if (*cellToCheck == *cellInGrays) // Cell in grays
		{
			foundInGrays = true;
			break;
		}
	}
	while (!tmp.empty()) // Return the cells to grays
	{
		grays->push(tmp.front());
		tmp.pop();
	}
	return foundInGrays;
}

bool Maze::checkIfThereIsPathToPacman(Cell& cellToFindPathFrom) // Check if there is path to pacman
{
	Cell pc;
	queue<Cell> grays; // Queue of gray cells
	vector<Cell> blacks; // Vector of black cells
	vector<Cell>::iterator itb; // Iterator of blacks
	bool needToContinueSearch = true; // Need to continue search

	// Add cellToFindPathFrom to grays
	grays.push(cellToFindPathFrom);

	while (!grays.empty())
	{
		// Pick the first cell from grays
		pc = grays.front();
		grays.pop();

		// Check if pc is pacmanCell
		if (pc.getIsPacmanInCell())
			return true;

		// Mark cell as black
		blacks.push_back(pc);

		// Check UP neighbour
		Cell* upNeighbour = &(maze[((pc.getCellRow() - 1) * MAZE_COLS_SIZE) + pc.getCellCol()]);
		if (upNeighbour->getCellType() != WALL) // Valid cell
		{
			itb = find(blacks.begin(), blacks.end(), *upNeighbour);
			if (itb == blacks.end()) // Check if not black
				if (!checkIfCellInGrays(upNeighbour, &grays)) // Check if not gray
					grays.push(*upNeighbour);
		}

		// Check DOWN neighbour
		Cell* downNeighbour = &(maze[((pc.getCellRow() + 1) * MAZE_COLS_SIZE) + pc.getCellCol()]);
		if (downNeighbour->getCellType() != WALL) // Valid cell
		{
			itb = find(blacks.begin(), blacks.end(), *downNeighbour);
			if (itb == blacks.end()) // Check if not black
				if (!checkIfCellInGrays(downNeighbour, &grays)) // Check if not gray
					grays.push(*downNeighbour);
		}

		// Check LEFT neighbour
		Cell* leftNeighbour = &(maze[(pc.getCellRow() * MAZE_COLS_SIZE) + pc.getCellCol() - 1]);
		if (leftNeighbour->getCellType() != WALL) // Valid cell
		{
			itb = find(blacks.begin(), blacks.end(), *leftNeighbour);
			if (itb == blacks.end()) // Check if not black
				if (!checkIfCellInGrays(leftNeighbour, &grays)) // Check if not gray
					grays.push(*leftNeighbour);
		}

		// Check RIGHT neighbour
		Cell* rightNeibour = &(maze[(pc.getCellRow() * MAZE_COLS_SIZE) + pc.getCellCol() + 1]);
		if (rightNeibour->getCellType() != WALL) // Valid cell
		{
			itb = find(blacks.begin(), blacks.end(), *rightNeibour);
			if (itb == blacks.end()) // Check if not black
				if (!checkIfCellInGrays(rightNeibour, &grays)) // Check if not gray
					grays.push(*rightNeibour);
		}
	}
	return false; // Failed to find PATH, because there is no cells to check
}

bool Maze::getMazeIsValid() // Get maze is valid
{
	for (int rowNo = 0; rowNo < MAZE_ROWS_SIZE; rowNo++) // Move on every row
	{
		for (int colNo = 0; colNo < MAZE_COLS_SIZE; colNo++) // Move on every col
		{
			Cell curCell = maze[(rowNo * MAZE_COLS_SIZE) + colNo];
			if ((curCell.getThereIsCoin()) || (curCell.getNumOfGhostsInCell() > 0) || (curCell.getIsCellIsTarget())) // Need to check that there is path to pacman (COIN / GHOST / TARGET)
				if (!checkIfThereIsPathToPacman(curCell))
					return false;
		}
	}
	return true;
}

void Maze::initNewMaze() // Init new maze
{
	bool mazeIsValid = false;
	do
	{
		runPacmanFlag = false;
		buildMaze(); // Build the maze
		initPacman(); // Init pacman
		initGhosts(); // Init ghosts
		putCoinsInMaze(); // Put coins in maze
		mazeIsValid = getMazeIsValid();
	} while (!mazeIsValid);
	restartMazeFlag = false;
	restartSameMazeFlag = false;
	needToRestartMazeFlag = false;
}

void Maze::initSameMaze() // Init same maze
{
	runPacmanFlag = false;
	restoreCellsToBegining(); // Init cells
	initPacman(); // Init pacman
	initGhosts(); // Init ghosts
	restartMazeFlag = false;
	restartSameMazeFlag = false;
	needToRestartMazeFlag = false;
}

void Maze::runPacman() // Run pacman
{
	if (needToRestartMazeFlag)
	{
		cout << "You need to restart maze first\n";
		runPacmanFlag = false;
		return;
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(MILLISECONDS_DELAY_BETWEEN_SET_OF_ACTIONS)); // Milliseconds delay between set of actions
	pacman->doAction(); // Pacman do action
	ghost1->doAction(); // Ghost1 do action
	ghost2->doAction(); // Ghost2 do action
	ghost3->doAction(); // Ghost3 do action
}

bool Maze::needToDrawFace(int cellType) // Need to draw face
{
	return (cellType == PACMAN) || (cellType == GHOST);
}

void Maze::drawMaze() // Draw the maze
{
	for (int rowNo = 0; rowNo < MAZE_ROWS_SIZE; rowNo++) // Move on every row
		for (int colNo = 0; colNo < MAZE_COLS_SIZE; colNo++) // Move on every col
		{
			switch (maze[rowNo * MAZE_COLS_SIZE + colNo].getCellType()) // Check the cell type - to set the cell color
			{
			case SPACE:
				glColor3d(1, 1, 1); // white
				break;
			case WALL:
				glColor3d(0, 0, 0); // black
				break;
			case COIN:
				glColor3d(0.8, 0.5, 0.2); // gold
				break;
			case TARGET:
				glColor3d(1, 0, 0); // red
				break;
			case PACMAN:
				glColor3d(1, 1, 0); // yellow
				break;
			case GHOST:
				glColor3d(0.97, 0.78, 0.86); // pastel pink
				break;
			}

			// Draw the cell
			if (maze[rowNo * MAZE_COLS_SIZE + colNo].getCellType() == COIN) // Coin (POINT on POLYGON)
			{
				// SPACE
				glColor3d(1, 1, 1); // white
				glBegin(GL_POLYGON);
				glVertex2d(colNo, rowNo); // Left up
				glVertex2d(colNo + 1, rowNo); // Right up
				glVertex2d(colNo + 1, rowNo + 1); // Right down
				glVertex2d(colNo, rowNo + 1); // Left down
				glEnd();

				// COIN
				glColor3d(0.8, 0.5, 0.2); // gold
				glPointSize(5);
				glBegin(GL_POINTS);
				glVertex2d(colNo + 0.5, rowNo + 0.5);
				glEnd();
				glPointSize(1);

			}
			else // Not coin (POLYGON)
			{
				glBegin(GL_POLYGON);
				glVertex2d(colNo, rowNo); // Left up
				glVertex2d(colNo + 1, rowNo); // Right up
				glVertex2d(colNo + 1, rowNo + 1); // Right down
				glVertex2d(colNo, rowNo + 1); // Left down
				glEnd();
			}

			// Draw face
			if (needToDrawFace(maze[rowNo * MAZE_COLS_SIZE + colNo].getCellType()))
			{
				// Left eye
				glColor3d(0, 0, 0); // black
				glBegin(GL_POLYGON);
				glVertex2d(colNo + 0.2, rowNo + 0.25); // Left up
				glVertex2d(colNo + 0.4, rowNo + 0.25); // Right up
				glVertex2d(colNo + 0.4, rowNo + 0.45); // Right down
				glVertex2d(colNo + 0.2, rowNo + 0.45); // Left down
				glEnd();

				// Right eye
				glColor3d(0, 0, 0); // black
				glBegin(GL_POLYGON);
				glVertex2d(colNo + 0.6, rowNo + 0.25); // Left up
				glVertex2d(colNo + 0.8, rowNo + 0.25); // Right up
				glVertex2d(colNo + 0.8, rowNo + 0.45); // Right down
				glVertex2d(colNo + 0.6, rowNo + 0.45); // Left down
				glEnd();

				// Mouth
				glColor3d(0, 0, 0); // black
				glBegin(GL_LINE_LOOP);
				glVertex2d(colNo + 0.2, rowNo + 0.7); // Left up
				glVertex2d(colNo + 0.2, rowNo + 0.85); // Right up
				glVertex2d(colNo + 0.8, rowNo + 0.85); // Right down
				glVertex2d(colNo + 0.8, rowNo + 0.7); // Left down
				glEnd();
			}
		}
}

void Maze::printMazeInWords() // Print maze in words
{
	for (int rowNo = 0; rowNo < MAZE_ROWS_SIZE; rowNo++)
	{
		for (int colNo = 0; colNo < MAZE_COLS_SIZE; colNo++)
		{
			cout << "Row: " << maze[rowNo * MAZE_COLS_SIZE + colNo].getCellRow()
				<< ", Col: " << maze[rowNo * MAZE_COLS_SIZE + colNo].getCellCol() 
				<< ", cellType: " << maze[rowNo * MAZE_COLS_SIZE + colNo].getCellType() << "\t";
		}
		cout << "\n";
	}
}