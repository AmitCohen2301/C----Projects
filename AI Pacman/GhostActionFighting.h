#pragma once

#include "GhostAction.h"
#include "NPC_Ghost.h"

class GhostActionFighting : public GhostAction
{
	void OnEnter(NPC_Ghost* pn); // On enter to ghost action fighting
	void Transition(NPC_Ghost* pn); // Transition to another ghost action from ghost action fighting
	void OnExit(NPC_Ghost* pn); // On exit from ghost action fighting
};