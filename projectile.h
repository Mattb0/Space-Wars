#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

class Projectile : public sf::RectangleShape {

private:

	//Variables
	int damage = 4;
	float pWidth = 1.0f;
	float pHeight = 0.4f;
	float target_x = 0;
	float target_y = 0;
	float velocityModifier = 1.0f;
	sf::Vector2f velocity;
	sf::Color color = sf::Color::Red;
	sf::Texture skin;

public:
	bool canHurt = false;

	//Constructors
	Projectile();
	Projectile(float  x, float y, sf::Vector2f v); // Constructor calls the superclass to set the players dimensions

	//Getters
	virtual int GetDamage();

	//Funtions
	void MoveToTarget();
	virtual void Setup() {};
	virtual void OnDeath() {}
};

