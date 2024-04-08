#include <iostream> 
#include <math.h>
#include "NPC_Ghost.h"
#include "GhostActionSearchPacman.h"

NPC_Ghost::NPC_Ghost(int rowToSet, int colToSet, Maze* mazeGhostInToSet) // Constructor
{
	ghostRow = rowToSet;
	ghostCol = colToSet;
	ghostHP = GHOST_FIRST_HP;
	ghostDircetionMove = STAY;
	mazeGhostIn = mazeGhostInToSet;
	searchPacmanFlag = false;
	movingFlag = false;
	fightingFlag = false;
	winFlag = false;
	loseFlag = false;
	currentGhostAction = new GhostActionSearchPacman();
	currentGhostAction->OnEnter(this);
}

void NPC_Ghost::calcAndSetH() // Calc and set h (Manhattan Distance To Pacman)
{
	int pacmanRow = mazeGhostIn->getPacman()->getPacmanRow();
	int pacmanCol = mazeGhostIn->getPacman()->getPacmanCol();
	for (int rowNo = 0; rowNo < MAZE_ROWS_SIZE; rowNo++) // Move on every row
		for (int colNo = 0; colNo < MAZE_COLS_SIZE; colNo++) // Move on every col
			mazeGhostIn->getMaze()[(rowNo * MAZE_COLS_SIZE) + colNo].setH((int)(fabs(pacmanRow - rowNo) + fabs(pacmanCol - colNo)));
}

void NPC_Ghost::calcAndSetG() // Calc and set g (Manhattan Distance To Ghost) according to that ghost
{
	int pacmanRow = mazeGhostIn->getPacman()->getPacmanRow();
	int pacmanCol = mazeGhostIn->getPacman()->getPacmanCol();
	for (int rowNo = 0; rowNo < MAZE_ROWS_SIZE; rowNo++) // Move on every row
		for (int colNo = 0; colNo < MAZE_COLS_SIZE; colNo++) // Move on every col
			mazeGhostIn->getMaze()[(rowNo * MAZE_COLS_SIZE) + colNo].setG((int)(fabs(ghostRow - rowNo) + fabs(ghostCol - colNo)));
}

bool NPC_Ghost::getIfIsPacmanNear() // Get if is pacman near
{
	bool pacmanInUpCell = mazeGhostIn->getMaze()[((ghostRow - 1) * MAZE_COLS_SIZE) + ghostCol].getIsPacmanInCell(); // Get if pacman in UP neighbour
	bool pacmanInDownCell = mazeGhostIn->getMaze()[((ghostRow + 1) * MAZE_COLS_SIZE) + ghostCol].getIsPacmanInCell(); // Get if pacman in DOWN neighbour
	bool pacmanInLeftCell = mazeGhostIn->getMaze()[(ghostRow * MAZE_COLS_SIZE) + ghostCol - 1].getIsPacmanInCell(); // Get if pacman in LEFT neighbour
	bool pacmanInRightCell = mazeGhostIn->getMaze()[(ghostRow * MAZE_COLS_SIZE) + ghostCol + 1].getIsPacmanInCell(); // Get if pacman in RIGHT neighbour
	return pacmanInUpCell || pacmanInDownCell || pacmanInLeftCell || pacmanInRightCell;
}

void NPC_Ghost::emptyGraysBlacksAndPriorityQueue() // Empty grays, blacks & priorityQueue
{
	while (!grays.empty()) // Clear grays
		grays.pop_back();
	while (!blacks.empty()) // Clear blacks
		blacks.pop_back();
	while (!priorityQueue.empty()) // Clear priorityQueue
		priorityQueue.pop();
}

int NPC_Ghost::getFirstDirectionMoveFromGhost(Cell* pCurrent) // Get first direction move from ghost
{
	Cell* cellGhostIn = &(mazeGhostIn->getMaze()[(ghostRow * MAZE_COLS_SIZE) + ghostCol]);
	int direction = 0;
	cout << "Ghost found: PACMAN At (" << pCurrent->getCellRow() << "," << pCurrent->getCellCol() << ")"; // Print what Ghost found
	while (!(*pCurrent == *cellGhostIn)) // Move on every cell until get to GHOST
	{
		Cell* father = pCurrent->getParent();
		if (father->getCellRow() - pCurrent->getCellRow() == 1) // Moved UP from father
			direction = UP;
		else if (father->getCellRow() - pCurrent->getCellRow() == -1) // Moved DOWN from father
			direction = DOWN;
		else if (father->getCellCol() - pCurrent->getCellCol() == 1) // Moved LEFT from father
			direction = LEFT;
		else // Moved RIGHT from father
			direction = RIGHT;
		pCurrent = pCurrent->getParent(); // Move to "father" cell
	}
	cout << ", Moving: " << mazeGhostIn->getDirectionInWords(direction) << "\n"; // Print where ghost moving
	return direction;
}

