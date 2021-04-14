#pragma once
#pragma once
#include "State.h"
#include "Definitions.h"

#include "player.h"
#include "npc.h"
#include "projectile.h"
#include "animatedsprite.h"
#include "laserBase.h"
#include "weapon_laser_repeater.h"
#include "weapon_missile_dumbfire.h"


class GameState : public State {

private:

	//State Variables
	std::stack<State*> states;

	//Variables
	sf::Music gameMusic;
	sf::Vector2f mousePos;
	sf::Vector2f aimDirection;
	sf::Vector2f aimDirectionNorm;
	sf::Sprite stars;
	sf::Sprite planet;
	sf::Font font;
	sf::Text text;
	float starScrollSpeed = 0.3f;
	float planetScrollSpeed = 0.05f;
	
	//Game Variables
	int score;
	float npc_spawnTimer; // accumulated time
	float npc_nextSpawn; // target time
	float max_npcs; 

	//Private Functions
	void InitVars();
	void InitWindow();
	void InitPlayer();
	void InitNPC();
	void SpawnProjectile(bool player, float x, float y, sf::Vector2f v);

	//RenderWindow, Event, VideoMode, Player
	sf::RenderWindow* window;
	sf::Event evt;
	sf::VideoMode vm;

	//Objects
	Player* ply;
	NPC* npc;
	Projectile* projectile;
	animatedSprite* m_sprite;

	//Object vectors
	std::vector<NPC> npcs;
	std::vector<Projectile*> projectiles;
	std::vector<animatedSprite> m_sprites;


public:
	//Variables
	sf::Sprite background;
	sf::Texture backgroundMat;
	sf::Texture planetMat;
	sf::Texture starMat;

	//Constructors
	GameState(sf::RenderWindow* target, std::stack<State*>* states);

	//Destructor
	~GameState();
	sf::Sprite GetBackground();

	//Accessors
	const bool EngineRunning();

	//State Virtual functions
	void Think(const float& dt);
	void RenderThink(sf::RenderTarget* target = nullptr);

	//Functions
	void ResetGame();
	void PlayerThink();
	void NPCThink();
	void ProjectileThink();
	void AnimatedSpriteThink();
	void EndState();
	void UpdateMousePos();
	void AddScore(int s);

	//Draw Functions
	void DrawObjects();
	void DrawBG(); 	//Draws the background sprites. Ensure the non-static sprites coordinates loops upon exiting the window size
	void NormalizeBackground(); 	//Scales the background mat and sprites based on the window resolution
	void AnimateBackground(); 	//Animates the background sprites


};
