#include "PacmanActionMoving.h"
#include "PacmanActionWin.h"
#include "PacmanActionFighting.h"
#include "PacmanActionSearchCoin.h"
#include "PacmanActionSearchTarget.h"

void PacmanActionMoving::OnEnter(NPC_Pacman* pn) // On enter to pacman action moving
{
	pn->setMovingFlag(true);
}

void PacmanActionMoving::Transition(NPC_Pacman* pn) // Transition to another pacman action from pacman action moving
{
	OnExit(pn); // Exiting pacman action moving
	if ((pn->getNumOfCollectedCoins() == NUM_OF_COINS) && (pn->getIfGetToTargetPoint())) // Win
		pn->setCurrentPacmanAction(new PacmanActionWin());
	else if (pn->getNumOfGhostsNearPacman() > 0) // Fight
		pn->setCurrentPacmanAction(new PacmanActionFighting());
	else if (pn->getNumOfCollectedCoins() < NUM_OF_COINS) // Search coin
		pn->setCurrentPacmanAction(new PacmanActionSearchCoin());
	else // Search target
		pn->setCurrentPacmanAction(new PacmanActionSearchTarget());
	pn->getCurrentPacmanAction()->OnEnter(pn); // Entering new pacman action
}

void PacmanActionMoving::OnExit(NPC_Pacman* pn) // On exit pacman action moving
{
	pn->setMovingFlag(false);
}