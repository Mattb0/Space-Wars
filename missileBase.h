#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "projectile.h"

class missileBase : public Projectile {

private:
	//Variables
	int damage = 1;
	float pWidth = 1.0f;
	float pHeight = 0.4f;
	float target_x = 0;
	float target_y = 0;

	sf::SoundBuffer soundExplosion;
	sf::SoundBuffer soundLoop;
	sf::Sound sfx;

	sf::Vector2f velocity;
	sf::Color color = sf::Color::Red;
	sf::Texture skin;

public:
	//Constructor
	missileBase(float x, float y, sf::Vector2f v)
		: Projectile(x, y, v)
	{
		soundExplosion.loadFromFile("sound/sfx/explode1.wav");
		soundLoop.loadFromFile("sound/sfx/rocketfire1.wav");
		sfx.setBuffer(soundLoop);
		sfx.play();

		this->setScale(1.1f, 8.f);
		this->skin.loadFromFile("materials/sprites/torpedo1.png");
		this->setTexture(&this->skin);
	}

	//Destructor
	~missileBase()
	{
		delete& sfx;
		delete& soundExplosion;
		delete& soundLoop;
	}

	//Functions	
	void OnDeath()
	{
		sfx.setBuffer(soundExplosion);
		sfx.play();
	}

};

