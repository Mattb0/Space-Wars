#pragma once
#include "GameState.h"
#include "MenuState.h"

class Game
{
private:
	//Variables
	float deltaTime;
	sf::Clock deltaTimeClock;

	//State Variables
	std::stack<State*> states;

	//RenderWindow, Event, VideoMode, Player
	sf::RenderWindow* window;
	sf::Event evt;
	sf::VideoMode vm;

	//Init functions
	void InitVars();
	void InitWindow();
	void InitStates();

public:
	//Constructors
	Game();

	//Destructor 
	virtual ~Game();

	//Functions
	void EventThink();
	void Think();
	void RenderThink();
	void Run();
	void UpdateDeltaTime();


};

