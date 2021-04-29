#pragma once
#include <SFML\Graphics.hpp>
#include "laserBase.h"

class weapon_laser_repeater : public laserBase {

private:
	//Variables
	float velocityModifier = 2.0f;

	sf::Vector2f velocity;
	sf::Color color = sf::Color::Red;
	sf::Texture skin;

public:
	int damage = 3;

	//Constructor
	weapon_laser_repeater()
	{
	}

	weapon_laser_repeater(float x, float y, sf::Vector2f v)
		: laserBase(x, y, v)
	{

	}


};

