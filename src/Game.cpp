#include "Utility/Game.h"

//inicializando thread para o processo de textura. É um pointeiro, pois no c++ o thread se desmanhca em um final dee escopo.
static std::thread* textureThread = nullptr;

//Constructors  and Destructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initEnemy();
	this->initFont();
	this->initText();
	this->mouseHeld = false;

	this->textureState.store(TEXTURE_IDLE);
}

Game::~Game()
{
	delete this->window;
}

//private
void Game::initVariables()
{
	this->window = nullptr;
	this->points = 0;
	this->playerHealth = 10;
	this->enemySpawnTimerMax = 20.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 8;
	this->endgame = false;
	this->requestTypes = { 1, 3 };
	this->mouseHeld = false;
}

void Game::initWindow()
{
	this->videomode.height = 720;
	this->videomode.width = 1280;
	this->window = new sf::RenderWindow(this->videomode, "Task cruncher", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::initEnemy()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;
}

void Game::initFont()
{
	if (!this->font.loadFromFile("src/Fonts/Poppins-Regular.ttf"))
	{
		std::cout << "ERROR UPON LOADING FONT\n";
	}
}

void Game::initText()
{
	this->uitext.setFont(this->font);
	this->uitext.setCharacterSize(24);
	this->uitext.setFillColor(sf::Color::White);
	this->uitext.setString("none");
}

//accessors
bool Game::running()
{
	return this->window->isOpen();
}

//functions

void Game::update()
{
	this->pollEvents();

	if (this->endgame == false)
	{
		this->updateEnemies();
		this->updateMousePos();
		this->updateText();
	}

	//endgame condititon
	if (this->playerHealth <= 0)
		this->endgame = true;
}

void Game::render()
{

	this->window->clear();

	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	this->renderText(*this->window);

	this->window->display();
}

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

void Game::pointSystem(Enemy* enemy, unsigned counter)
{
	//check if clicked
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{

		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			if (enemy->getBounds().contains(this->mousePosView))
			{
				//pontuação
				this->enemies.erase(this->enemies.begin() + counter);
				if (std::find(this->requestTypes.begin(), this->requestTypes.end(), enemy->getType()) != this->requestTypes.end())
				{
					this->points += 1;
				}
				else
				{
					this->points -= 1;
				}
			}
		}
	}
	else
	{
		this->mouseHeld = false;
	}
}

void Game::updateEnemies()
{
	// atualiza o tempo de spawn e spawna inimigos.
	this->enemySpawnTimer -= 0.5;

	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			Enemy* enemy = new Enemy(rand() % this->window->getSize().x - 20.f, 0.f);
			//começando thread de textura
			std::cout << "textstate: " << this->textureState.load() << "\n";
			textureThread = new std::thread(&Enemy::frutalize, enemy, &this->textureState);
			std::cout << "textstateafter: " << this->textureState.load() << "\n";

			if (this->textureState.load() == TEXTURE_READY)
			{
				std::cout << "here\n";
				this->enemies.push_back(enemy);
				this->enemySpawnTimer = 0.f;
				//TERMINOU USO DA TEXTURA, VOLTA O ESTADO
				this->textureState.store(TEXTURE_IDLE);
				textureThread->join();
				delete textureThread;
				textureThread = nullptr;
			}
		}
		else
			this->enemySpawnTimer += 1.f;
	}

	//update
	unsigned counter = 0;
	for (auto* enemy : this->enemies)
	{
		enemy->update();

		//if the enemy is in the bottom
		if (enemy->getPosY() > this->window->getSize().y)
		{
			if (std::find(this->requestTypes.begin(), this->requestTypes.end(), enemy->getType()) != this->requestTypes.end())
			{
				this->playerHealth -= 1;
			}

			this->enemies.erase(this->enemies.begin() + counter);
		}
		counter++;
	}

	//check if clicked
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{

		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;

			counter = 0;
			for (auto* enemy : this->enemies)
			{
				std::cout << "bounds" << enemy->getBounds().contains(this->mousePosView) << "\n";
				if (enemy->getBounds().contains(this->mousePosView))
				{
					//pontuação
					this->enemies.erase(this->enemies.begin() + counter);
					if (std::find(this->requestTypes.begin(), this->requestTypes.end(), enemy->getType()) != this->requestTypes.end())
					{
						this->points += 1;
					}
					else
					{
						this->points -= 1;
					}
				}
				counter++;
			}
		}
	}
	else
	{
		this->mouseHeld = false;
	}
}

void Game::updateText()
{
	std::stringstream ss;

	ss << "Pontos: " << this->points << "\n"
	   << "Vida: " << this->playerHealth;

	for (auto fruit : this->requestTypes)
	{
		switch (fruit)
		{
			default:
				break;
			case 0:
				ss << "\nMaca\n";
				break;
			case 1:
				ss << "\nBanana\n";
				break;
			case 2:
				ss << "\nLaranja\n";
				break;
			case 3:
				ss << "\nLimao\n";
				break;
			case 4:
				ss << "\nPera\n";
				break;
		}
	}

	this->uitext.setString(ss.str());
}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uitext);
}

bool Game::getEndGame()
{
	return this->endgame;
}
