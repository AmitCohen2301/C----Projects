#include "Cell.h"
#include <math.h>

Cell::Cell() // Empty constructor
{
	cellType = SPACE;
	thereIsCoin = false;
	wasCoinAtBegin = false;
	numOfGhostsInCell = 0;
	isCellIsTarget = false;
	isPacmanInCell = false;
	isPacmanStartedInCell = false;
	h = 0;
	g = 0;
	parent = nullptr;
}

void Cell::setParametersForFirstTime(int rowToSet, int colToSet, int cellTypeToSet) // Set row, col and cellType for first time
{
	// Row & Col
	cellRow = rowToSet;
	cellCol = colToSet;

	// Cell type
	cellType = cellTypeToSet;

	// Coin
	if (cellTypeToSet == COIN)
	{
		thereIsCoin = true;
		wasCoinAtBegin = true;
	}
	else
	{
		thereIsCoin = false;
		wasCoinAtBegin = false;
	}

	// Ghost
	if (cellTypeToSet == GHOST)
		numOfGhostsInCell = 1;
	else
		numOfGhostsInCell = 0;

	// Target
	if (cellTypeToSet == TARGET)
		isCellIsTarget = true;
	else
		isCellIsTarget = false;

	// Pacman in cell
	if (cellTypeToSet == PACMAN)
	{
		isPacmanInCell = true;
		isPacmanStartedInCell = true;
	}
	else
	{
		isPacmanInCell = false;
		isPacmanStartedInCell = false;
	}

	// Parent
	parent = nullptr;
}

void Cell::restoreCellToBegining() // Restore cell to begining
{
	// Restore cellType
	switch (cellType)
	{
	case SPACE:
	case WALL:
	case TARGET:
		break;
	case COIN:
	case PACMAN:
	case GHOST:
		cellType = SPACE;
		break;
	}

	// Restore coin
	if (wasCoinAtBegin)
	{
		thereIsCoin = true;
		cellType = COIN;
	}
	else
		thereIsCoin = false;

	// Restore no ghosts in cell
	numOfGhostsInCell = 0;

	// Restore cell target
	if (isCellIsTarget)
		cellType = TARGET;

	// Pacman in cell
	if (isPacmanStartedInCell)
	{
		cellType = PACMAN;
		isPacmanInCell = true;
	}
	else
		isPacmanInCell = false;

	// Restore no parent
	parent = nullptr;
}

void Cell::initCoinFirstTime() // Init coin first time
{
	thereIsCoin = true;
	wasCoinAtBegin = true;
	cellType = COIN;
}

bool Cell::isThereIsGhostInCell() // Is there is ghost in cell
{
	return numOfGhostsInCell > 0;
}

void Cell::addPacmanToCell() // Add pacman to cell
{
	isPacmanInCell = true;
	cellType = PACMAN;
}

void Cell::removePacmanFromCell() // Remove pacman from cell
{
	isPacmanInCell = false;
	cellType = SPACE;
}

void Cell::addGhostToCell() // Add ghost to cell
{
	numOfGhostsInCell++;
	cellType = GHOST;
}

void Cell::removeGhostFromCell() // Remove ghost from cell
{
	numOfGhostsInCell--;
	if (numOfGhostsInCell == 0)
		cellType = SPACE;
}

bool Cell::operator==(const Cell& other) // Check if cells are the same
{
	return (cellRow == other.cellRow) && (cellCol == other.cellCol);
}