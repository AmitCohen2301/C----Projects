#pragma once

#include "PacmanAction.h"
#include "NPC_Pacman.h"

class PacmanActionSearchTarget : public PacmanAction
{
	void OnEnter(NPC_Pacman* pn); // On enter to pacman action search target
	void Transition(NPC_Pacman* pn); // Transition to another pacman action from pacman action search target
	void OnExit(NPC_Pacman* pn); // On exit from pacman action search target
};