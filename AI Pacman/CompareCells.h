#pragma once

#include "Cell.h"

class CompareCells
{
public:
	bool operator() (Cell* pc1, Cell* pc2); // Compare tow cells by ghost
};