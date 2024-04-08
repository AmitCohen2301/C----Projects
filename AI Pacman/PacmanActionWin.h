#pragma once

#include "PacmanAction.h"
#include "NPC_Pacman.h"

class PacmanActionWin : public PacmanAction
{
	void OnEnter(NPC_Pacman* pn); // On enter to pacman action win
	void Transition(NPC_Pacman* pn); // Transition to another pacman action from pacman action win
	void OnExit(NPC_Pacman* pn); // On exit from pacman action win
};