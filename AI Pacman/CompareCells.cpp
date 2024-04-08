#include "CompareCells.h"

bool CompareCells::operator()(Cell * pc1, Cell * pc2) // Compare tow cells
{
	return (pc1->getH() + pc1->getG()) > (pc2->getH() + pc2->getG());
}