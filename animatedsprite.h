#pragma once
#include <SFML\Graphics.hpp>
#include "laserBase.h"

/*
	A class used for creating animated sprites off tile sheets.
	Used for explosions
*/

class animatedSprite : public sf::Sprite
{

private:
	//Variables
	float duration;
	float nextFrame;
	sf::Texture texture1;
	sf::Texture texture2;
	sf::Clock time;
	sf::IntRect iRect;

public:
	//Public variables
	bool shouldDelete;

	//Constructors
	animatedSprite()
	{
		this->duration = 0.5f;
		this->nextFrame = 0.2f;
		this-> shouldDelete = false;
		this->texture1.loadFromFile("materials/sprites/exp_1.png");
		this->setTexture(texture1);
		this->setOrigin(this->getTexture()->getSize().x, this->getTexture()->getSize().y / 2);
	}

	animatedSprite(int x, int y, float sizeW, float sizeH)
	{
		this->duration = 0.4f;
		this->nextFrame = 0.2f;
		this->shouldDelete = false;
		this->setScale(sizeW, sizeH);
		shouldDelete = false;
		this->setPosition(x, y);
		this->texture1.loadFromFile("materials/sprites/exp_1.png");
		this->texture2.loadFromFile("materials/sprites/exp_2.png");
		this->setTexture(texture1);
		this->setOrigin(this->getTexture()->getSize().x / 2, this->getTexture()->getSize().y / 2);
	}

	//Functions
	void Think() 
	{
		if (this->time.getElapsedTime().asSeconds() > this->duration) 
		{
			shouldDelete = true;
		}
		else if (this->time.getElapsedTime().asSeconds() > this->nextFrame)
		{
			this->setTexture(texture2);
		}
	}

};