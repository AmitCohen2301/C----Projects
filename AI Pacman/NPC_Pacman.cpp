#include <iostream> 
#include "NPC_Pacman.h"
#include "PacmanActionSearchTarget.h"
#include "PacmanActionSearchCoin.h"

NPC_Pacman::NPC_Pacman(int rowToSet, int colToSet, Maze* mazeToSet) // Constructor
{
	pacmanRow = rowToSet;
	pacmanCol = colToSet;
	pacmanHP = PACMAN_FIRST_HP;
	pacmanDircetionMove = STAY;
	numOfCollectedCoins = 0;
	mazePacmanIn = mazeToSet;
	searchCoinFlag = false;
	movingFlag = false;
	searchTargetFlag = false;
	fightingFlag = false;
	winFlag = false;
	loseFlag = false;
	if (NUM_OF_COINS == 0) // No coins at maze
		currentPacmanAction = new PacmanActionSearchTarget();
	else
		currentPacmanAction = new PacmanActionSearchCoin();
	currentPacmanAction->OnEnter(this);
}

bool NPC_Pacman::getIfGetToTargetPoint() // Get if get to target point
{
	return (pacmanRow == mazePacmanIn->getTargetRow()) && (pacmanCol == mazePacmanIn->getTargetCol());
}

int NPC_Pacman::getNumOfGhostsNearPacman() // Get num of ghosts near pacman
{
	int numOfGhostsNearPacman = 0;
	numOfGhostsNearPacman += mazePacmanIn->getMaze()[((pacmanRow - 1) * MAZE_COLS_SIZE) + pacmanCol].getNumOfGhostsInCell(); // Add num of ghosts in UP neighbour
	numOfGhostsNearPacman += mazePacmanIn->getMaze()[((pacmanRow + 1) * MAZE_COLS_SIZE) + pacmanCol].getNumOfGhostsInCell(); // Add num of ghosts in DOWN neighbour
	numOfGhostsNearPacman += mazePacmanIn->getMaze()[(pacmanRow * MAZE_COLS_SIZE) + pacmanCol - 1].getNumOfGhostsInCell(); // Add num of ghosts in LEFT neighbour
	numOfGhostsNearPacman += mazePacmanIn->getMaze()[(pacmanRow * MAZE_COLS_SIZE) + pacmanCol + 1].getNumOfGhostsInCell(); // Add num of ghosts in RIGHT neighbour
	return numOfGhostsNearPacman;
}

void NPC_Pacman::emptyGraysAndBlacks() // Empty grays & blacks
{
	while (!grays.empty()) // Empty grays
		grays.pop();
	while (!blacks.empty()) // Empty blacks
		blacks.pop_back();
}

bool NPC_Pacman::checkIfGray(Cell* cellToCheck) // Check if cell is gray
{
	queue<Cell> tmp;
	Cell* cellInGrays;
	bool foundInGrays = false;
	while (!grays.empty()) // There is grays to check
	{
		cellInGrays = &(grays.front());
		grays.pop();
		tmp.push(*cellInGrays);
		if (*cellToCheck == *cellInGrays) // Cell in grays
		{
			foundInGrays = true;
			break;
		}
	}
	while (!tmp.empty()) // Return the cells
	{
		grays.push(tmp.front());
		tmp.pop();
	}
	return foundInGrays;
}

void NPC_Pacman::chooseRandomDirections(int* pDirections) // Choose random directions
{
	int place;
	for (int dir = 1; dir < 5; dir++)
	{
		do {
			place = rand() % 4;
		} while (pDirections[place] != -1);
		pDirections[place] = dir;
	}
}

int NPC_Pacman::getFirstDirectionMoveFromPacman(Cell* pCurrent) // Get first direction move from pacman
{
	int direction = 0;
	cout << "Pacman found: " << pCurrent->getTypeInWords(pCurrent->getCellType()) << " At (" << pCurrent->getCellRow() << "," << pCurrent->getCellCol() << ")"; // Print what pacman found
	while (!(pCurrent->getIsPacmanInCell())) // Move on every cell until get to PACMAN cell
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
	cout << ", In direction " << mazePacmanIn->getDirectionInWords(direction);
	return direction;
}

