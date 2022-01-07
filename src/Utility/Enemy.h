#pragma once

#define apple 0
#define banana 1
#define lemon 2
#define pear 3
#define orange 4

class Enemy
{
private:
	void initTexture();
	void initShape();
	void initVariables();

	sf::RectangleShape shape;
	sf::Texture textureSheet;

	int type;

public:
	Enemy(float x, float y);
	virtual ~Enemy();

	//acessors
	const sf::FloatRect getBounds() const;
	float getPosY();
	int getType();

	//Functions
	void setToWaiting();
	void frutalize(std::atomic_int* textureState);
	void update();
	void render(sf::RenderTarget* target);
};