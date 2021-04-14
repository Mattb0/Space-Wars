#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> // For added flavor
#include <iostream>
#include <vector>
#include<stack>
#include <map>

#include "Definitions.h"

class State
{
private:
	//Variables
	sf::RenderWindow* window;
	std::vector<sf::Texture> textures;
	bool shouldExit;

	//Variables (accessible by inherited classes)
protected: 
	std::stack<State*>* states;
	sf::Vector2i mousePos;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

public:
	//Constructors
	State(sf::RenderWindow* window, std::stack<State*>* states);

	//Destructor
	virtual ~State();

	//Functions
	const bool& ShouldExit() const;
	void QuitThink();

	//Pure virtual functions
	virtual void UpdateMouseCords();
	virtual void EndState() = 0;
	virtual void Think(const float& dt) = 0;
	virtual void RenderThink(sf::RenderTarget* target = nullptr) = 0;
};