#pragma once

class Player
{
private:
	sf::Sprite sprite;
	sf::Texture textureSheet;
	void initTexture();
	void initSprite();

	//movement

public:
	Player();
	virtual ~Player();

	//functions
	void update();
	void render(sf::RenderTarget& target);
};