#pragma once
#include <Utility/Enemy.h>
#include <sstream>

void Enemy::initTexture()
{
	//initializes type and texture
	this->type = rand() % 5;
	std::stringstream ss;
	switch (this->type)
	{
		default:
			break;
		case 0:
			while (!this->textureSheet.loadFromFile(ss.str()))
			{
				ss << "src/Images/apple" << rand() % 5 << ".png";
			}
			break;
		case 1:
			while (!this->textureSheet.loadFromFile(ss.str()))
			{
				ss << "src/Images/banana" << rand() % 5 << ".png";
			}
			break;
		case 2:
			while (!this->textureSheet.loadFromFile(ss.str()))
			{
				ss << "src/Images/lemon" << rand() % 5 << ".png";
			}
			break;
		case 3:
			while (!this->textureSheet.loadFromFile(ss.str()))
			{
				ss << "src/Images/pear" << rand() % 5 << ".png";
			}
			break;
		case 4:
			while (!this->textureSheet.loadFromFile(ss.str()))
			{
				ss << "src/Images/orange" << rand() % 5 << ".png";
			}
			break;
	}
}

void Enemy::initShape()
{
	this->shape.setTexture(&this->textureSheet);
	this->shape.setTextureRect(sf::IntRect(10, 10, 100, 100));
}

Enemy::Enemy()
{
	this->initTexture();
	this->initShape();
}

Enemy::~Enemy()
{
}

void Enemy::spawn()
{
}