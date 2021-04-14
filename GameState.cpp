#include <iostream>
#include "GameState.h"
#include "math.h"

//////////////////////////////
//Constructors
//////////////////////////////
GameState::GameState(sf::RenderWindow* target, std::stack<State*>* states)
	: State(target, states)
{
	//this->InitWindow();
	this->window = target;
	this->InitVars();
	this->InitPlayer();
	this->InitNPC();
	this->score = 0.f;

	backgroundMat.loadFromFile("materials/parallax-space-backgound.png");
	background.setTexture(backgroundMat);

	planetMat.loadFromFile("materials/parallax-space-stars.png");
	stars.setTexture(planetMat);

	starMat.loadFromFile("materials/parallax-space-far-planets.png");
	planet.setTexture(starMat);

	NormalizeBackground();


	if (!gameMusic.openFromFile("sound/music/game_loop.wav"))
	{
		std::cout << "Failed to load gameplay music" << "\n";
		system("pause");
	}

	gameMusic.setVolume(40.f);
	gameMusic.play();
	gameMusic.setLoop(true);

	if (!font.loadFromFile("resource/all.ttf"))
	{
		std::cout << "Failed to load font file" << "\n";
		system("pause");
	}
	this->text.setFont(this->font);
	this->text.setString("Score: " + std::to_string(this->score));


}

//////////////////////////////
//Deconstructor
////////////////////////////
GameState::~GameState()
{
	this->gameMusic.stop();
	//delete this->window; -- crash?
}

//////////////////////////////
//Private functions
//////////////////////////////
void GameState::InitWindow()
{
	//this->window = nullptr;
	this->vm.width = WIN_W;
	this->vm.height = WIN_H;
	this->window = new sf::RenderWindow(this->vm, "Space Wars", sf::Style::Close); // | sf::Style::Resize
	this->window->setFramerateLimit(60);
}

void GameState::InitVars()
{
	this->vm.width = WIN_W;
	this->vm.height = WIN_H;

	this->score = 0;
	this->npc_spawnTimer = 0.0f;
	this->npc_nextSpawn = 100.f;
	this->max_npcs = 5;
}


void GameState::InitPlayer()
{
	this->ply = new Player(28.6f, 32.5f);
	this->ply->CenterPlayer();
}

void GameState::InitNPC()
{
	float scalingSpeed = 1.f;
	int scalingHP = 3;

	if (this->score < 100)
	{
		scalingHP = 6;
		scalingSpeed = 1.3f;
	}
	else if (this->score < 300)
	{
		scalingHP = 9;
		scalingSpeed = 1.8f;
	}
	else if (this->score < 500)
	{
		scalingHP = 12;
		scalingSpeed = 2.4f;
	}
	else if (this->score < 700)
	{
		scalingHP = 15;
		scalingSpeed = 2.6f;
	}
	else if (this->score < 1000)
	{
		scalingHP = 18;
		scalingSpeed = 2.9f;
	}
	else if (this->score >= 1000)
	{
		scalingHP = 21;
		scalingSpeed = 3.3f;
	}

	this->npc = new NPC(35.0f, 35.0f, scalingHP, scalingSpeed);
	this->npc->setPosition(WIN_W - 40, rand() % WIN_H);
	//this->npc->setFillColor(sf::Color::Red);
	//this->npc->setOutlineColor(sf::Color::Green);
	//this->npc->setOutlineThickness(2.0f);
	this->npcs.push_back(*this->npc);
}


//////////////////////////////
//Acccessors
//////////////////////////////
const bool GameState::EngineRunning()
{
	return this->window->isOpen();
}


//////////////////////////////
//Public Functions
//////////////////////////////

void GameState::AnimateBackground()
{
	stars.setPosition(stars.getPosition().x - starScrollSpeed, stars.getPosition().y);

	if (stars.getPosition().x < -750)
	{
		stars.setPosition(this->window->getView().getSize().x, stars.getPosition().y);

	}

	planet.setPosition(planet.getPosition().x - planetScrollSpeed, planet.getPosition().y);

	if (planet.getPosition().x < -750)
	{
		planet.setPosition(this->window->getView().getSize().x, planet.getPosition().y);

	}
}

