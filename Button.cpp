#include "Button.h"

//////////////////////////////
//Constructors
//////////////////////////////
Button::Button(float x, float y, float w, float h, std::string text)
{
	if (!font.loadFromFile("resource/all.ttf"))
	{
		std::cout << "Failed to load font file" << "\n";
		system("pause");
	}

	this->text.setFont(this->font);

	this->buttonState = 0;
	this->buttonShape.setSize(sf::Vector2f(w, h));
	this->buttonShape.setPosition(sf::Vector2f(x, y));
	this->text.setString(text);

	this->color = sf::Color(35, 35, 35, 100);
	this->hoverColor = sf::Color(65, 65, 65, 200);
	this->clickColor = sf::Color(255, 0, 0, 50);

	this->text.setFillColor(sf::Color::Cyan);
	this->text.setPosition(
		this->buttonShape.getPosition().x + (this->buttonShape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 1.5f,
		this->buttonShape.getPosition().y + (this->buttonShape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 1.5f
	);
}

//////////////////////////////
//Deconstructor
//////////////////////////////
Button::~Button()
{

}

//////////////////////////////
//Accessors
//////////////////////////////
const bool Button::isPressed()
{
	if (this->buttonState == BUTTON_PRESSED)
	{
		return true;
	}
	return false;
}


//////////////////////////////
//Functions
//////////////////////////////
void Button::Think(const sf::Vector2f cordinates)
{
	if (this->buttonShape.getGlobalBounds().contains(cordinates))
	{
		this->buttonState = BUTTON_HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BUTTON_PRESSED;
		}
	}
	else
	{
		this->buttonState = BUTTON_IDLE;
	}

	switch (this->buttonState)
	{
		case BUTTON_IDLE:
			this->buttonShape.setFillColor(this->color);
			break;
		case BUTTON_HOVER:
			this->buttonShape.setFillColor(this->hoverColor);
			break;
		case BUTTON_PRESSED:
			this->buttonShape.setFillColor(this->clickColor);
			break;
	}
}

void Button::RenderThink(sf::RenderTarget* target)
{
	target->draw(this->buttonShape);
	target->draw(this->text);

}