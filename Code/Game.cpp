#include "Game.h"

//Initializations
void Game::CreateWindow()
{
	p_Window = new RenderWindow(m_ScreenSize,"MINESWEEPER");
	p_Window->setFramerateLimit(30);
}

//Update
void Game::UpdateEvents()
{
	Event e;
	while (p_Window->pollEvent(e))
	{
		if (e.type == Event::Closed ||
			Keyboard::isKeyPressed(Keyboard::Escape))
		{
			p_Window->close();
		}
	}
}

void Game::UpdateAll()
{
	UpdateEvents();
	m_Controller->Update();
}

//Render
void Game::RenderAll()
{
	p_Window->clear(m_ScreenBgColor);

	//All draws here
	m_Controller->Render();

	p_Window->display();
}

// Constructor and destructor
Game::Game()
{
	m_ScreenBgColor = Color(20, 20, 20, 225);

	m_ScreenSize.width = 600;
	m_ScreenSize.height = 800;

	CreateWindow();

	m_Controller = new StateController(p_Window);
}

Game::~Game()
{
	delete p_Window;
	delete m_Controller;
}

//game LOOP
void Game::Run()
{
	while (p_Window->isOpen())
	{
		UpdateAll();
		RenderAll();
	}
}