void GameState::DrawObjects()
{

	for (auto& n : this->npcs) // Draw NPCS
	{
		this->window->draw(n);
	}

	for (auto p : this->projectiles) // Draw Projectiles
	{
		this->window->draw(*p);
	}

	this->window->draw(*this->ply); // Draw Player


	for (auto& sp : this->m_sprites)  //Draw animatedSprites above all
	{
		this->window->draw(sp);
	}

}

void GameState::UpdateMousePos()
{
	this->mousePos = sf::Vector2f(sf::Mouse::getPosition(*this->window));

	this->aimDirection = this->mousePos - this->ply->GetCenter();
	this->aimDirectionNorm = sf::Vector2f(this->aimDirection.x / sqrt(pow(this->aimDirection.x, 2) + pow(this->aimDirection.y, 2))
		, this->aimDirection.y / sqrt(pow(this->aimDirection.x, 2) + pow(this->aimDirection.y, 2)));

	//std::cout << std::endl << this->aimDirectionNorm.x << " " << this->aimDirectionNorm.x;
}

void GameState::DrawBG()
{
	this->window->draw(this->background);
	this->window->draw(this->planet);
	this->window->draw(this->stars);
	this->window->draw(this->text);
	AnimateBackground();
}

void GameState::NormalizeBackground()
{
	background.setScale(this->window->getView().getSize().x / background.getLocalBounds().width, this->window->getView().getSize().y / background.getLocalBounds().height);
	planet.setScale(this->window->getView().getSize().x / background.getLocalBounds().width, this->window->getView().getSize().y / background.getLocalBounds().height);
	stars.setScale(this->window->getView().getSize().x / background.getLocalBounds().width, this->window->getView().getSize().y / background.getLocalBounds().height);
}

sf::Sprite GameState::GetBackground()
{
	return background;
}

void GameState::Think(const float& dt)
{
	this->UpdateMousePos();
	this->PlayerThink();
	this->NPCThink();
	this->ProjectileThink();
	this->AnimatedSpriteThink();
}

void GameState::RenderThink(sf::RenderTarget* target)
{
	//this->window->clear();
	this->DrawBG();
	this->DrawObjects();
	//this->window->display();
}


void GameState::PlayerThink()
{
	this->ply->PlayerUpdate();
	this->ply->VerifyBounds(*this->window);

	if (this->ply->firedPrimary || this->ply->firedSecondary)
	{
		float orginX = this->ply->getPosition().x;
		float orginY = this->ply->getPosition().y;

		if (this->ply->firedPrimary || this->ply->firedSecondary)
		{
			int projectileSpeed = 15;
			float rot = this->ply->getRotation();
			SpawnProjectile(true, orginX, orginY, sf::Vector2f(this->aimDirectionNorm.x * projectileSpeed, this->aimDirectionNorm.y * projectileSpeed));
			
			this->ply->firedPrimary = false;
			this->ply->firedSecondary = false;
		}
	}
}

void GameState::SpawnProjectile(bool player, float x, float y, sf::Vector2f vel)
{
	if (player)
	{
		if (this->ply->currWepIndex == this->ply->primaryWeapon)
			this->projectile = new weapon_laser_repeater(this->window->getSize().x, 0, vel);
		else if (this->ply->currWepIndex == this->ply->altWeapon)
			this->projectile = new weapon_missile_dumbfire(this->window->getSize().x, 0, vel);

		this->projectile->setPosition(x, y);
		this->projectiles.push_back(this->projectile);
	}


}

void GameState::AddScore(int s)
{
	this->score += s;
	this->text.setString("Score: " + std::to_string(this->score));
}

