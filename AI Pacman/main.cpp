#include <iostream> 
#include <time.h>
#include "glut.h"
#include "Maze.h"

using namespace std;

// Constants
const int WIDTH = 750;
const int HEIGHT = 750;

Maze theMaze;

void init() // Init first time
{
	glClearColor(0.5, 0.5, 0.5, 0); // Set color of window background
	glOrtho(0, MAZE_COLS_SIZE, MAZE_ROWS_SIZE, 0, 1, -1); // Set coordinates system
	srand(time(0)); // Init the random
	theMaze.initNewMaze(); // Init the maze
}

void display() // Display drawings
{
	glClear(GL_COLOR_BUFFER_BIT); // Clean frame buffer with background color

	theMaze.drawMaze(); // Draw maze

	glutSwapBuffers(); // Show all
}

void idle() // Idle the choice option
{
	if (theMaze.getRunPacmanFlag()) // Run pacman choice
		theMaze.runPacman();
	if (theMaze.getRestartMazeFlag()) // Restart maze (new maze)
		theMaze.initNewMaze();
	if (theMaze.getRestartSameMazeFlag()) // Restart maze (same maze)
		theMaze.initSameMaze();

	glutPostRedisplay(); // Call to display indirectly
}

void menu(int choice) // Menu options
{
	if (choice == 1) // Run pacman
		theMaze.setRunPacmanFlag(true);
	if (choice == 2) // Restart maze (new maze)
		theMaze.setRestartMazeFlag(true);
	if (choice == 3) // Restart maze (same maze)
		theMaze.setRestartSameMazeFlag(true);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(400, 30);
	glutCreateWindow("BestFirstSearch & A* Example");

	glutDisplayFunc(display); // Refresh function
	glutIdleFunc(idle);  // Updates function

	// Menu
	glutCreateMenu(menu);
	glutAddMenuEntry("Run pacman", 1);
	glutAddMenuEntry("Restart Maze (new maze)", 2);
	glutAddMenuEntry("Restart Maze (same maze)", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	init();
	
	glutMainLoop();
}