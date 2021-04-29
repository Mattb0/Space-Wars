#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "projectile.h"
#include <iostream>

class laserBase : public Projectile {

private:
	//variables
	int damage;
	float pWidth = 1.0f;
	float pHeight = 0.4f;
	float target_x = 0;
	float target_y = 0;

	sf::SoundBuffer soundImpact;
	sf::SoundBuffer soundLaser;
	sf::Sound sfx;

	sf::Vector2f velocity;
	sf::Color color = sf::Color::Red;
	sf::Texture skin;

public:
	//Constructors
	laserBase(){}

	//Destructor
	~laserBase()
	{

	}

	laserBase(float x, float y, sf::Vector2f v)
		: Projectile(x, y, v)
	{
		soundImpact.loadFromFile("sound/sfx/target_hit.wav");
		soundLaser.loadFromFile("sound/sfx/pl_gun2.wav");
		sfx.setBuffer(soundLaser);
		sfx.play();

		this->setScale(1.f, 5.f);
		this->skin.loadFromFile("materials/sprites/laser.png");
		this->setTexture(&this->skin);
	}

	//Functions	                                        
	void OnDeath()
	{
		sfx.setBuffer(soundImpact);
		sfx.play();
	}

};


