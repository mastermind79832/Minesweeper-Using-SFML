#pragma once

#include "PlayState.h"
#include "Button.h"

class MainMenuState :
    public State
{
private:
	std::string m_Title;
	std::string m_Declaration;

	Font m_Font;
	Text m_TitleText;
	Text m_DeclarationText;
	Color m_TextColor;

	//Play button
	Button btn_Play;
	//Quit Button
	Button btn_Quit;

	void SetUpText();

	//Control Input
	void CheckForMouseHover(Vector2i mousePos);
	void CheckForMouseClick(Vector2i mousePos);
	void MouseInput();

public:
	//Constructor / destructor
	MainMenuState(RenderWindow* window);
	virtual ~MainMenuState();

	//Overrride
	void MoveToNextState(std::stack<State*>* states);
	void Update();
	void Render();
};

