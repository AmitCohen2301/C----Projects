#include "PacmanActionLose.h"

void PacmanActionLose::OnEnter(NPC_Pacman* pn) // On enter to pacman action lose
{
	pn->setLoseFlag(true);
}

void PacmanActionLose::Transition(NPC_Pacman* pn) // Transition to another pacman action from pacman action lose
{
	OnExit(pn); // Exiting pacman action lose
	pn->setCurrentPacmanAction(new PacmanActionLose()); // Lose
	pn->getCurrentPacmanAction()->OnEnter(pn); // Entering new pacman action
}

void PacmanActionLose::OnExit(NPC_Pacman* pn) // On exit from action lose
{
	pn->setLoseFlag(false);
}