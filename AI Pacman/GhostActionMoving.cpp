#include "GhostActionMoving.h"
#include "GhostActionFighting.h"
#include "GhostActionSearchPacman.h"

void GhostActionMoving::OnEnter(NPC_Ghost* pn) // On enter to ghost action moving
{
	pn->setMovingFlag(true);
}

void GhostActionMoving::Transition(NPC_Ghost* pn) // Transition to another ghost action from ghost action moving
{
	OnExit(pn); // Exiting ghost action moving
	if (pn->getIfIsPacmanNear()) // Fight
		pn->setCurrentGhostAction(new GhostActionFighting());
	else // Search pacman
		pn->setCurrentGhostAction(new GhostActionSearchPacman());
	pn->getCurrentGhostAction()->OnEnter(pn); // Entering new ghost action
}

void GhostActionMoving::OnExit(NPC_Ghost* pn) // On exit ghost action moving
{
	pn->setMovingFlag(false);
}