void NPC_Ghost::checkNeighbourWithAStar(int rowOfNeighbour, int colOfNeighbour, Cell* pCurrent) // Check neighbour
{
	Cell* pNeighbour = &(mazeGhostIn->getMaze()[(rowOfNeighbour * MAZE_COLS_SIZE) + colOfNeighbour]);

	vector<Cell>::iterator itrBlacks; // Iterator of blacks
	vector<Cell>::iterator itrGrays; // Iterator of grays

	itrBlacks = find(blacks.begin(), blacks.end(), *pNeighbour);
	itrGrays = find(grays.begin(), grays.end(), *pNeighbour);

	if (itrBlacks != blacks.end()) //  Neighbour is black
		return;
	else if (itrGrays != grays.end()) // Neighbour is gray 
	{
		int pacmanRow = mazeGhostIn->getPacman()->getPacmanRow();
		int pacmanCol = mazeGhostIn->getPacman()->getPacmanRow();
		if ((itrGrays->getH() + itrGrays->getG()) > (pNeighbour->getH() + pNeighbour->getG())) // Need to exchange what has been stored in grays and pNeighbour
		{
			// Update in grays
			*itrGrays = *pNeighbour;

			// Set parent
			pNeighbour->setParent(pCurrent);

			// Update it in priorityQueue
			vector<Cell*> tmp;
			Cell* pn;
			bool found = false;
			while (!priorityQueue.empty() && !found)
			{
				pn = priorityQueue.top();
				priorityQueue.pop();
				if ((*pn) == (*pNeighbour)) // Found neighbour in priorityQueue
					found = true;
				else // Not found neighbour in priorityQueue yet
					tmp.push_back(pn);
			}
			if (priorityQueue.empty()) // Not found neighbour in priorityQueue at all
			{
				cout << "ERROR!!! Neighbour wasn't found in priorityQueue\n";
				exit(4);
			}
			else // Found neighbour in priorityQueue
			{
				priorityQueue.push(pNeighbour);
				while (!tmp.empty()) // Restore priorityQueue
				{
					pn = tmp.back();
					tmp.pop_back();
					priorityQueue.push(pn);
				}
			}
		}
	}
	else // Neighbour is white
	{
		// Set parent
		pNeighbour->setParent(pCurrent);

		// Add to grays & priorityQueue
		grays.push_back(*pNeighbour);
		priorityQueue.push(pNeighbour);
	}
}

void NPC_Ghost::checkAllNeighboursWithAStar(int curRow, int curCol, Cell* pCurrent) // Check all neighbours of pCurrent with AStar
{
	if (mazeGhostIn->getMaze()[((curRow - 1) * MAZE_COLS_SIZE) + curCol].getCellType() != WALL)
		checkNeighbourWithAStar(curRow - 1, curCol, pCurrent); // UP
	if (mazeGhostIn->getMaze()[((curRow + 1) * MAZE_COLS_SIZE) + curCol].getCellType() != WALL)
		checkNeighbourWithAStar(curRow + 1, curCol, pCurrent); // DOWN
	if (mazeGhostIn->getMaze()[(curRow * MAZE_COLS_SIZE) + curCol - 1].getCellType() != WALL)
		checkNeighbourWithAStar(curRow, curCol - 1, pCurrent); // LEFT
	if (mazeGhostIn->getMaze()[(curRow * MAZE_COLS_SIZE) + curCol + 1].getCellType() != WALL)
		checkNeighbourWithAStar(curRow, curCol + 1, pCurrent); // RIGHT
}

int NPC_Ghost::findDirectionToMoveWithAStar() // Find direction to move with AStar
{
	Cell* pCurrent = &(mazeGhostIn->getMaze()[(ghostRow * MAZE_COLS_SIZE) + ghostCol]);
	vector<Cell>::iterator itrGrays;

	emptyGraysBlacksAndPriorityQueue(); // Empty grays, blacks & priorityQueue

	 // Insert ghost cell to grays & priorityQueue
	grays.push_back(*pCurrent);
	priorityQueue.push(pCurrent);

	while (!priorityQueue.empty()) // There is cells to check
	{
		pCurrent = priorityQueue.top(); // Pick the best cell

		// Check if get to PACMAN
		if (pCurrent->getIsPacmanInCell())
			return getFirstDirectionMoveFromGhost(pCurrent);

		priorityQueue.pop(); // Pop the best node from priority queue

		itrGrays = find(grays.begin(), grays.end(), *pCurrent); // Extract pCurrent from grays (implement operator ==)

		// Check that pCurrent found
		if (itrGrays == grays.end())
		{
			cout << "Error: pCurrent wasn't found in grays of ghost\n";
			exit(1);
		}

		grays.erase(itrGrays); // Remove pCurrent from grays

		blacks.push_back(*pCurrent); // Mark cell as black

		checkAllNeighboursWithAStar(pCurrent->getCellRow(), pCurrent->getCellCol(), pCurrent); // Check all neighbors of pCurrent with AStar
	}
	cout << "There is no path to ghost, please restart maze\n";
	mazeGhostIn->setRunPacmanFlag(false);
	mazeGhostIn->setNeedToRestartMazeFlag(true);
	return NO_DIRECTION_TO_MOVE;
}

