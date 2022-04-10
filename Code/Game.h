#pragma once

#include "StateController.h"

class Game
{
private:
//Variables
	RenderWindow* p_Window;
	VideoMode m_ScreenSize;
	Color m_ScreenBgColor;

	StateController* m_Controller;

//Functions

	//Initializations
	void CreateWindow();

	//Update
	void UpdateEvents();
	void UpdateAll();

	//Render
	void RenderAll();

public:
	// Constructor and destructor
	Game();
	virtual ~Game();

	//game LOOP
	void Run();

};

