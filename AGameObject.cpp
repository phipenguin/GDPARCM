#include "AGameObject.h"

AGameObject::AGameObject(String name)
{
	this->name = name;
}

AGameObject::~AGameObject()
{
	delete this->texture;
	delete this->sprite;
}

void AGameObject::initialize()
{
}

void AGameObject::processInput(sf::Event event)
{
}

void AGameObject::update(sf::Time delta_time)
{
}

void AGameObject::draw(sf::RenderWindow* target_window)
{
	if (this->sprite != nullptr) {
		this->sprite->setPosition(this->posX, this->posY);
		this->sprite->setScale(this->scaleX, this->scaleY);
		target_window->draw(*this->sprite);
	}
}

AGameObject::String AGameObject::getName()
{
	return this->name;
}

sf::FloatRect AGameObject::getLocalBounds()
{
	return this->sprite->getLocalBounds();
}

void AGameObject::setPosition(float x, float y)
{
	this->posX = x;
	this->posY = y;

	if (this->sprite != nullptr)
	{
		this->sprite->setPosition(this->posX, this->posY);
	}
}

sf::Vector2f AGameObject::getPosition()
{
	return this->sprite->getPosition();
}

void AGameObject::setScale(float x, float y)
{
	this->scaleX = x;
	this->scaleY = y;

	if (this->sprite != nullptr)
	{
		this->sprite->setScale(this->scaleX, this->scaleY);
	}
}

sf::Vector2f AGameObject::getScale()
{
	return this->sprite->getScale();
}