#include "PacmanActionWin.h"

void PacmanActionWin::OnEnter(NPC_Pacman* pn) // On enter to pacman action win
{
	pn->setWinFlag(true);
}

void PacmanActionWin::Transition(NPC_Pacman* pn) // Transition to another pacman action from pacman action win
{
	OnExit(pn); // Exiting pacman action finish
	pn->setCurrentPacmanAction(new PacmanActionWin());
	pn->getCurrentPacmanAction()->OnEnter(pn); // Entering new pacman action
}

void PacmanActionWin::OnExit(NPC_Pacman* pn) // On exit from pacman action win
{
	pn->setWinFlag(false);
}