Cell* NPC_Ghost::getCellToMoveTo() // Get cell to move to
{
	switch (ghostDircetionMove)
	{
	case UP: // Need to move UP
		return &(mazeGhostIn->getMaze()[((ghostRow - 1) * MAZE_COLS_SIZE) + ghostCol]);
	case DOWN: // Need to move DOWN
		return &(mazeGhostIn->getMaze()[((ghostRow + 1) * MAZE_COLS_SIZE) + ghostCol]);
	case LEFT: // Need to move LEFT
		return &(mazeGhostIn->getMaze()[(ghostRow * MAZE_COLS_SIZE) + ghostCol - 1]);
	case RIGHT: // Need to move RIGHT
		return &(mazeGhostIn->getMaze()[(ghostRow * MAZE_COLS_SIZE) + ghostCol + 1]);
	}
	return nullptr;
}

void NPC_Ghost::moveGhostToNewCell(Cell* currCellOfGhost, Cell* newCellOfGhost) // Move ghost to new cell
{
	newCellOfGhost->addGhostToCell(); // Add ghost to new cell
	currCellOfGhost->removeGhostFromCell(); // Remove ghost from old cell
	if (currCellOfGhost->getIsCellIsTarget()) // The old cell is TARGET
		currCellOfGhost->setCellType(TARGET);
	if(currCellOfGhost->getThereIsCoin()) // The old cell contain COIN
		currCellOfGhost->setCellType(COIN);
	ghostRow = newCellOfGhost->getCellRow(); // Update ghost row
	ghostCol = newCellOfGhost->getCellCol(); // Update ghost col
}

void NPC_Ghost::doAction() // Do action
{
	if (mazeGhostIn->getRunPacmanFlag()) // Need to do action
	{
		calcAndSetH(); // Calc and set h according to that ghost
		calcAndSetG(); // Calc and set g according to that ghost
		if (searchPacmanFlag) // Search pacman
		{
			if (getIfIsPacmanNear()) // There is pacman near, so need to STAY
				ghostDircetionMove = STAY;
			else // Need to move
				ghostDircetionMove = findDirectionToMoveWithAStar();
			currentGhostAction->Transition(this);
		}
		else if (movingFlag) // Moving
		{
			if (!getIfIsPacmanNear()) // Need to move
			{
				Cell* currCellOfGhost = &(mazeGhostIn->getMaze()[(ghostRow * MAZE_COLS_SIZE) + ghostCol]);
				Cell* newCellOfGhost = getCellToMoveTo();
				moveGhostToNewCell(currCellOfGhost, newCellOfGhost);
			}
			else // There is pacman near (PACMAN moved next to GHOST) so need to STAY
			{
				ghostDircetionMove = STAY;
				currentGhostAction->Transition(this);
				doAction(); // Change action
				return;
			}
			currentGhostAction->Transition(this);
		}
		else if (fightingFlag) // Fighting
		{
			if (getIfIsPacmanNear()) // Check the PACMAN didn't die
			{
				cout << "Ghost is fighting, GhostHP before fighting: " << ghostHP;
				ghostHP--;
				cout << ", GhostHP after fighting: " << ghostHP << "\n";
				if (ghostHP <= 0)
				{
					cout << "Ghost lost in fight!\n";
					mazeGhostIn->getMaze()[(ghostRow * MAZE_COLS_SIZE) + ghostCol].removeGhostFromCell();
				}
			}
			currentGhostAction->Transition(this);
		}
		else if (winFlag) // Win
		{
			mazeGhostIn->setRunPacmanFlag(false);
			mazeGhostIn->setNeedToRestartMazeFlag(true);
			currentGhostAction->Transition(this);
		}
		else if (loseFlag) // Lose
		{
			currentGhostAction->Transition(this);
		}
	}
}