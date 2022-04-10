#include "Tile.h"

Tile::Tile()
{
	c_Outline = Color(100, 100, 100, 255);
	c_Default = Color(150, 150, 150, 255);
	c_Reveal = Color(50, 50, 50, 255);
	c_Blasted = Color(200, 0, 0, 255);
	c_Marked = Color( 0, 200, 0, 255);

	m_AdjacentCount = 0;
	
	b_IsBomb = false;
	b_IsBlasted = false;
	
	b_IsRevealed = false;
	b_IsMarked = false;

	m_Number.setString("");
}

Tile::~Tile()
{
}

void Tile::CreateTile(Vector2f pos, Vector2f size)
{
	m_Tile.setPosition(pos);
	m_Tile.setSize(size);
	m_Tile.setFillColor(c_Default);
	m_Tile.setOutlineColor(c_Outline);
	m_Tile.setOutlineThickness(3.f);
}

void Tile::SetAdjacent(int count)
{
	m_AdjacentCount = count;
	std::stringstream ss;
	ss << m_AdjacentCount;
	m_Number.setString(ss.str());

	m_Font.loadFromFile("Fonts/MomcakeBold.otf");
	m_Number.setFont(m_Font);
	m_Number.setFillColor(Color::White);
	m_Number.setPosition(Vector2f(
		m_Tile.getPosition().x + m_Tile.getSize().x/3,
		m_Tile.getPosition().y));

}

void Tile::SetBomb()
{
	b_IsBomb = true;
	m_Bomb.setFillColor(Color::White);
	m_Bomb.setRadius(m_Tile.getSize().x / 4);
	m_Bomb.setPosition(m_Tile.getPosition() + Vector2f(10.f,10.f));
}

bool Tile::IsBomb()
{
	return b_IsBomb;
}

int Tile::Mark()
{
	if (b_IsRevealed)
		return -1;

	b_IsMarked = !b_IsMarked;
	if (b_IsMarked)
		m_Tile.setFillColor(c_Marked);
	else
		m_Tile.setFillColor(c_Default);

	return b_IsMarked;
}

bool Tile::IsRevealed()
{
	return b_IsRevealed;
}

bool Tile::Reveal(bool clicked)
{
	if (b_IsRevealed || b_IsMarked)
		return false;

	b_IsRevealed = true;
	m_Tile.setFillColor(c_Reveal);

	if (b_IsBomb && clicked)
	{
		b_IsBlasted = true;
		m_Tile.setFillColor(c_Blasted);
	}

	return true;
}

int Tile::GetAdjacentCount()
{
	return m_AdjacentCount;
}

void Tile::Render(RenderWindow* window)
{
	window->draw(m_Tile);
	if (b_IsRevealed)
	{
		if (b_IsBomb)
		{
			window->draw(m_Bomb);
		}
		else if (m_AdjacentCount > 0)
		{
			window->draw(m_Number);
		}
	}
}
