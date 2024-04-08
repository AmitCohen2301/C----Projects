#pragma once

#include "GhostAction.h"
#include "NPC_Ghost.h"

class GhostActionLose : public GhostAction
{
	void OnEnter(NPC_Ghost* pn); // On enter to ghost action lose
	void Transition(NPC_Ghost* pn); // Transition to another ghost action from ghost action lose
	void OnExit(NPC_Ghost* pn); // On exit from ghost action lose
};