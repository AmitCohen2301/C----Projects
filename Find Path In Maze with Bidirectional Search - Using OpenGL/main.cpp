#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "glut.h"
#include <queue>
#include "Cell.h"
#include <iostream>

using namespace std;

// Vars
Cell maze[MAZE_SIZE][MAZE_SIZE]; // Maze
bool runBFS = false; // Run BFS flag
bool restartMaze = false; // Restart maze flag
queue <Cell*> graysFromStart; // Queue of gray cells from start
queue <Cell*> graysFromTarget; // Queue of gray cells from target

void InitMaze() // Init the maze
{
	int rowNo, colNo;

	while (!graysFromStart.empty()) // Clear grays from start queue
		graysFromStart.pop();
	while (!graysFromTarget.empty()) // Clear grays from target queue
		graysFromTarget.pop();

	for (int i = 0; i < MAZE_SIZE; i++) // Init the frame to be walls
	{
		maze[0][i].setParameters(0, i, WALL); // First row
		maze[MAZE_SIZE - 1][i].setParameters(MAZE_SIZE - 1, i, WALL); // Last row
		maze[i][0].setParameters(i, 0, WALL); // First col
		maze[i][MAZE_SIZE - 1].setParameters(i, MAZE_SIZE - 1, WALL); // Last col
	}

	// Build the maze without the frame (if row is odd = so cell mostly need to be space, if row is even = so cell mostly need to be wall)
	for (rowNo = 1; rowNo < MAZE_SIZE - 1; rowNo++) // Move on every row (except first and last - that frame)
		for (colNo = 1; colNo < MAZE_SIZE - 1; colNo++) // Move on every col (except first and last - that frame)
		{
			if (rowNo % 2 == 1) // Row is odd
			{
				if (rand() % 10 < WALL_CHANCE_IN_ODD_ROW) // Cell need to be WALL
					maze[rowNo][colNo].setParameters(rowNo, colNo, WALL);
				else // Cell need to be SPACE
					maze[rowNo][colNo].setParameters(rowNo, colNo, SPACE);
			}
			else // Row is even
			{
				if (rand() % 10 < SPACE_CHANCE_IN_EVEN_ROW) // Cell need to be SPACE
					maze[rowNo][colNo].setParameters(rowNo, colNo, SPACE);
				else // Cell need to be WALL
					maze[rowNo][colNo].setParameters(rowNo, colNo, WALL);
			}
		}

	maze[MAZE_SIZE / 2][MAZE_SIZE / 2].setType(START); // Set the START cell (middle of the maze)
	int xTarget = (rand() % (MAZE_SIZE - 2)) + 1; // Range: between 1 to MAZE_SIZE-2 (In order the target not on frame)
	int yTarget = (rand() % (MAZE_SIZE - 2)) + 1; // Range: between 1 to MAZE_SIZE-2 (In order the target not on frame)
	maze[xTarget][yTarget].setType(TARGET); // Set the TARGET cell (random location)

	graysFromStart.push(&(maze[MAZE_SIZE / 2][MAZE_SIZE / 2])); // Insert start cell to grays from start
	graysFromTarget.push(&(maze[xTarget][yTarget])); // Insert target cell to grays from target

	restartMaze = false;
}

void init() // Init first time
{
	glClearColor(0.5, 0.5, 0.5, 0);// Set color of window background
	glOrtho(0, MAZE_SIZE, 0, MAZE_SIZE, -1, 1); // Set coordinates system
	srand(time(0)); // Init the random num
	InitMaze(); // Init the maze
}

