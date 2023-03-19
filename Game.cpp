#include "Game.h"
#include "BGObject.h"
#include "P5IconObject.h"
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

	P5IconObject* p5_icon_object = new P5IconObject("P5_ICON");
	GameObjectManager::getInstance()->addObject(p5_icon_object);

	TextureDisplay* display = new TextureDisplay();
	GameObjectManager::getInstance()->addObject(display);

	FPSCounter* fps_counter = new FPSCounter();
	GameObjectManager::getInstance()->addObject(fps_counter);

	this->loading_bar.setFillColor(sf::Color::Red);
	this->loading_bar.setPosition(this->WINDOW_WIDTH - 1920, this->WINDOW_HEIGHT - 50);
}

void Game::render()
{
	this->main_window.clear();
	GameObjectManager::getInstance()->draw(&this->main_window);

	if (!is_enter_pressed)
		this->main_window.draw(loading_bar);

	this->main_window.display();
}

void Game::processEvents()
{
	sf::Event event;
	while (this->main_window.pollEvent(event))
	{
		switch (event.type)
		{
			//default: 
			//	GameObjectManager::getInstance()->processInput(event);
			//	break;
			case sf::Event::Closed:
				this->main_window.close();
				break;
		}

		if (is_finished_loading_everything)
		{
			if (!is_enter_pressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{
					is_enter_pressed = true;
					GameObjectManager::getInstance()->processInput(event, "TEXTURE_DISPLAY");
				}
			}
		}
	}
}

void Game::update(sf::Time elapsedTime)
{
	GameObjectManager::getInstance()->update(elapsedTime);

	if (this->num_of_thread_finished <= TextureManager::getInstance()->streaming_asset_count)
		this->loading_bar.setSize(sf::Vector2f(this->num_of_thread_finished * (this->WINDOW_WIDTH / TextureManager::getInstance()->streaming_asset_count), 20.0f));
	else
	{
		this->is_finished_loading_everything = true;
		this->loading_bar.setSize(sf::Vector2f(this->WINDOW_WIDTH, 20.0f));
	}
}