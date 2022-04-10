#pragma once

#include <sstream>

#include "State.h"
#include "Button.h"
#include "Board.h"

class PlayState :
    public State
{
private:
	//Game Area
	Vector2f m_BorderOffset;
	RectangleShape m_GameArea;
	void CreateGameArea();

	Board m_Board;

	//Bomb
	int m_BombCount;
	Text m_BombText;
	void ResetBombs();
	void UpdateBomb();

	//Timer
	Clock m_Timer;
	Clock m_ClickTimer;
	int m_PlayTime;
	Font m_Font;
	Text m_TimeText;
	void ResetTime();
	void UpdateTime();

	//Buttons
	Button btn_Reset;
	Button btn_Share;
	void CreateButtons();
	void TakeScreenShot();
	
	//Game end
	Text m_VictoryText;
	void ResetVictory();
	void RePositionVictory();

	void ResetGame();
	void PlayGame(bool isLeftCLick , Vector2i mousePos);

	//Mouse
	bool m_IsGameStart;
	void CheckForMouseClick(Vector2i mousePos);
	void CheckForMouseHover(Vector2i mousePos);

	void CheckExitState();


public:
	PlayState(RenderWindow* window);
	virtual ~PlayState();

	void MoveToNextState(std::stack<State*>* states);
	void Update();
	void Render();
};