void DrawMaze() // Draw the maze
{
	int rowNo, colNo;

	for (rowNo = 0; rowNo < MAZE_SIZE; rowNo++) // Move on every row
		for (colNo = 0; colNo < MAZE_SIZE; colNo++) // Move on every col
		{
			switch (maze[rowNo][colNo].getType()) // Check the cell type - to set the cell color
			{
			case SPACE:
				glColor3d(1, 1, 1); // white
				break;
			case WALL:
				glColor3d(0, 0, 0); // black
				break;
			case START:
				glColor3d(0.5, 0.5, 1); // blue
				break;
			case TARGET:
				glColor3d(1, 0, 0); // red
				break;
			case GRAY_FROM_START:
			case GRAY_FROM_TARGET:
				glColor3d(1, 0.7, 0); // orange
				break;
			case BLACK_FROM_START:
			case BLACK_FROM_TARGET:
				glColor3d(0.8, 1, 0.8); // green
				break;
			case PATH:
				glColor3d(1, 0, 1); // magenta
				break;
			}

			// Draw the cell
			glBegin(GL_POLYGON);
			glVertex2d(rowNo, colNo);
			glVertex2d(rowNo, colNo + 1);
			glVertex2d(rowNo + 1, colNo + 1);
			glVertex2d(rowNo + 1, colNo);
			glEnd();
		}
}

void RestorePath(Cell* pc) // Restore the path to start cell
{
	while (pc != nullptr) // Move on every cell until there is no "father" cell
	{
		int cellType = maze[pc->getRow()][pc->getCol()].getType();
		if ((cellType != START) && (cellType != TARGET)) // Change cell type to PATH, beside the START and TARGET cell
			maze[pc->getRow()][pc->getCol()].setType(PATH);
		pc = pc->getParent(); // Move to "father" cell
	}
}

bool HandleNeighbourThatSpaceOrBlackFromTargetOrTarget(int neighbourRow, int neighbourCol, Cell* pCurrent) // Handle neighbour that space or black from target or target
{
	int neighbourCellType = maze[neighbourRow][neighbourCol].getType();
	if ((neighbourCellType == TARGET) || (neighbourCellType == BLACK_FROM_TARGET)) // Neighbour is TARGET or BLACK_FROM_TARGET
	{
		runBFS = false; // Stop BFS
		RestorePath(pCurrent); // Restore path to start
		RestorePath(&(maze[neighbourRow][neighbourCol])); // Restore path to target
		return false; // No need to continue the BFS
	}
	else // Neighbour is SPACE
	{
		maze[neighbourRow][neighbourCol].setParent(pCurrent); // Set "father" to neighbour
		graysFromStart.push(&(maze[neighbourRow][neighbourCol])); // Add the neighbour cell to the grays from start
		maze[neighbourRow][neighbourCol].setType(GRAY_FROM_START); // Change neighbour cell type to GRAY_FROM_START
		return true; // Need to continue the BFS
	}
}

bool HandleNeighbourThatSpaceOrBlackFromStartOrStart(int neighbourRow, int neighbourCol, Cell* pCurrent) // Handle neighbour that space or black from start or start
{
	int neighbourCellType = maze[neighbourRow][neighbourCol].getType();
	if ((neighbourCellType == START) || (neighbourCellType == BLACK_FROM_START)) // Neighbour is START or BLACK_FROM_START
	{
		runBFS = false; // Stop BFS
		RestorePath(pCurrent); // Restore path to target
		RestorePath(&(maze[neighbourRow][neighbourCol])); // Restore path to start
		return false; // No need to continue the BFS
	}
	else // Neighbour is SPACE
	{
		maze[neighbourRow][neighbourCol].setParent(pCurrent); // Set "father" to neighbour
		graysFromTarget.push(&(maze[neighbourRow][neighbourCol])); // Add the neighbour cell to the grays from target
		maze[neighbourRow][neighbourCol].setType(GRAY_FROM_TARGET); // Change neighbour cell type to GRAY_FROM_TARGET
		return true; // Need to continue the BFS
	}
}

