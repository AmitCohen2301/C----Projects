#pragma once

#include "PacmanAction.h"
#include "NPC_Pacman.h"

class PacmanActionMoving : public PacmanAction
{
	void OnEnter(NPC_Pacman* pn); // On enter to pacman action moving
	void Transition(NPC_Pacman* pn); // Transition to another pacman action from pacman action moving
	void OnExit(NPC_Pacman* pn); // On exit from pacman action moving
};