int NPC_Pacman::findNewDirectionToRunFromGhost(int direction) // New find new direction to run from ghost
{
	Cell* upCell = &(mazePacmanIn->getMaze()[((pacmanRow - 1) * MAZE_COLS_SIZE) + pacmanCol]);
	Cell* downCell = &(mazePacmanIn->getMaze()[((pacmanRow + 1) * MAZE_COLS_SIZE) + pacmanCol]);
	Cell* leftCell = &(mazePacmanIn->getMaze()[(pacmanRow * MAZE_COLS_SIZE) + pacmanCol - 1]);
	Cell* rightCell = &(mazePacmanIn->getMaze()[(pacmanRow * MAZE_COLS_SIZE) + pacmanCol + 1]);
	int pDirections[4] = { -1, -1, -1, -1 };

	chooseRandomDirections(pDirections); // Choose random direction to move

	for (int place = 0; place < 4; place++) // Move on all directions
	{
		if (pDirections[place] != direction) // Not direction, because need to run
		{
			if ((pDirections[place] == UP) && (upCell->getCellType() != WALL))
				return UP;
			if ((pDirections[place] == DOWN) && (downCell->getCellType() != WALL))
				return DOWN;
			if ((pDirections[place] == LEFT) && (leftCell->getCellType() != WALL))
				return LEFT;
			if ((pDirections[place] == RIGHT) && (rightCell->getCellType() != WALL))
				return RIGHT;
		}
	}
	return direction; // All other directions are WALL
}

int NPC_Pacman::checkNeighbour(int neighbourRow, int neighbourCol, Cell* pCurrent, int* pNumOfFoundGhosts, int typeToSearch) // Check neighbour
{
	Cell* pNeighbour = &(mazePacmanIn->getMaze()[(neighbourRow * MAZE_COLS_SIZE) + neighbourCol]);
	vector<Cell>::iterator itrBlacks = find(blacks.begin(), blacks.end(), *pNeighbour); // Iterator of blacks

	if (pNeighbour->getCellType() == WALL) // Neighbour is wall, not need to check
		return NOT_FOUND_DIRECTION_YET;

	if (itrBlacks != blacks.end()) // Neighbour is black, not need to check
		return NOT_FOUND_DIRECTION_YET;

	if (checkIfGray(pNeighbour)) // Neighbour is gray, not need to check now
		return NOT_FOUND_DIRECTION_YET;

	pNeighbour->setParent(&(mazePacmanIn->getMaze()[(pCurrent->getCellRow() * MAZE_COLS_SIZE) + pCurrent->getCellCol()])); // Set parent

	// Neighbour is white, so check if neighbour is typeToSearch or ghost
	if (pNeighbour->getNumOfGhostsInCell() > 0) // Neighbour is GHOST
	{
		*pNumOfFoundGhosts += pNeighbour->getNumOfGhostsInCell(); // Update num of found ghosts
		if (pacmanHP < ((*pNumOfFoundGhosts) * GHOST_FIRST_HP)) // Check if need to run (enough HP)
			return findNewDirectionToRunFromGhost(getFirstDirectionMoveFromPacman(pNeighbour));
	}
	else if ((typeToSearch == COIN) && (pNeighbour->getThereIsCoin())) // Search COIN and neighbour is COIN
		return getFirstDirectionMoveFromPacman(pNeighbour);
	else if ((typeToSearch == TARGET) && (pNeighbour->getIsCellIsTarget())) // Search TARGET and neighbour is TARGET
		return getFirstDirectionMoveFromPacman(pNeighbour);

	// Not get to typeToSearch or to run
	grays.push(*pNeighbour); // Add neighbour to grays
	return NOT_FOUND_DIRECTION_YET;
}

