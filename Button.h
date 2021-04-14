#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>

enum button_states
{
	BUTTON_IDLE = 0,
	BUTTON_HOVER = 1,
	BUTTON_PRESSED = 2
};

class Button
{
private:
	//Variables
	short unsigned buttonState;

	sf::RectangleShape buttonShape;
	sf::Font font;
	sf::Text text;
	sf::Color color;
	sf::Color hoverColor;
	sf::Color clickColor; 

public:
	//Constructors
	Button(float x, float y, float w, float h, std::string text);

	//Destructor
	~Button();

	//Accessors
	const bool isPressed();

	//Functions
	void Think(const sf::Vector2f cordinates);
	void RenderThink(sf::RenderTarget* target);

};

