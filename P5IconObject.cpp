#include "P5IconObject.h"
#include "TextureManager.h"
#include "Game.h"
#include <iostream>

P5IconObject::P5IconObject(String name) : AGameObject(name)
{
}

void P5IconObject::initialize()
{
	AGameObject::initialize();
	std::cout << "P5IconObject declared as " << this->getName() << "\n";

	//assign texture
	this->sprite = new sf::Sprite();
	this->texture = TextureManager::getInstance()->getFromTextureMap("TakeYourTime", 0);

	this->texture->setRepeated(false);
	this->sprite->setTexture(*texture);
	sf::Vector2u textureSize = this->sprite->getTexture()->getSize();

	this->setPosition(Game::getInstance()->WINDOW_WIDTH - 210, Game::getInstance()->WINDOW_HEIGHT - 325);
	this->setScale(0.5f, 0.5f);
}

void P5IconObject::processInput(sf::Event event)
{
	AGameObject::processInput(event);
}

void P5IconObject::update(sf::Time delta_time)
{
	AGameObject::update(delta_time);

	this->ticks += delta_time.asSeconds();

	if (this->ticks > 5.0f)
	{
		if (index == 0)
		{
			index = 1;
			this->ticks = 0.0f;
			can_change_icon = true;
		}
		else
		{
			index = 0;
			this->ticks = 0.0f;
			can_change_icon = true;
		}
	}

	if (index == 0 && can_change_icon)
	{
		this->sprite = new sf::Sprite();
		this->texture = TextureManager::getInstance()->getFromTextureMap("TakeYourTime", 0);

		this->texture->setRepeated(false);
		this->sprite->setTexture(*texture);
		sf::Vector2u textureSize = this->sprite->getTexture()->getSize();

		this->setPosition(Game::getInstance()->WINDOW_WIDTH - 210, Game::getInstance()->WINDOW_HEIGHT - 325);
		this->setScale(0.5f, 0.5f);
	}
	else if (index == 1 && can_change_icon)
	{
		this->texture = TextureManager::getInstance()->getFromTextureMap("TakeYourHeart", 0);

		this->texture->setRepeated(false);
		this->sprite->setTexture(*texture);
		sf::Vector2u textureSize = this->sprite->getTexture()->getSize();

		this->sprite->setTextureRect(sf::IntRect(0, 0, 499, 538));
		this->setPosition(Game::getInstance()->WINDOW_WIDTH - 280, Game::getInstance()->WINDOW_HEIGHT - 330);
	}
}
