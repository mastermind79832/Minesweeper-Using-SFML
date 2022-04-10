#include "Button.h"

//constructor and destructors

Button::Button()
{
}

Button::~Button()
{
}

void Button::Create(std::string str, Color color, float size)
{
	m_Default = color;
	m_HighLight = Color(225, 225, 225, 225);

	m_Font.loadFromFile("Fonts/MomcakeBold.otf");
	m_Text.setFont(m_Font);
	m_Text.setString(str);
	m_Text.setCharacterSize(size);
	m_Text.setFillColor(m_Default);
}

void Button::SetPosition(float xPos, float yPos)
{
	m_Text.setPosition(xPos,yPos);
}

void Button::CheckForMouseHover(Vector2i mousePos)
{
	//is mouse over button
	//activate button hover effect
	if (m_Text.getGlobalBounds().contains(mousePos.x, mousePos.y))
	{
		m_Text.setFillColor(m_HighLight);
	}
	else
	{
		m_Text.setFillColor(m_Default);
	}
}

bool Button::IsPressed(Vector2i mousePos)
{
	if (m_Text.getGlobalBounds().contains(mousePos.x, mousePos.y))
	{
		m_Text.setFillColor(m_Default);
		return true;
	}
	return false;
}

Vector2f Button::getBounds()
{
	return Vector2f(m_Text.getGlobalBounds().width, m_Text.getGlobalBounds().height);
}

Vector2f Button::getPosition()
{
	return m_Text.getPosition();
}

void Button::Render(RenderWindow* window)
{
	window->draw(m_Text);
}
