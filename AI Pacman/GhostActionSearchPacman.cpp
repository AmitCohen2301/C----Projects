#include "GhostActionSearchPacman.h"
#include "GhostActionFighting.h"
#include "GhostActionMoving.h"

void GhostActionSearchPacman::OnEnter(NPC_Ghost* pn) // On enter to ghost action search pacman
{
	pn->setSearchPacmanFlag(true);
}

void GhostActionSearchPacman::Transition(NPC_Ghost* pn) // Transition to another ghost action from ghost action search pacman
{
	OnExit(pn); // Exiting ghost action search pacman
	if (pn->getGhostDircetionMove() == STAY) // Fight
		pn->setCurrentGhostAction(new GhostActionFighting());
	else // Move
		pn->setCurrentGhostAction(new GhostActionMoving());
	pn->getCurrentGhostAction()->OnEnter(pn); // Entering new ghost action
}

void GhostActionSearchPacman::OnExit(NPC_Ghost* pn) // On exit ghost action search pacman
{
	pn->setSearchPacmanFlag(false);
}