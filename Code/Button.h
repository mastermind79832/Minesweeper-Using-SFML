#pragma once

#include <SFML\Graphics.hpp>
using namespace sf;

class Button
{
private:
	std::string m_String;

	Font m_Font;
	Text m_Text;

	Color m_Default;
	Color m_HighLight;

public:
	//constructor and destructors
	Button();
	virtual ~Button();

	void Create(std::string str, Color color, float size);
	void SetPosition(float xPos, float yPos);
	
	// Mouse input
	void CheckForMouseHover(Vector2i mousePos);
	bool IsPressed(Vector2i mousePos);
	
	Vector2f getBounds();
	Vector2f getPosition();

	void Render(RenderWindow* window);
};

