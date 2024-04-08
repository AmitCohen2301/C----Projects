#pragma once

#include "PacmanAction.h"
#include "NPC_Pacman.h"

class PacmanActionLose : public PacmanAction
{
	void OnEnter(NPC_Pacman* pn); // On enter to pacman action lose
	void Transition(NPC_Pacman* pn); // Transition to another pacman action from pacman action lose
	void OnExit(NPC_Pacman* pn); // On exit from pacman action lose
};