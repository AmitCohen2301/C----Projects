#pragma once

#include "NPC_Ghost.h"

class NPC_Ghost;

// Abstract class
class GhostAction
{
public:
	virtual void OnEnter(NPC_Ghost* pn) = 0; // On enter to that pacman action
	virtual void Transition(NPC_Ghost* pn) = 0; // Transition to another pacman action from that pacman action
	virtual void OnExit(NPC_Ghost* pn) = 0; // On exit from that pacman action
};