void GameState::NPCThink()
{
	//NPC spawner logic
	if (this->npcs.size() < this->max_npcs)
		if (this->npc_spawnTimer >= this->npc_nextSpawn)
		{
			this->InitNPC();
			this->npc_spawnTimer = 0.0f;
		}
		else
		{
			this->npc_spawnTimer += 1.f;
		}

	//move towards player
	float infoX = this->ply->getPosition().x;
	float infoY = this->ply->getPosition().y;
	for (auto& n : this->npcs)
	{
		if (n.getPosition().x < infoX)
		{
			n.MoveTo(n.GetSpeed(), 0.f);
		}
		else if (n.getPosition().x > infoX)
		{
			n.MoveTo(n.GetSpeed() * -1, 0.f);
		}

		if (n.getPosition().y < infoY)
		{
			n.MoveTo(0.f, n.GetSpeed());
		}
		else if (n.getPosition().y > infoY)
		{
			n.MoveTo(0.f, n.GetSpeed() * -1);
		}
	}

}

void GameState::ResetGame()
{
	this->score = 0;
	this->AddScore(0);
	this->ply->setPosition(WIN_W / 2, WIN_H / 2);
	this->projectiles.clear();
	this->npcs.clear();
}

void GameState::ProjectileThink()
{
	//Call member function to move towards Vector2f coordinates
	for (auto p : this->projectiles)
	{
		p->MoveToTarget();
	}

	//Delete projectiles that are out of bounds
	for (int i = 0; i < this->projectiles.size(); i++)
	{
		if (this->projectiles[i]->canHurt && this->projectiles[i]->getGlobalBounds().intersects(this->ply->getGlobalBounds()))
		{
			this->ResetGame();
			break;
		}

		if (this->projectiles[i]->getPosition().x > this->window->getSize().x)
		{
			int fade = rand() % 2 + 1;

			if (fade == 2)
			{
				this->projectiles[i]->canHurt = true;
				if (this->projectiles[i]->getPosition().y > this->window->getView().getSize().y)
				{
					this->projectiles[i]->setPosition(this->projectiles[i]->getPosition().x, 0);
				}
				else if (this->projectiles[i]->getPosition().y < 0)
				{
					this->projectiles[i]->setPosition(this->projectiles[i]->getPosition().x, this->window->getView().getSize().y);
				}

				if (this->projectiles[i]->getPosition().x > this->window->getView().getSize().x)
				{
					this->projectiles[i]->setPosition(0, this->projectiles[i]->getPosition().y);
				}
				else if (this->projectiles[i]->getPosition().x < 0)
				{
					this->projectiles[i]->setPosition(this->window->getView().getSize().x, this->projectiles[i]->getPosition().y);
				}
			}
			else
			{
				this->projectiles.erase(this->projectiles.begin() + i);
				std::cout << "\nDeleted-->Projectile [out of bounds]";
				 i--; // or break;
				break;
			}
		}
		else
		{
			for (int ii = 0; ii < this->npcs.size(); ii++)  //Checks for collision
			{
				if (this->projectiles[i]->getGlobalBounds().intersects(npcs[ii].getGlobalBounds()))
				{

					this->projectiles[i]->OnDeath();
					npcs[ii].TakeDamage(this->projectiles[i]->GetDamage());
					this->projectiles.erase(this->projectiles.begin() + i);
		
					if (npcs[ii].GetHP() <= 0)
					{	
						this->m_sprite = new animatedSprite(npcs[ii].getPosition().x, npcs[ii].getPosition().y, 3.f, 2.5f);
						this->m_sprites.push_back(*this->m_sprite);
						this->npcs.erase(this->npcs.begin() + ii);
						this->AddScore(20);
						break;
					}
					break;
				}
			}
		}
	}
}

void GameState::AnimatedSpriteThink()
{
	//Call member function to move towards Vector2f coordinates
	for (int i = 0; i < this->m_sprites.size(); i++)
	{
		this->m_sprites[i].Think();

		if (this->m_sprites[i].shouldDelete)
		{
			this->m_sprites.erase(this->m_sprites.begin() + i);
			break;
		}
	}
}

void GameState::EndState()
{
	this->gameMusic.stop();
}