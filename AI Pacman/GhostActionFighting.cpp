#include "GhostActionFighting.h"
#include "GhostActionLose.h"
#include "GhostActionWin.h"

void GhostActionFighting::OnEnter(NPC_Ghost* pn) // On enter to ghost action fighting
{
	pn->setFightingFlag(true);
}

void GhostActionFighting::Transition(NPC_Ghost* pn) // Transition to another ghost action from ghost action fighting
{
	OnExit(pn); // Exiting ghost action fighting
	if (pn->getGhostHP() <= 0) // Lose
		pn->setCurrentGhostAction(new GhostActionLose());
	else if (pn->getIfIsPacmanNear()) // Fight
		pn->setCurrentGhostAction(new GhostActionFighting());
	else // Win
		pn->setCurrentGhostAction(new GhostActionWin());
	pn->getCurrentGhostAction()->OnEnter(pn); // Entering new ghost action
}

void GhostActionFighting::OnExit(NPC_Ghost* pn) // On exit ghost action fighting
{
	pn->setFightingFlag(false);
}