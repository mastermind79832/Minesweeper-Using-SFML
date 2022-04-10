#include "StateController.h"

//Initialize
StateController::StateController(RenderWindow* window)
{
	s_States.push(new MainMenuState(window));
}

StateController::~StateController()
{
//Empty the states
	while (!s_States.empty())
	{
		delete s_States.top();
		s_States.pop();
	}
}

//State managing functions
void StateController::CheckForStateChange()
{
	if (s_States.top()->IsNextState())
	{
		s_States.top()->ResetState();
		s_States.top()->MoveToNextState(&s_States);
	}
	else if (s_States.top()->IsQuitState())
	{
		delete s_States.top();
		s_States.pop();
	}
}

//Update
void StateController::Update()
{
	CheckForStateChange();
	if(!s_States.empty())
		s_States.top()->Update();
}

//Render
void StateController::Render()
{
	if (!s_States.empty())
		s_States.top()->Render();
}