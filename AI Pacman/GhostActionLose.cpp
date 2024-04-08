#include "GhostActionLose.h"

void GhostActionLose::OnEnter(NPC_Ghost* pn) // On enter to ghost action lose
{
	pn->setLoseFlag(true);
}

void GhostActionLose::Transition(NPC_Ghost* pn) // Transition to another ghost action from ghost action lose
{
	OnExit(pn); // Exiting ghost action lose
	pn->setCurrentGhostAction(new GhostActionLose());
	pn->getCurrentGhostAction()->OnEnter(pn); // Entering new ghost action
}

void GhostActionLose::OnExit(NPC_Ghost* pn) // On exit from ghost action lose
{
	pn->setLoseFlag(false);
}