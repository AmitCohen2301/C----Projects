#pragma once

// Constants of maze
const int MAZE_SIZE = 100; // Size of rows and cols in maze
const int WALL_CHANCE_IN_ODD_ROW = 2; // Chance that the cell will be wall in odd row (out of 10)
const int SPACE_CHANCE_IN_EVEN_ROW = 4; // Chance that the cell will be space in even row (out of 10)

// Constants of cell IDs
const int SPACE = 0; // ID of space
const int WALL = 1; // ID of wall
const int START = 2; // ID of start
const int TARGET = 3; // ID of target
const int GRAY_FROM_START = 4; // ID of gray from start
const int GRAY_FROM_TARGET = 5; // ID of gray from target
const int BLACK_FROM_START = 6; // ID of black from start
const int BLACK_FROM_TARGET = 7; // ID of black from target
const int PATH = 8; // ID of path

class Cell
{
private:
	int row;
	int col;
	int cellType;
	Cell* parent;

public:
	Cell();
	int getRow() { return row; }
	int getCol() { return col; }
	int getType() { return cellType; }
	Cell* getParent() { return parent; }
	void setRow(int r) { row = r; }
	void setCol(int c) { col = c; }
	void setType(int type) { cellType = type; }
	void setParent(Cell* p) { parent = p; }
	void setParameters(int row, int col, int type);
};