void RunBFSIteration() // Run BFS
{
	Cell* pc;
	int row, col;
	bool goOn = true;

	if (graysFromStart.empty() || graysFromTarget.empty()) // Failed to find PATH, because there is no cells to check
	{
		runBFS = false; // Stop BFS
		cout << "Grays are empty. There is no solution\n";
		return;
	}
	else // Continue to find path, because there are cells to check
	{
		// Pick the first cell from grays from start
		pc = graysFromStart.front();
		graysFromStart.pop();

		// Change cell type to BLACK_FROM_START, beside the START cell
		if (maze[pc->getRow()][pc->getCol()].getType() != START)
			maze[pc->getRow()][pc->getCol()].setType(BLACK_FROM_START);

		// Get row and col
		row = pc->getRow();
		col = pc->getCol();

		// Neighbours checks - if they are white add them to grays, if one of them is target then stop BFS		
		if (goOn && (maze[row + 1][col].getType() == SPACE || maze[row + 1][col].getType() == TARGET || maze[row + 1][col].getType() == BLACK_FROM_TARGET))// Upper neighbour
			goOn = HandleNeighbourThatSpaceOrBlackFromTargetOrTarget(row + 1, col, pc);
		if (goOn && (maze[row - 1][col].getType() == SPACE || maze[row - 1][col].getType() == TARGET || maze[row - 1][col].getType() == BLACK_FROM_TARGET)) // Lower neighbour
			goOn = HandleNeighbourThatSpaceOrBlackFromTargetOrTarget(row - 1, col, pc);
		if (goOn && (maze[row][col - 1].getType() == SPACE || maze[row][col - 1].getType() == TARGET || maze[row][col - 1].getType() == BLACK_FROM_TARGET)) // Left neighbour
			goOn = HandleNeighbourThatSpaceOrBlackFromTargetOrTarget(row, col - 1, pc);
		if (goOn && (maze[row][col + 1].getType() == SPACE || maze[row][col + 1].getType() == TARGET || maze[row][col + 1].getType() == BLACK_FROM_TARGET)) // Right neighbour
			goOn = HandleNeighbourThatSpaceOrBlackFromTargetOrTarget(row, col + 1, pc);

		// Pick the first cell from grays from target
		pc = graysFromTarget.front();
		graysFromTarget.pop();

		// Change cell type to BLACK_FROM_TARGET, beside the TARGET cell
		if (maze[pc->getRow()][pc->getCol()].getType() != TARGET)
			maze[pc->getRow()][pc->getCol()].setType(BLACK_FROM_TARGET);

		// Get row and col
		row = pc->getRow();
		col = pc->getCol();

		// Neighbours checks - if they are white add them to grays, if one of them is start then stop BFS		
		if (goOn && (maze[row + 1][col].getType() == SPACE || maze[row + 1][col].getType() == START || maze[row + 1][col].getType() == BLACK_FROM_START))// Upper neighbour
			goOn = HandleNeighbourThatSpaceOrBlackFromStartOrStart(row + 1, col, pc);
		if (goOn && (maze[row - 1][col].getType() == SPACE || maze[row - 1][col].getType() == START || maze[row - 1][col].getType() == BLACK_FROM_START)) // Lower neighbour
			goOn = HandleNeighbourThatSpaceOrBlackFromStartOrStart(row - 1, col, pc);
		if (goOn && (maze[row][col - 1].getType() == SPACE || maze[row][col - 1].getType() == START || maze[row][col - 1].getType() == BLACK_FROM_START)) // Left neighbour
			goOn = HandleNeighbourThatSpaceOrBlackFromStartOrStart(row, col - 1, pc);
		if (goOn && (maze[row][col + 1].getType() == SPACE || maze[row][col + 1].getType() == START || maze[row][col + 1].getType() == BLACK_FROM_START)) // Right neighbour
			goOn = HandleNeighbourThatSpaceOrBlackFromStartOrStart(row, col + 1, pc);
	}
}

void display() // Display drawings
{
	glClear(GL_COLOR_BUFFER_BIT); // Clean frame buffer with background color

	DrawMaze();

	glutSwapBuffers(); // Show all
}

void idle() // Idle the choice option
{
	if (runBFS) // BFS choice
		RunBFSIteration();
	if (restartMaze) // Restart maze
		InitMaze();

	glutPostRedisplay(); // Call to display indirectly
}

void menu(int choice) // Menu options
{
	if (choice == 1) // BFS
		runBFS = true;
	if (choice == 2) // Restart maze
		restartMaze = true;
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(750, 750);
	glutInitWindowPosition(400, 30);
	glutCreateWindow("BFS Example");

	glutDisplayFunc(display); // Refresh function
	glutIdleFunc(idle);  // Updates function

	// Menu
	glutCreateMenu(menu);
	glutAddMenuEntry("Run BFS", 1);
	glutAddMenuEntry("Restart Maze", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	init();

	glutMainLoop();
}