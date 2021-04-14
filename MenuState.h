#pragma once
#include "State.h"
#include "Button.h"
#include "GameState.h"

class MenuState : public State
{
private:
	//Variables
	sf::Music menuMusic;
	sf::RectangleShape menuBackground;
	sf::Sprite menuBackgroundSprite;
	sf::Sprite menuBackgroundPlanets;
	std::map<std::string, Button*> buttons;
	sf::RenderWindow* window;

	//Texture Variables
	sf::Texture backgroundMat;
	sf::Texture planetMat;

	//Mouse Variables
	sf::Vector2f mousePos;
	sf::Vector2f aimDirection;
	sf::Vector2f aimDirectionNorm;

	//Button Variables
	Button* button_play;
	Button* button_exit;

public:
	//Constructor
	MenuState(sf::RenderWindow* target, std::stack<State*>* states);

	//Deconstructor
	~MenuState();

	//Functions
	void InitButtons();

	//State:: pure virtual functions
	void EndState();
	void Think(const float& dt);
	void RenderThink(sf::RenderTarget* target = nullptr);

};






