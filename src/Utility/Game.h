#pragma once

#include <Utility/Enemy.h>
#include <atomic>
#include <ctime>
#include <sstream>
#include <thread>
#include <vector>

#define TEXTURE_IDLE 0
#define TEXTURE_STARTED 1
#define TEXTURE_READY 2

#define apple 0
#define banana 1
#define lemon 2
#define pear 3
#define orange 4

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

	//Enemies
	float spawnTimer;
	float spawnTimerMax;
	unsigned int maxEnemies;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	float enemySpeed;
	std::vector<Enemy*> enemies;

	//reosources
	sf::Font font;

	//text
	sf::Text uitext;

	//game logic
	bool mouseHeld;
	int points;
	int playerHealth;
	bool endgame;
	std::vector<int> requestTypes;

	void initVariables();
	void initWindow();
	void initEnemy();
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
	void updateMousePos();
	void pollEvents();

	void update();
	void updatePlayer();
	void updateEnemies();
	void updateText();
	void pointSystem(Enemy* enemy, unsigned counter);

	void renderText(sf::RenderTarget& target);
	void renderEnemies(sf::RenderTarget& target);
	void render();

	//ATOMICO PARA THREAD DE TEXTURA
	std::atomic_int textureState;
};