int NPC_Pacman::checkAllNeighbours(Cell* pCurrent, int* pNumOfFoundGhosts, int typeToSearch) // Check all neighbours
{
	int directionToMove = NOT_FOUND_DIRECTION_YET;
	int rowCell = pCurrent->getCellRow();
	int colCell = pCurrent->getCellCol();
	int directions[4] = { -1, -1, -1, -1 };

	chooseRandomDirections(directions); //Choose random direction to check

	// Check all neighbours
	for (int dirNo = 0; dirNo < sizeof(directions) / sizeof(int); dirNo++)
	{
		if (directions[dirNo] == UP) // UP neighbour
		{
			directionToMove = checkNeighbour(rowCell - 1, colCell, pCurrent, pNumOfFoundGhosts, typeToSearch);
			if (directionToMove != NOT_FOUND_DIRECTION_YET) // Found path
				return directionToMove;
		}
		else if (directions[dirNo] == DOWN) // DOWN neighbour
		{
			directionToMove = checkNeighbour(rowCell + 1, colCell, pCurrent, pNumOfFoundGhosts, typeToSearch);
			if (directionToMove != NOT_FOUND_DIRECTION_YET) // Found path
				return directionToMove;
		}
		else if (directions[dirNo] == LEFT) // LEFT neighbour
		{
			directionToMove = checkNeighbour(rowCell, colCell - 1, pCurrent, pNumOfFoundGhosts, typeToSearch);
			if (directionToMove != NOT_FOUND_DIRECTION_YET) // Found path
				return directionToMove;
		}
		else if (directions[dirNo] == RIGHT) // RIGHT neighbour
		{
			directionToMove = checkNeighbour(rowCell, colCell + 1, pCurrent, pNumOfFoundGhosts, typeToSearch);
			if (directionToMove != NOT_FOUND_DIRECTION_YET) // Found path
				return directionToMove;
		}
	}
	return directionToMove;
}

int NPC_Pacman::findDirectionToMoveToTypeWithBFS(int typeToSearch) // Find direction to move to type with BFS
{
	int direction = NO_DIRECTION_TO_MOVE;
	Cell currentCell;
	int numOfFoundGhosts = 0;

	if (getNumOfGhostsNearPacman() > 0) // Need to STAY (fight)
		return STAY;

	emptyGraysAndBlacks(); // Empty grays and blacks

	grays.push(mazePacmanIn->getMaze()[(pacmanRow * MAZE_COLS_SIZE) + pacmanCol]); // Insert pacman cell to grays

	while (!(grays.empty())) // Continue to find path to type, because there are cells to check
	{
		// Pick the first cell from grays
		currentCell = grays.front();
		grays.pop();

		// Mark cell as black
		blacks.push_back(currentCell);

		// Neighbours checks (if they are white add them to grays, if one of them is coin or a lot of ghosts then find path)
		direction = checkAllNeighbours(&currentCell, &numOfFoundGhosts, typeToSearch);
		if (direction != NOT_FOUND_DIRECTION_YET) // Found path
		{
			cout << " So moving: " << mazePacmanIn->getDirectionInWords(direction) << "\n";
			return direction;
		}
	}

	// Failed to find PATH to type, because there is no cells to check
	cout << "There is no path to pacman, please restart maze\n";
	mazePacmanIn->setRunPacmanFlag(false);
	mazePacmanIn->setNeedToRestartMazeFlag(true);
	return NO_DIRECTION_TO_MOVE;
}

Cell* NPC_Pacman::getCellToMoveTo() // Get cell to move to
{
	switch (pacmanDircetionMove)
	{
	case UP: // Need to move UP
		return &(mazePacmanIn->getMaze()[((pacmanRow - 1) * MAZE_COLS_SIZE) + pacmanCol]);
	case DOWN: // Need to move DOWN
		return &(mazePacmanIn->getMaze()[((pacmanRow + 1) * MAZE_COLS_SIZE) + pacmanCol]);
	case LEFT: // Need to move LEFT
		return &(mazePacmanIn->getMaze()[(pacmanRow * MAZE_COLS_SIZE) + pacmanCol - 1]);
	case RIGHT: // Need to move RIGHT
		return &(mazePacmanIn->getMaze()[(pacmanRow * MAZE_COLS_SIZE) + pacmanCol + 1]);
	}
	return nullptr;
}

