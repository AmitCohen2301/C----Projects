#pragma once

#include "GhostAction.h"
#include "NPC_Ghost.h"

class GhostActionWin : public GhostAction
{
	void OnEnter(NPC_Ghost* pn); // On enter to ghost action win
	void Transition(NPC_Ghost* pn); // Transition to another ghost action from ghost action win
	void OnExit(NPC_Ghost* pn); // On exit from ghost action win
};