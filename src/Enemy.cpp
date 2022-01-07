#include <Utility/Enemy.h>
#include <Utility/Game.h>
#include <atomic>
#include <sstream>
#include <thread>

void Enemy::initTexture()
{
	//initializes texture
	std::stringstream ss;
	sf::Image im;
	//init rand
	std::srand(static_cast<unsigned>(time(NULL)));

	switch (this->type)
	{
		default:
			break;
		case 0:
			ss << "src/Images/apple" << rand() % 5 << ".png";
			this->textureSheet.loadFromFile(ss.str());
			break;
		case 1:
			ss << "src/Images/banana" << rand() % 4 << ".png";
			this->textureSheet.loadFromFile(ss.str());
			break;
		case 2:
			ss << "src/Images/orange" << rand() % 3 << ".png";
			this->textureSheet.loadFromFile(ss.str());
			break;
		case 3:
			ss << "src/Images/lemon" << rand() % 4 << ".png";
			this->textureSheet.loadFromFile(ss.str());
			break;
		case 4:
			ss << "src/Images/pear" << rand() % 3 << ".png";
			this->textureSheet.loadFromFile(ss.str());
			break;

			/*
		case 0:
			while (!this->textureSheet.loadFromFile(ss.str()))
			{
				ss << "src/Images/apple" << rand() % 5 << ".png";
				std::cout << ss.str() << " this\n";
			}
			break;
		case 1:
			while (!this->textureSheet.loadFromFile(ss.str()))
			{
				ss << "src/Images/banana" << rand() % 4 << ".png";
			}
			break;
		case 2:
			while (!this->textureSheet.loadFromFile(ss.str()))
			{
				ss << "src/Images/lemon" << rand() % 4 << ".png";
			}
			break;
		case 3:
			while (!this->textureSheet.loadFromFile(ss.str()))
			{
				ss << "src/Images/pear" << rand() % 3 << ".png";
			}
			break;
		case 4:
			while (!this->textureSheet.loadFromFile(ss.str()))
			{
				ss << "src/Images/orange" << rand() % 3 << ".png";
			}
			break;
			*/
	}
}

void Enemy::initShape()
{
	this->shape.setTexture(&this->textureSheet);
	//this->shape.setTextureRect(sf::IntRect(50, 50, 100, 100));
	this->shape.setFillColor(sf::Color::White);
	this->shape.setSize(sf::Vector2f(150.f, 150.f));
}

void Enemy::initVariables()
{
	//init rand
	std::srand(static_cast<unsigned>(time(NULL)));
	this->type = rand() % 5;
}

Enemy::Enemy(float x, float y)
{
	this->initVariables();
	this->initTexture();
	this->initShape();
	this->shape.setPosition(x, y);
}

Enemy::~Enemy()
{
}

//Accessors
const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

float Enemy::getPosY()
{
	return this->shape.getPosition().y;
}

int Enemy::getType()
{
	return this->type;
}
//Functions

void Enemy::setToWaiting()
{
	this->shape.setFillColor(sf::Color::Red);
}

void Enemy::frutalize(std::atomic_int* textureState)
{
	initTexture();
	initShape();
	textureState->store(TEXTURE_READY);
}

void Enemy::update()
{
	this->shape.move(0.f, 3.f);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