void NPC_Pacman::collectCoin() // Collect coin
{ 
	numOfCollectedCoins++;
	mazePacmanIn->getMaze()[(pacmanRow * MAZE_COLS_SIZE) + pacmanCol].setThereIsCoin(false);
}

void NPC_Pacman::movePacmanToNewCell(Cell* currCellOfPacman, Cell* newCellOfPacman) // Move pacman to new cell
{
	newCellOfPacman->addPacmanToCell(); // Add pacman to new cell
	currCellOfPacman->removePacmanFromCell(); // Remove pacman from old cell
	if (currCellOfPacman->getIsCellIsTarget()) // The old cell is TARGET
		currCellOfPacman->setCellType(TARGET);
	pacmanRow = newCellOfPacman->getCellRow(); // Update pacman row
	pacmanCol = newCellOfPacman->getCellCol(); // Update pacman col
	if (newCellOfPacman->getThereIsCoin()) // Need to collect coin
		collectCoin();
}

void NPC_Pacman::doAction() // Do action
{
	if (mazePacmanIn->getRunPacmanFlag()) // Need to do action
	{
		if (searchCoinFlag) // Search coin
		{
			int numOfGhostsNearPacman = getNumOfGhostsNearPacman();
			if (numOfGhostsNearPacman > 0) // There is ghost near, so need to STAY
				pacmanDircetionMove = STAY;
			else // Need to move
				pacmanDircetionMove = findDirectionToMoveToTypeWithBFS(COIN);
			currentPacmanAction->Transition(this);
		}
		else if (movingFlag) // Moving
		{
			if (getNumOfGhostsNearPacman() == 0) // Need to move
			{
				Cell* currCellOfPacman = &(mazePacmanIn->getMaze()[(pacmanRow * MAZE_COLS_SIZE) + pacmanCol]);
				Cell* newCellOfPacman = getCellToMoveTo();
				movePacmanToNewCell(currCellOfPacman, newCellOfPacman);
			}
			else // There is ghost near (GHOST moved next to PACMAN) so need to STAY
			{
				pacmanDircetionMove = STAY;
				currentPacmanAction->Transition(this);
				doAction(); // Change action
				return;
			}
			currentPacmanAction->Transition(this);
		}
		else if (searchTargetFlag) // Search target
		{
			int numOfGhostsNearPacman = getNumOfGhostsNearPacman();
			if (numOfGhostsNearPacman > 0) // There is ghost near, so need to STAY
				pacmanDircetionMove = STAY;
			else // Need to move
				pacmanDircetionMove = findDirectionToMoveToTypeWithBFS(TARGET);
			currentPacmanAction->Transition(this);
		}
		else if (fightingFlag) // Fighting
		{
			if (getNumOfGhostsNearPacman() > 0) // Check the GHOST didn't die
			{
				int numOfGhostsNear = getNumOfGhostsNearPacman();
				cout << "Pacman is fighting agains: " << numOfGhostsNear << " ghsots, PacmanHP before fighting: " << pacmanHP;
				pacmanHP -= numOfGhostsNear;
				cout << ", PacmanHP after fighting: " << pacmanHP << "\n";
				if (pacmanHP <= 0) // Lose
				{
					cout << "The pacman lost!\n";
					cout << "Please restart maze if you want new game\n";
					mazePacmanIn->getMaze()[(pacmanRow * MAZE_COLS_SIZE) + pacmanCol].removePacmanFromCell();
					mazePacmanIn->setRunPacmanFlag(false);
					mazePacmanIn->setNeedToRestartMazeFlag(true);
				}
			}
			currentPacmanAction->Transition(this);
		}
		else if (winFlag) // Win
		{
			cout << "The pacman won!\n";
			cout << "Please restart maze if you want new game\n";
			mazePacmanIn->setRunPacmanFlag(false);
			mazePacmanIn->setNeedToRestartMazeFlag(true);
			currentPacmanAction->Transition(this);
		}
		else if (loseFlag)
		{
			currentPacmanAction->Transition(this);
		}
	}
}