#include "MenuState.h"

//////////////////////////////
//Constructors
//////////////////////////////
MenuState::MenuState(sf::RenderWindow* target, std::stack<State*>* states)
	: State ( target, states )
{

	this->window = target;

	backgroundMat.loadFromFile("materials/parallax-space-backgound.png");
	planetMat.loadFromFile("materials/parallax-space-ring-planet.png");

	menuBackgroundSprite.setTexture(backgroundMat);
	menuBackgroundSprite.setScale(target->getView().getSize().x / menuBackgroundSprite.getLocalBounds().width, target->getView().getSize().y / menuBackgroundSprite.getLocalBounds().height);

	menuBackgroundPlanets.setTexture(planetMat);
	menuBackgroundPlanets.setScale(target->getView().getSize().x / menuBackgroundSprite.getLocalBounds().width, target->getView().getSize().y / menuBackgroundSprite.getLocalBounds().height);
	menuBackgroundPlanets.setPosition(target->getView().getSize().x / 2.f, menuBackgroundPlanets.getPosition().y / 2.f);

	this->menuBackground.setSize(sf::Vector2f(target->getSize().x, target->getSize().y));
	this->menuBackground.setFillColor(sf::Color(5, 5, 5, 200));


	this->InitButtons();

	if (!menuMusic.openFromFile("sound/music/title_loop.wav"))
	{
		std::cout << "Failed to load menu music" << "\n";
		system("pause");
	}

	menuMusic.setVolume(30.f);
	menuMusic.play();
	menuMusic.setLoop(true);
}


//////////////////////////////
//Destructor
//////////////////////////////
MenuState::~MenuState()
{
	menuMusic.stop();

	auto k = this->buttons.begin();
	for (k = this->buttons.begin(); k != this->buttons.end(); ++k)
	{
		delete k->second;
	}
}

//////////////////////////////
//Functions
//////////////////////////////
void MenuState::InitButtons()
{
	this->buttons["BUTTON_START_GAME"] = new Button(100, 150, 200, 50, "PLAY");
	this->buttons["BUTTON_EXIT_GAME"] = new Button(100, 230, 200, 50, "EXIT");
}

void MenuState::EndState()
{
	this->menuMusic.stop();
	std::cout << "Called end" << "\n";
}

void MenuState::Think(const float& dt)
{
	this->UpdateMouseCords();

	auto k = this->buttons.begin();
	for (k = this->buttons.begin(); k != this->buttons.end(); ++k)
	{
		k->second->Think(this->mousePosView);
	}

	if (this->buttons["BUTTON_START_GAME"]->isPressed())
	{
		this->EndState();
		this->states->push(new GameState(this->window, this->states));
	}

	if (this->buttons["BUTTON_EXIT_GAME"]->isPressed())
	{
		this->window->close();
	}

}

void MenuState::RenderThink(sf::RenderTarget* target)
{
	target->draw(menuBackgroundSprite);
	target->draw(menuBackgroundPlanets);
	target->draw(this->menuBackground);

	auto k = this->buttons.begin();
	for (k = this->buttons.begin(); k != this->buttons.end(); ++k)
	{
		k->second->RenderThink(target);
	}
}