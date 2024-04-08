#pragma once

#include "NPC_Pacman.h"

class NPC_Pacman;

// Abstract class
class PacmanAction
{
public:
	virtual void OnEnter(NPC_Pacman* pn) = 0; // On enter to that pacman action
	virtual void Transition(NPC_Pacman* pn) = 0; // Transition to another pacman action from that pacman action
	virtual void OnExit(NPC_Pacman* pn) = 0; // On exit from that pacman action
};