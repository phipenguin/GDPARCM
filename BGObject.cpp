#include "BGObject.h"
#include <iostream>
#include "Game.h"
#include "TextureManager.h"

BGObject::BGObject(std::string name) : AGameObject(name)
{
}

void BGObject::initialize()
{
	AGameObject::initialize();
	std::cout << "BGObject declared as " << this->getName() << "\n";

	//assign texture
	this->sprite = new sf::Sprite();
	//this->texture = TextureManager::getInstance()->getFromTextureMap("Desert", 0);
	this->texture = TextureManager::getInstance()->getFromTextureMap("Daytime", 0);

	this->texture->setRepeated(true);
	this->sprite->setTexture(*texture);
	sf::Vector2u textureSize = this->sprite->getTexture()->getSize();

	//make BG height x k to emulate repeating BG.
	this->sprite->setTextureRect(sf::IntRect(0, 0, Game::getInstance()->WINDOW_WIDTH, Game::getInstance()->WINDOW_HEIGHT * 8));
	this->setPosition(0, -Game::getInstance()->WINDOW_HEIGHT * 7);

}

void BGObject::processInput(sf::Event event)
{
	AGameObject::processInput(event);
}

void BGObject::update(sf::Time delta_time)
{
	AGameObject::update(delta_time);
	//make BG scroll slowly
	//sf::Vector2f position = this->getPosition();
	//position.y += this->SPEED_MULTIPLIER * delta_time.asSeconds();
	//this->setPosition(position.x, position.y);

	//sf::Vector2f localPos = this->sprite->getPosition();
	//if (localPos.y * delta_time.asSeconds() > 0) {
	//	//reset position
	//	this->setPosition(0, -Game::WINDOW_HEIGHT * 7);
	//}
	this->ticks += delta_time.asSeconds();

	if (this->ticks > 5.0f)
	{
		if (index == 0)
		{
			index = 1;
			this->ticks = 0.0f;
			can_change_bg = true;
		}
		else
		{
			index = 0;
			this->ticks = 0.0f;
			can_change_bg = true;
		}
	}

	if (index == 0 && can_change_bg)
	{
		this->texture = TextureManager::getInstance()->getFromTextureMap("Daytime", 0);

		this->texture->setRepeated(true);
		this->sprite->setTexture(*texture);
		sf::Vector2u textureSize = this->sprite->getTexture()->getSize();

		this->sprite->setTextureRect(sf::IntRect(0, 0, Game::getInstance()->WINDOW_WIDTH, Game::getInstance()->WINDOW_HEIGHT * 8));
		this->setPosition(0, -Game::getInstance()->WINDOW_HEIGHT * 7);
	}
	else if (index == 1 && can_change_bg)
	{
		this->texture = TextureManager::getInstance()->getFromTextureMap("Nighttime", 0);

		this->texture->setRepeated(true);
		this->sprite->setTexture(*texture);
		sf::Vector2u textureSize = this->sprite->getTexture()->getSize();

		this->sprite->setTextureRect(sf::IntRect(0, 0, Game::getInstance()->WINDOW_WIDTH, Game::getInstance()->WINDOW_HEIGHT * 8));
		this->setPosition(0, -Game::getInstance()->WINDOW_HEIGHT * 7);
	}
}