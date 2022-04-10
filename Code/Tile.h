#pragma once

#include <SFML\Graphics.hpp>
#include <sstream>
using namespace sf;

class Tile
{
private:
	RectangleShape m_Tile;
	bool b_IsBomb;
	bool b_IsBlasted;

	bool b_IsRevealed;
	bool b_IsMarked;

	int m_AdjacentCount;

	Color c_Outline;
	Color c_Default;
	Color c_Reveal;
	Color c_Blasted;
	Color c_Marked;

	Font m_Font;
	Text m_Number;
	CircleShape m_Bomb;

public:
	Tile();
	virtual ~Tile();

	void CreateTile(Vector2f pos, Vector2f size);
	
	void SetAdjacent(int count);
	int GetAdjacentCount();

	void SetBomb();
	bool IsBomb();

	int Mark();

	bool IsRevealed();
	bool Reveal(bool clicked);
	void Render(RenderWindow* window);
};

