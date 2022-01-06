#include "Utility/Game.h"
#include "Platform/Platform.hpp"

util::Platform platform;

//private
void Game::initVariables()
{
	this->window = nullptr;

	this->points = 0;

	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 10;

	this->playerHealth = 5;

	this->endgame = false;
}

void Game::initWindow()
{
	this->videomode.height = 400;
	this->videomode.width = 800;
	this->window = new sf::RenderWindow(this->videomode, "Task cruncher", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::initEnemies()
{
	this->enemy.setPosition(10.f, 10.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setFillColor(sf::Color::Cyan);
	this->enemy.setOutlineColor(sf::Color::Blue);
	this->enemy.setOutlineThickness(1.f);
}

//Constructors  and Destructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initEnemies();
	this->initFont();
	this->initText();
}

Game::~Game()
{
	delete this->window;
}

//accessors
bool Game::running()
{
	return this->window->isOpen();
}

//functions

void Game::updateMousePos()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::pollEvents()
{
	//event polling
	while (this->window->pollEvent(event))
	{
		switch (this->event.type)
		{
			default:
				break;
			case sf::Event::Closed:
				this->window->close();
				break;
			case sf::Event::KeyPressed:
				if (this->event.key.code == sf::Keyboard::Escape)
					this->window->close();
				break;
		}
	}
}

void Game::spawnEnemies()
{
	float x = static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x));
	this->enemy.setPosition(x, 0.f);

	this->enemy.setFillColor(sf::Color::Blue);

	this->enemies.push_back(this->enemy);
}

void Game::updateEnemies()
{
	// atualiza o tempo de spawn e spawna inimigos.

	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			this->spawnEnemies();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}

	//movimentar os inimigos
	for (unsigned int i = 0; i < this->enemies.size(); i++)
	{
		bool deleted = false;
		this->enemies[i].move(0.f, 1.f);

		//check if clicked
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
			{
				this->enemies.erase(this->enemies.begin() + i);
			}
		}

		//if the enemy is in the button
		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->playerHealth -= 1;
			deleted = true;
		}

		if (deleted)
			this->enemies.erase(this->enemies.begin() + i);
	}
}

void Game::renderEnemies(sf::RenderTarget& target)
{
	for (auto& e : this->enemies)
	{
		target.draw(e);
	}
}

void Game::update()
{
	this->pollEvents();

	if (this->endgame == false)
	{
		this->updateMousePos();

		this->updateEnemies();
	}

	//endgame condititon
	if (this->playerHealth <= 0)
		this->endgame = true;
}

void Game::render()
{

	this->window->clear();

	this->renderEnemies(*this->window);
	this->renderText(*this->window);

	this->window->display();
}

bool Game::getEndGame()
{
	return this->endgame;
}

void Game::initFont()
{
	if (!this->font.loadFromFile("../Poppins-Regular.ttf"))
	{
		std::cout << "ERROR UPON LOADING FONT\n";
	}
}

void Game::initText()
{
	this->uitext.setFont(this->font);
	this->uitext.setCharacterSize(13);
	this->uitext.setFillColor(sf::Color::White);
	this->uitext.setString("none");
}

void Game::updateText()
{
	std::stringstream ss;

	ss << "Points" << this->points;

	this->uitext.setString(ss.str());
}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uitext);
}