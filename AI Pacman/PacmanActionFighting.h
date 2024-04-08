#pragma once

#include "PacmanAction.h"
#include "NPC_Pacman.h"

class PacmanActionFighting : public PacmanAction
{
	void OnEnter(NPC_Pacman* pn); // On enter to pacman action fighting
	void Transition(NPC_Pacman* pn); // Transition to another pacman action from pacman action fighting
	void OnExit(NPC_Pacman* pn); // On exit from pacman action fighting
};