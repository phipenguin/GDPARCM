#include "TextureDisplay.h"
#include "Game.h"
#include "TextureManager.h"
#include "GameObjectManager.h"
#include "IconObject.h"
#include <iostream>

TextureDisplay::TextureDisplay() : AGameObject("TEXTURE_DISPLAY")
{
}

void TextureDisplay::initialize()
{
}

void TextureDisplay::processInput(sf::Event event)
{
	start_playing = true;
}

void TextureDisplay::update(sf::Time delta_time)
{
	this->ticks += Game::getInstance()->TIME_PER_FRAME.asMilliseconds();

	if (this->streaming_type == StreamingType::BATCH_LOAD && !this->started_streaming && this->ticks > this->STREAMING_LOAD_DELAY)
	{
		this->started_streaming = true;
		this->ticks = 0.0f;
		TextureManager::getInstance()->loadStreamingAssets();
	}
	else if (this->streaming_type == StreamingType::SINGLE_STREAM && this->ticks > this->STREAMING_LOAD_DELAY)
	{
		this->ticks = 0.0f;
		TextureManager::getInstance()->loadSingleStreamAsset(this->num_displayed, this);
		this->num_displayed++;
	}

	if (start_playing)
	{
		this->play_ticks += delta_time.asSeconds();

		if (frame_index >= icon_list.size())
		{
			start_playing = false;
		}
		else
		{
			if (this->play_ticks > 0.065f)
			{
				GameObjectManager::getInstance()->addObject(icon_list[frame_index]);
				this->play_ticks = 0;
				frame_index++;
			}
		}
	}
}

void TextureDisplay::onFinishedExecution()
{
	guard.lock();
	Game::getInstance()->num_of_thread_finished++;
	this->spawnObject();
	guard.unlock();
}

void TextureDisplay::spawnObject()
{
	String object_name = "ICON_" + std::to_string(this->icon_list.size());
	auto* icon_object = new IconObject(object_name, static_cast<int>(this->icon_list.size()));

	this->icon_list.push_back(icon_object);

	//set position
	//int IMG_WIDTH = 68; int IMG_HEIGHT = 68;
	//float x = this->column_grid * IMG_WIDTH;
	//float y = this->row_grid * IMG_HEIGHT;
	icon_object->setPosition(0, 0);

	//std::cout << "Set position: " << x << " " << y << std::endl;

	//this->column_grid++;
	//if (this->column_grid == this->MAX_COLUMN)
	//{
	//	this->column_grid = 0;
	//	this->row_grid++;
	//}

	//GameObjectManager::getInstance()->addObject(icon_object);
}
