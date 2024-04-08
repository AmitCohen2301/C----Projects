#pragma once

#include "GhostAction.h"
#include "NPC_Ghost.h"

class GhostActionSearchPacman : public GhostAction
{
	void OnEnter(NPC_Ghost* pn); // On enter to ghost action search pacman
	void Transition(NPC_Ghost* pn); // Transition to another ghost action from ghost action search pacman
	void OnExit(NPC_Ghost* pn); // On exit from ghost action search pacman
};