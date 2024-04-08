#pragma once

#include "PacmanAction.h"
#include "NPC_Pacman.h"

class PacmanActionSearchCoin : public PacmanAction
{
	void OnEnter(NPC_Pacman* pn); // On enter to pacman action search coin
	void Transition(NPC_Pacman* pn); // Transition to another pacman action from pacman action search coin
	void OnExit(NPC_Pacman* pn); // On exit from pacman action search coin
};