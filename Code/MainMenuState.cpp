#include "MainMenuState.h"

//Constructor / destructor
MainMenuState::MainMenuState(RenderWindow* window):
	State(window)
{
	std::cout << "Starting MainMenu\n";

	m_Title = "MINESWEEPER";
	m_Declaration = "created by ADITYA AJITH";
	m_TextColor = Color(225, 225, 225, 225);
	SetUpText();
}

MainMenuState::~MainMenuState()
{
	std::cout << "Exiting MainMenu\n";
}

void MainMenuState::SetUpText()
{
	m_Font.loadFromFile("Fonts/MomcakeBold.otf");

	m_DeclarationText.setFont(m_Font);
	m_DeclarationText.setString(m_Declaration);
	m_DeclarationText.setFillColor(m_TextColor);
	m_DeclarationText.setCharacterSize(15);
	m_DeclarationText.setPosition(
		p_Window->getSize().x / 2.f - m_DeclarationText.getGlobalBounds().width / 2.f,
		p_Window->getSize().x / 3.f);

	m_TitleText.setFont(m_Font);
	m_TitleText.setString(m_Title);
	m_TitleText.setFillColor(m_TextColor);
	m_TitleText.setCharacterSize(80);
	m_TitleText.setPosition(
		p_Window->getSize().x / 2.f - m_TitleText.getGlobalBounds().width/2.f, 
		p_Window->getSize().x / 3.f);

	btn_Play.Create("PLAY", Color(80, 80, 80, 225), 40);
	btn_Play.SetPosition(
		p_Window->getSize().x / 2.f - btn_Play.getBounds().x / 2.f,
		m_TitleText.getPosition().y + p_Window->getSize().x / 3.f);

	btn_Quit.Create("QUIT", Color(80, 80, 80, 225), 40);
	btn_Quit.SetPosition(
		p_Window->getSize().x / 2.f - btn_Quit.getBounds().x / 2.f,
		btn_Play.getPosition().y + btn_Play.getBounds().y + 20.f);
}

//Control Input
void MainMenuState::CheckForMouseHover(Vector2i mousePos)
{
	//is mouse over button
	//activate button hover effect
	btn_Play.CheckForMouseHover(mousePos);
	btn_Quit.CheckForMouseHover(mousePos);
}

void MainMenuState::CheckForMouseClick(Vector2i mousePos)
{
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		//is mouse on play
		//m_NextState = true
		if (btn_Play.IsPressed(mousePos))
		{
			m_NextState = true;
		}
		//is mouse on Exit
		//m_QuitState = true 
		if (btn_Quit.IsPressed(mousePos))
		{
			m_QuitState = true;
			p_Window->close();
		}
	}
}

void MainMenuState::MouseInput()
{
	Vector2i mousePos = Mouse::getPosition(*p_Window);
	CheckForMouseHover(mousePos);
	CheckForMouseClick(mousePos);
}

//Overrride
void MainMenuState::MoveToNextState(std::stack<State*>* states)
{
	states->push(new PlayState(p_Window));
}

void MainMenuState::Update()
{
	//std::cout << "MainMenu\n";
	MouseInput();

	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		m_QuitState = true;
	}
}

void MainMenuState::Render()
{
	p_Window->draw(m_TitleText);
	btn_Play.Render(p_Window);
	btn_Quit.Render(p_Window);
	p_Window->draw(m_DeclarationText);
}
