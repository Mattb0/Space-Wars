#include "projectile.h"
#include <SFML\Graphics.hpp>
#include <iostream>

/* 
	Base Projectile class for other projectiles to derive off
*/

//////////////////////////////
//Constructors
//////////////////////////////
Projectile::Projectile()
{
	std::cout << "copy constructor called";
	this->canHurt = false;
	this->damage = 1;
	this->pWidth = 1.0f;
	this->pHeight = 0.5f;
	this->target_x = 0;
	this->target_y = 0;
	this->velocity = sf::Vector2f(0, 0);
	this->color = sf::Color::Red;
}



Projectile::Projectile(float x, float y, sf::Vector2f v)
	: RectangleShape(sf::Vector2f(5.f, 2.5f))
{
	this->setRotation(90.f);
	this->target_x = x;
	this->target_y = y;

	this->velocity = v;
}


//////////////////////////////
//Getter Functions
//////////////////////////////

int Projectile::GetDamage()
{
	return this->damage;
}

//////////////////////////////
//Functions
//////////////////////////////

void Projectile::MoveToTarget()
{
	this->move(this->velocity.x * velocityModifier, this->velocity.y * velocityModifier);
}
