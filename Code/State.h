#pragma once

#include <iostream>
#include <stack>

#include <SFML\Graphics.hpp>

using namespace sf;

class State
{
protected:
	RenderWindow* p_Window;
	bool m_QuitState;
	bool m_NextState;

public:
	State(RenderWindow* window);
	virtual ~State();

	bool IsQuitState();
	bool IsNextState();
	void ResetState();

	virtual void MoveToNextState(std::stack<State*>* states) = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};

 