#include "State.h"

State::State(RenderWindow* window)
{
	p_Window = window;
	ResetState();
}

State::~State()
{
}

bool State::IsQuitState()
{
	return m_QuitState;
}

bool State::IsNextState()
{
	return m_NextState;
}

void State::ResetState()
{
	m_QuitState = false;
	m_NextState = false;
}
