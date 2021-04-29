#pragma once
#include <SFML\Graphics.hpp>
#include "weapon_laser_repeater.h"
#include "weapon_missile_dumbfire.h"

/*
	Player class derives from 'RectangleShape' to allow movement and all kinds of fun things from SFML lib
*/

class Player: public sf::RectangleShape {

	private:
		//Variables
		int health;
		int score;
		sf::Texture skin;

		//Fire rate variables
		int primaryWepCD = 0;				// Stores the concurrent cooldown
		int secondaryWepCD = 0;				
		const int primaryWepCDNext = 10;	// Constant rate of fire variable
		const int secondaryCDNext = 45;

		//Movement variables
		float currAcceleration = 0.f;
		float currAccelerationAdd = 0.05f;
		float maxAcceleration = 1.5f;
		float hSpeed			= 2.5f;
		float vSpeed			= 2.5f;

		// Private functions
		void MovePlayer(float x, float y);

	public: 
		//Fire rate variables
		bool firedPrimary = false;
		bool firedSecondary = false;

		//Stores player's loadout - All weapons derive from projectile
		int primaryWeapon;
		int altWeapon;
		int currWepIndex;

		//Constructors
		Player(float w, float h);

		// Functions
		void CenterPlayer();
		void PlayerUpdate(); // Updates Player objects coordinates and allows movement
		void VerifyBounds(sf::RenderWindow& window); //Verifies the Player object's position using 'RenderWindow' object's x & y bounds. 
		void FirePrimaryWeapon();
		void FireAltWeapon();

		// Setter functions
		void SetSkin();

		//Accessor functions
		sf::Vector2f GetCenter();
		int GetHealth();
		int GetScore();
		float HSpeed();
		float VSpeed();
		sf::Texture GetSkin();
};