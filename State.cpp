#include "State.h"

//////////////////////////////
//Constructor
//////////////////////////////
State::State(sf::RenderWindow* window, std::stack<State*>* states)
{
	this->states = states;
	this->window = window;
}

//////////////////////////////
//Destructor
//////////////////////////////
State::~State()
{

}

//////////////////////////////
//Functions
//////////////////////////////
void State::UpdateMouseCords()
{
	this->mousePos = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

const bool & State::ShouldExit() const
{
	return this->shouldExit;
}

void State::QuitThink()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		this->shouldExit = true;
	}
}

