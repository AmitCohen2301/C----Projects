#include "PacmanActionSearchTarget.h"
#include "PacmanActionFighting.h"
#include "PacmanActionMoving.h"

void PacmanActionSearchTarget::OnEnter(NPC_Pacman* pn) // On enter to pacman action search target
{
	pn->setSearchTargetFlag(true);
}

void PacmanActionSearchTarget::Transition(NPC_Pacman* pn) // Transition to another pacman action from pacman action search target
{
	OnExit(pn); // Exiting pacman action search target
	if (pn->getPacmanDircetionMove() == STAY) // Fight
		pn->setCurrentPacmanAction(new PacmanActionFighting());
	else // Move
		pn->setCurrentPacmanAction(new PacmanActionMoving());
	pn->getCurrentPacmanAction()->OnEnter(pn); // Entering new pacman action
}

void PacmanActionSearchTarget::OnExit(NPC_Pacman* pn) // On exit from pacman action search target
{
	pn->setSearchTargetFlag(false);
}