#pragma once
#include <SFML\Graphics.hpp>

class NPC : public sf::RectangleShape {

private:
	//Variables
	int health = 0;
	float maxSpeed = 0.9f;
	float sizeW = 0.5f;
	float sizeH = 0.5f;
	bool hostile = true;
	sf::Texture skin;

public:

	//Constructors
	NPC();
	NPC(float w, float h, int hp, float speed);

	//Deconstructor
	~NPC();

	//Accessors
	int GetHP();
	float GetSpeed();

	// Setters 
	void SetSkin();

	//Functions
	void TakeDamage(int damage);
	void CenterNPC();
	void MoveTo(float x, float y);
	void Shoot(float x, float y);


};