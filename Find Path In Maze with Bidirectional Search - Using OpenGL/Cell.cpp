#include "Cell.h"

Cell::Cell()
{
	cellType = SPACE;
	parent = nullptr;
}

void Cell::setParameters(int row, int col, int type)
{
	setRow(row);
	setCol(col);
	setType(type);
	setParent(nullptr);
}