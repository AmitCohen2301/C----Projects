#include "GhostActionWin.h"

void GhostActionWin::OnEnter(NPC_Ghost* pn) // On enter to ghost action win
{
	pn->setWinFlag(true);
}

void GhostActionWin::Transition(NPC_Ghost* pn) // Transition to another ghost action from ghost action win
{
	OnExit(pn); // Exiting ghost action win
	pn->setCurrentGhostAction(new GhostActionWin());
	pn->getCurrentGhostAction()->OnEnter(pn); // Entering new ghost action
}

void GhostActionWin::OnExit(NPC_Ghost* pn) // On exit from ghost action win
{
	pn->setWinFlag(false);
}