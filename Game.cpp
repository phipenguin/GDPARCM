﻿#include "Game.h"
#include "BGObject.h"
#include "FPSCounter.h"
#include "GameObjectManager.h"
#include "TextureDisplay.h"
#include "TextureManager.h"

const sf::Time Game::TIME_PER_FRAME = sf::seconds(1.f / 60.f);

Game* Game::shared_instance = nullptr;

Game* Game::getInstance()
{
	if (shared_instance == nullptr) 
		shared_instance = new Game();

	return shared_instance;
}

void Game::run()
{
	sf::Clock clock;
	sf::Time prevTime = clock.getElapsedTime();
	sf::Time currTime = sf::Time::Zero;

	while (this->main_window.isOpen())
	{
		++frames;
		currTime = clock.getElapsedTime();
		float deltaTime = currTime.asSeconds() - prevTime.asSeconds();
		//this->fps = floor(1.0f / deltaTime);
		this->fps = frames / deltaTime;

		processEvents();
		update(sf::seconds(1/fps));
		render();
	}
}

float Game::getFPS()
{
	return this->fps;
}

Game::Game() : main_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "GDPARCM", sf::Style::Close)
{
	shared_instance = this;
	this->main_window.setFramerateLimit(60);

	TextureManager::getInstance()->loadFromAssetList();

    //initialize GOs/Textures/...
	BGObject* bg_object = new BGObject("BG_OBJECT");
	GameObjectManager::getInstance()->addObject(bg_object);

	TextureDisplay* display = new TextureDisplay();
	GameObjectManager::getInstance()->addObject(display);

	FPSCounter* fps_counter = new FPSCounter();
	GameObjectManager::getInstance()->addObject(fps_counter);
}

void Game::render()
{
	this->main_window.clear();
	GameObjectManager::getInstance()->draw(&this->main_window);
	this->main_window.display();
}

void Game::processEvents()
{
	sf::Event event;
	while (this->main_window.pollEvent(event))
	{
		switch (event.type)
		{
			default: 
				GameObjectManager::getInstance()->processInput(event);
				break;
			case sf::Event::Closed:
				this->main_window.close();
				break;

		}
	}
}

void Game::update(sf::Time elapsedTime)
{
	GameObjectManager::getInstance()->update(elapsedTime);
}