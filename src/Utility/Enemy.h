#pragma once

class Enemy
{
private:
	sf::RectangleShape shape;
	sf::Texture textureSheet;
	int type;

	void initTexture();
	void initShape();

public:
	Enemy();
	virtual ~Enemy();

	//Functions
	void spawn();
	void update();
	void render(sf::RenderTarget& target);
};