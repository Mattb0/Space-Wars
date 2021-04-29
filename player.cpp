#include <iostream>
#include "player.h"
#include "projectile.h"

float PLAYER_SIZE_W = 20.0;
float PLAYER_SIZE_H = 20.0;

//////////////////////////////
//Constructors
//////////////////////////////
Player::Player(float w, float h) 	// calls superclass constructor to set the players dimensions
	: RectangleShape(sf::Vector2f(w, h))
{
	this->health = 100;
	this->score = 0;
	this->SetSkin();
	std::cout << "\n" << "initialized player";

	this->primaryWeapon = 1;
	this->altWeapon = 2;
	this->currWepIndex = 0;
}

//////////////////////////////
//Deconstructor
//////////////////////////////

//////////////////////////////
//Private functions
//////////////////////////////
void Player::MovePlayer(float x, float y)
{

	if (this->currAcceleration < this->maxAcceleration)
	{
		currAcceleration += currAccelerationAdd;
	}

	this->move(x * currAcceleration, y * currAcceleration);

	std::cout << "\n" << currAcceleration;
}

//////////////////////////////
//Functions
//////////////////////////////


void Player::CenterPlayer()
{
	this->setOrigin(PLAYER_SIZE_W / 2, PLAYER_SIZE_H / 2);
}


sf::Vector2f Player::GetCenter()
{
	return sf::Vector2f(this->getPosition().x, this->getPosition().y);
}


void Player::PlayerUpdate()
{

	if (this->primaryWepCD > 0)
	{
		this->primaryWepCD -= 1;
	}
	if (this->secondaryWepCD > 0)
	{
		this->secondaryWepCD -= 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		this->FirePrimaryWeapon();
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
	{
		this->FireAltWeapon();
	}
	
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        this->MovePlayer(0.0f, this->VSpeed() * -1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
		this->MovePlayer(0.0f, this->VSpeed());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
		this->MovePlayer(this->HSpeed() * -1, 0.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
		this->MovePlayer(this->HSpeed() , 0.0f);
    }

	if (this->currAcceleration > 0)
	{
		this->currAcceleration -= currAccelerationAdd / 2;
	}
}

/*
	Verifies the Player object's position using 'RenderWindow' object's x & y bounds.
	If the Player object leaves the screen, object is moved to the opposite side of the screen similar to 'Space Wars'.
*/
void Player::VerifyBounds(sf::RenderWindow& window)
{
	if (this->getPosition().y > window.getView().getSize().y)
	{
		this->setPosition(this->getPosition().x, 0);
	}
	else if (this->getPosition().y < 0)
	{
		this->setPosition(this->getPosition().x, window.getView().getSize().y);
	}

	if (this->getPosition().x > window.getView().getSize().x)
	{
		this->setPosition(0, this->getPosition().y);
	}
	else if (this->getPosition().x < 0)
	{
		this->setPosition(window.getView().getSize().x, this->getPosition().y);
	}

}

void Player::FirePrimaryWeapon()
{									
	if (this->primaryWepCD <= 0)
	{
		this->firedPrimary = true;
		this->currWepIndex = this->primaryWeapon;
		this->primaryWepCD = this->primaryWepCDNext;
	}
}

void Player::FireAltWeapon()
{
	if (this->secondaryWepCD <= 0)
	{
		this->firedSecondary = true;
		this->currWepIndex = this->altWeapon;
		this->secondaryWepCD = this->secondaryCDNext;
	}
}

void Player::SetSkin()
{
	this->skin.loadFromFile("materials/nightraiderfixed.png");
	setTexture(&this->skin);
}

sf::Texture Player::GetSkin()
{
	return skin;
}

int Player::GetHealth()
{
	return health;
}

int Player::GetScore()
{
	return score;
}

float Player::HSpeed()
{
	return hSpeed;
}

float Player::VSpeed()
{
	return vSpeed;
}


