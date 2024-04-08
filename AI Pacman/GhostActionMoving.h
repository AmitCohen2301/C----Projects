#pragma once

#include "GhostAction.h"
#include "NPC_Ghost.h"

class GhostActionMoving : public GhostAction
{
	void OnEnter(NPC_Ghost* pn); // On enter to ghost action moving
	void Transition(NPC_Ghost* pn); // Transition to another ghost action from ghost action moving
	void OnExit(NPC_Ghost* pn); // On exit from ghost action moving
};