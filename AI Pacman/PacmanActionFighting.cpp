#include "PacmanActionFighting.h"
#include "PacmanActionLose.h"
#include "PacmanActionSearchCoin.h"
#include "PacmanActionSearchTarget.h"

void PacmanActionFighting::OnEnter(NPC_Pacman* pn) // On enter to pacman action fighting
{
	pn->setFightingFlag(true);
}

void PacmanActionFighting::Transition(NPC_Pacman* pn) // Transition to another pacman action from pacman action fighting
{
	OnExit(pn); // Exiting pacman action fighting
	if (pn->getPacmanHP() <= 0) // Lose
		pn->setCurrentPacmanAction(new PacmanActionLose());
	else if (pn->getNumOfGhostsNearPacman() > 0) // Fight
		pn->setCurrentPacmanAction(new PacmanActionFighting());
	else if (pn->getNumOfCollectedCoins() < NUM_OF_COINS) // Search coin
		pn->setCurrentPacmanAction(new PacmanActionSearchCoin());
	else // Search target
		pn->setCurrentPacmanAction(new PacmanActionSearchTarget());
	pn->getCurrentPacmanAction()->OnEnter(pn); // Entering new pacman action
}

void PacmanActionFighting::OnExit(NPC_Pacman* pn) // On exit from action fighting
{
	pn->setFightingFlag(false);
}