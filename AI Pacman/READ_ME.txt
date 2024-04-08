Summary:
The program simulates the Pacman game in an artificial intelligence version (the Pacman and the ghosts move independently)
Pacman and ghosts have a health amount (HP), when the amount of health reaches 0 the character "loses" (if the Pacman loses then the game stops and if the ghost loses it disappears).
During a fight, each character drops one HP point (if there are several ghosts around Pacman, he will drop the number of ghosts around him).

Goal:
The pacman has to collect all the coins and reach to the end point without losing.

Pacman progresses:
As long as the pacman has not collected all the coins he will look for a way to the closest coin to him (using the BFS algorithm).
If he met a ghost while scanning for a path to the coin,
He will test whether he can overcome her (enough life points),
If he can overcome it, he will continue to search for a way to the coin until he meets as many ghosts that he cannot overcome.
If he cannot overcome the ghosts he will run away in another random direction that is not in the direction of the spirits (if everything around him is walls then he will move in the direction of the ghosts).
Pacman will scan for coins until he collects them all, then he will try to reach to the end point in the same "search coin" way (will search for the end point instead of coin).

Ghosts progress:
The ghosts are looking for a way to Pacman (using algorithm *A).
If they meet Pacman, they fight against him.

Definitions:
You can define the amount of rows in the maze (MAZE_ROWS_SIZE), the amount of columns in the maze (MAZE_COLS_SIZE), 
the amount of coins (NUM_OF_COINS), waiting time between actions (MILLISECONDS_DELAY_BETWEEN_SET_OF_ACTIONS) 
in the program "Maze.h".

Options (by clicking on the right mouse in the maze screen):
Starting a game, starting a new maze, starting an existing maze.

Building the maze and presenting it:
The maze is built and presented using OpenGL.
The maze is automatically initialized to have path between the Pacman, the coins, the ghosts and the end point.

Colors in maze:
Pacman is marked in yellow.
Ghosts are marked in pink.
Coins are marked in gold.
End point is marked in red.
Wall is marked in black.
Free cell is marked in white.