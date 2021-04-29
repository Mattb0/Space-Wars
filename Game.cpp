#include "Game.h"

//////////////////////////////
//Constructors
//////////////////////////////
Game::Game()
{
	this->InitWindow();
	this->InitVars();
	this->InitStates();
}

//////////////////////////////
//Deconstructor
//////////////////////////////
Game::~Game()
{
	delete this->window;
	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

//////////////////////////////
//Private functions
//////////////////////////////
void Game::InitWindow()
{
	//this->window = nullptr;
	this->vm.width = WIN_W;
	this->vm.height = WIN_H;
	this->window = new sf::RenderWindow(this->vm, "Space Wars", sf::Style::Close); // | sf::Style::Resize
	this->window->setFramerateLimit(60);
}

void Game::InitVars()
{
	this->vm.width = WIN_W;
	this->vm.height = WIN_H;
}


void Game::InitStates()
{
	this->states.push(new MenuState(this->window, &this->states));
}

//////////////////////////////
//Functions
//////////////////////////////

void Game::Think()
{
	this->EventThink();

	if (!this->states.empty())
	{
		this->states.top()->Think(this->deltaTime);
	}
}

void Game::RenderThink()
{
	this->window->clear();

	if (!this->states.empty())
	{
		this->states.top()->RenderThink(this->window);
	}

	this->window->display();
}

void Game::EventThink()
{
	while (this->window->pollEvent(this->evt))
	{
		switch (this->evt.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::Resized:
			break;
		case sf::Event::KeyPressed:
			if (this->evt.key.code == sf::Keyboard::Escape)
			{
				this->states.top()->EndState();
				this->states.push(new MenuState(this->window, &this->states));
				//this->window->close();
			}
		}
	}
}

void Game::Run()
{
	while (this->window->isOpen())
	{
		this->UpdateDeltaTime();
		this->Think();
		this->RenderThink();
	}
}


void  Game::UpdateDeltaTime()
{
	this->deltaTime = this->deltaTimeClock.getElapsedTime().asSeconds();
}
