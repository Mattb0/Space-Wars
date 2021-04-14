#include <iostream>
#include "npc.h"

//////////////////////////////
//Constructors
//////////////////////////////
NPC::NPC(){}

NPC::NPC(float w, float h, int hp, float speed)
	: RectangleShape(sf::Vector2f(w, h))
{
	this->health = hp;
	this->sizeW = w;
	this->sizeH = h;
	this->maxSpeed = speed;
	this->hostile = true;
	this->CenterNPC();
	this->SetSkin();
}
//////////////////////////////
//Deconstructor
//////////////////////////////

NPC::~NPC()
{
}


//////////////////////////////
//Getter functions
//////////////////////////////
int  NPC::GetHP()
{
	return this->health;
}

float  NPC::GetSpeed()
{
	return this->maxSpeed;
}


//////////////////////////////
//Functions
//////////////////////////////
void NPC::CenterNPC()
{
	this->setOrigin(this->sizeW / 2, this->sizeW / 2);
}
 
void NPC::TakeDamage(int damage)
{
	this->health -= damage;
}

void NPC::MoveTo(float x, float y)
{
	this->move(x,y);
}

void NPC::Shoot(float x, float y)
{

}


void NPC::SetSkin()
{
	int i = rand() % 3 + 1;
	skin;
	this->setRotation(-90);

	std::cout << i;
	if (i <= 1)
	{
		skin.loadFromFile("materials/sprites/fighter3.png");
	}
	else if (i <= 2)
	{
		skin.loadFromFile("materials/sprites/fighter2.png");
	}
	else if (i <= 3)
	{
		skin.loadFromFile("materials/sprites/fighter2.png");
	}
	setTexture(&skin);
}
