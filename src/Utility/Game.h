#pragma once

#include <Utility/Enemy.h>
#include <ctime>
#include <sstream>
#include <vector>

/*
	Classe de engine do jogo, wrapper.
*/

class Game
{
private:
	//Variables
	//Window
	sf::RenderWindow* window;
	sf::Event event;
	sf::VideoMode videomode;

	//mouse position
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//game objects
	sf::RectangleShape enemy;
	std::vector<sf::RectangleShape> enemies;
	sf::Texture textureSheet;
	std::vector<sf::Texture> textures;
	Enemy* enemyy;
	std::vector<Enemy> enemiess;

	//reosources
	sf::Font font;

	//text
	sf::Text uitext;

	//game logic
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	unsigned int maxEnemies;
	int points;
	int playerHealth;
	bool endgame;

	void initVariables();
	void initWindow();
	void initEnemies();
	void initTexture();
	void initText();
	void initFont();

public:
	// Constructors and Destructors
	Game();
	virtual ~Game();

	//Acessors
	bool running();
	bool getEndGame();

	//Functions
	void spawnEnemies();
	void updateMousePos();
	void pollEvents();

	void update();
	void updatePlayer();
	void updateEnemies();
	void updateText();

	void renderText(sf::RenderTarget& target);
	void renderEnemies(sf::RenderTarget& target);
	void render();
};