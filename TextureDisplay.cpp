#include "TextureDisplay.h"
#include "Game.h"
#include "TextureManager.h"
#include "GameObjectManager.h"
#include "IconObject.h"
#include <iostream>

TextureDisplay::TextureDisplay(): AGameObject("TEXTURE_DISPLAY")
{
}

void TextureDisplay::initialize()
{
	AGameObject::initialize();
}

void TextureDisplay::processInput(sf::Event event)
{
	AGameObject::processInput(event);
}

void TextureDisplay::update(sf::Time deltaTime)
{
	AGameObject::update(deltaTime);
	this->ticks += Game::getInstance()->TIME_PER_FRAME.asMilliseconds();

	if (this->ticks >= 200.0f) {
		if (static_cast<int>(this->iconList.size()) < TextureManager::getInstance()->streaming_asset_count)
		{
			TextureManager::getInstance()->loadSingleStreamAsset(static_cast<int>(this->iconList.size()));
			spawnObject();
		}
		this->ticks = 0.0f;
	}
}

void TextureDisplay::spawnObject()
{
	String object_name = "Icon_" + std::to_string(this->iconList.size());
	auto* icon_object = new IconObject(object_name, static_cast<int>(this->iconList.size()));

	this->iconList.push_back(icon_object);

	//set position
	int IMG_WIDTH = 68; int IMG_HEIGHT = 68;
	float x = this->columnGrid * IMG_WIDTH;
	float y = this->rowGrid * IMG_HEIGHT;
	icon_object->setPosition(x, y);

	std::cout << "Set position: " << x << " " << y << std::endl;

	this->columnGrid++;
	if (this->columnGrid == this->MAX_COLUMN)
	{
		this->columnGrid = 0;
		this->rowGrid++;
	}

	GameObjectManager::getInstance()->addObject(icon_object);
}