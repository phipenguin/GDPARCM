#include "IconObject.h"
#include "TextureManager.h"
#include <iostream>

IconObject::IconObject(String name, int texture_index) : AGameObject(name)
{
	this->texture_index = texture_index;
}

void IconObject::initialize()
{
	AGameObject::initialize();

	std::cout << "Icon declared as " << this->getName() << "\n";

	this->sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::getInstance()->getStreamTextureFromList(this->texture_index);
	this->sprite->setTexture(*texture);
}

void IconObject::processInput(sf::Event event)
{
	AGameObject::processInput(event);
}

void IconObject::update(sf::Time delta_time)
{
	AGameObject::update(delta_time);
	//std::cout << "Icon update for " << this->getName() << "\n";
}
