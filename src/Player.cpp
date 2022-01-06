#include "Utility/Player.h"
#include "Utility/stdfax.h"

void Player::initTexture()
{
}

void Player::initSprite()
{}

Player::Player()
{
	this->initSprite();
	this->initTexture();
}

Player::~Player()
{
}

void Player::update()
{
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}