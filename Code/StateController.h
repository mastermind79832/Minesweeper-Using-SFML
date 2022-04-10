#pragma once

#include "MainMenuState.h"

class StateController
{
private:
	//Variables
	std::stack<State*> s_States;

	//State managing functions
	void CheckForStateChange();

public:
	//Initialize
	StateController(RenderWindow* window);
	virtual ~StateController();

	// Update
	void Update();
	
	//Render
	void Render();
};

