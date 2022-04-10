#include "PlayState.h"

PlayState::PlayState(RenderWindow* window):
	State(window)
{
	std::cout << "Starting playstate\n";
	m_BorderOffset = Vector2f(20.f,20.f);
	m_IsGameStart = false;
	CreateGameArea();
	CreateButtons();
	ResetGame();
}

void PlayState::CreateGameArea()
{
	float screenWidth = p_Window->getSize().x;
	m_GameArea.setFillColor(Color(0,0,0,0));
	m_GameArea.setPosition(m_BorderOffset.x, m_BorderOffset.y);
	m_GameArea.setSize(Vector2f(
		screenWidth - m_BorderOffset.x*2 ,
		screenWidth - m_BorderOffset.x*2));
	m_GameArea.setOutlineThickness(3.f);
	m_GameArea.setOutlineColor(Color(120,120,120,225));
}

void PlayState::CreateButtons()
{
	btn_Reset.Create("RESET", Color(80, 80, 80, 255),40.f);
	btn_Share.Create("SHARE", Color(80, 80, 80, 255),40.f);

	float screenMid = p_Window->getSize().x/2;
	
	btn_Reset.SetPosition(
		screenMid - btn_Reset.getBounds().x - 20.f,
		p_Window->getSize().y - btn_Reset.getBounds().y - 30.f);

	btn_Share.SetPosition(
		screenMid + 10.f,
		p_Window->getSize().y - btn_Share.getBounds().y - 30.f);
}

void PlayState::ResetBombs()
{
	m_BombCount = 20;
	m_BombText.setFont(m_Font);
	m_BombText.setPosition(
		5* m_GameArea.getGlobalBounds().width/7,
		m_GameArea.getPosition().y + m_GameArea.getGlobalBounds().height + 20);
	UpdateBomb();
}

void PlayState::UpdateBomb()
{
	std::stringstream ss;
	ss << "BOMBS : ";
	ss << m_BombCount;
	m_BombText.setString(ss.str());
}

void PlayState::ResetTime()
{
	m_Font.loadFromFile("Fonts/MomcakeBold.otf");
	m_TimeText.setFont(m_Font);
	m_TimeText.setPosition(
		m_GameArea.getPosition().x,
		m_GameArea.getPosition().y + m_GameArea.getGlobalBounds().height + 20);
	m_TimeText.setString("TIME : 0");

	m_Timer.restart();
	m_PlayTime = 0;
}

void PlayState::ResetVictory()
{
	m_VictoryText.setFont(m_Font);
	m_VictoryText.setFillColor(Color::Green);
	m_VictoryText.setCharacterSize(100.f);
	m_VictoryText.setString("");
	RePositionVictory();
}

void PlayState::RePositionVictory()
{
	m_VictoryText.setPosition(
		(p_Window->getSize().x / 2.f) - (m_VictoryText.getGlobalBounds().width / 2),
		 btn_Reset.getPosition().y - m_VictoryText.getGlobalBounds().height - 50.f);
}

void PlayState::ResetGame()
{
	m_IsGameStart = false;
	ResetTime();
	ResetBombs();
	ResetVictory();

	m_Board.CreateNewBoard(m_GameArea, m_BombCount);
}

PlayState::~PlayState()
{
	std::cout << "Exiting playstate\n";
}

void PlayState::MoveToNextState(std::stack<State*>* states)
{
	return;
}

void PlayState::PlayGame(bool isLeftCLick, Vector2i mousePos)
{
	if (!m_IsGameStart && m_Timer.getElapsedTime().asSeconds() > 0.5f)
	{
		m_IsGameStart = true;
		m_Timer.restart();
	}

	if (isLeftCLick)
	{
		m_Board.PlayLeft(mousePos);
	}
	else
	{
		m_Board.PlayRight(mousePos);
	}
	
	if (m_Board.IsLoss())
	{
		m_IsGameStart = false;
		m_VictoryText.setString("LOSS");
		m_VictoryText.setFillColor(Color::Red);
		RePositionVictory();
	}
	else if (m_Board.IsVictory())
	{
		m_IsGameStart = false;
		m_VictoryText.setString("VICTORY");
		RePositionVictory();
	}
	
	m_BombCount = m_Board.GetRemainingBombs();
	UpdateBomb();
}

//Mouse
void PlayState::CheckForMouseClick(Vector2i mousePos)
{
	if (m_ClickTimer.getElapsedTime().asSeconds() < 0.2f)
		return;

	if (Mouse::isButtonPressed(Mouse::Left))
	{
		m_ClickTimer.restart();
		if (btn_Reset.IsPressed(mousePos))
		{
			ResetGame();
		}

		if (btn_Share.IsPressed(mousePos))
		{
			TakeScreenShot();
		}

		if (m_GameArea.getGlobalBounds().contains(mousePos.x,mousePos.y))
		{
			PlayGame(true, mousePos);
		}
	}

	if (Mouse::isButtonPressed(Mouse::Right))
	{
		m_ClickTimer.restart();
		PlayGame(false, mousePos);
	}
}

void PlayState::CheckForMouseHover(Vector2i mousePos)
{
	btn_Reset.CheckForMouseHover(mousePos);
	btn_Share.CheckForMouseHover(mousePos);
}

void PlayState::TakeScreenShot()
{
	Vector2u windowSize = p_Window->getSize();
	Texture texture;
	texture.create(windowSize.x, windowSize.y);
	texture.update(*p_Window);
	Image screenshot = texture.copyToImage();
	screenshot.saveToFile("ScreenShots/capture.png");
}

void PlayState::UpdateTime()
{
	if (!m_IsGameStart)
		return;
	
	if (m_Timer.getElapsedTime().asSeconds() > 1)
	{
		m_PlayTime += m_Timer.getElapsedTime().asSeconds();
		m_Timer.restart();
		
		std::stringstream ss;
		ss << "TIME : ";
		ss << m_PlayTime;
		m_TimeText.setString(ss.str());
	}
}

void PlayState::Update()
{
	CheckExitState();
	Vector2i mousePos = Mouse::getPosition(*p_Window);
	CheckForMouseHover(mousePos);
	CheckForMouseClick(mousePos);
	UpdateTime();
	//std::cout << "playstate\n";
}

void PlayState::CheckExitState()
{
	if (Keyboard::isKeyPressed(Keyboard::BackSpace))
	{
		m_QuitState = true;
	}
}

void PlayState::Render()
{
	//p_Window->draw(m_GameArea);
	m_Board.RenderBoard(p_Window);

	p_Window->draw(m_TimeText);
	p_Window->draw(m_BombText);
	p_Window->draw(m_VictoryText);
	
	btn_Reset.Render(p_Window);
	btn_Share.Render(p_Window);
}
