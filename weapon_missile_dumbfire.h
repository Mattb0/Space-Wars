#pragma once
#include <SFML\Graphics.hpp>
#include "missileBase.h"

class weapon_missile_dumbfire : public missileBase {

private:
	//variables
	float pWidth = 1.0f;
	float pHeight = 0.4f;
	float target_x = 0;
	float target_y = 0;
	sf::Vector2f velocity;
	sf::Color color = sf::Color::Red;
	sf::Texture skin;

public:
	int damage = 10;

	//Constructor
	weapon_missile_dumbfire(float x, float y, sf::Vector2f v)
		: missileBase(x,y,v)
	{
	}


};

