#include "PacmanActionSearchCoin.h"
#include "PacmanActionFighting.h"
#include "PacmanActionMoving.h"

void PacmanActionSearchCoin::OnEnter(NPC_Pacman* pn) // On enter to pacman action search coin
{
	pn->setSearchCoinFlag(true);
}

void PacmanActionSearchCoin::Transition(NPC_Pacman* pn) // Transition to another pacman action from pacman action search coin
{
	OnExit(pn); // Exiting pacman action search coin
	if (pn->getPacmanDircetionMove() == STAY) // Fight
		pn->setCurrentPacmanAction(new PacmanActionFighting());
	else // Move
		pn->setCurrentPacmanAction(new PacmanActionMoving());
	pn->getCurrentPacmanAction()->OnEnter(pn); // Entering new pacman action
}

void PacmanActionSearchCoin::OnExit(NPC_Pacman* pn) // On exit pacman action search coin
{
	pn->setSearchCoinFlag(false);
}