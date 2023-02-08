#include "FPSCounter.h"
#include "Game.h"
#include <iostream>

FPSCounter::FPSCounter() : AGameObject("FPSCounter")
{
}

FPSCounter::~FPSCounter()
{
	delete this->stats_text->getFont();
	delete this->stats_text;
	AGameObject::~AGameObject();
}

void FPSCounter::initialize()
{
	sf::Font* font = new sf::Font();
	font->loadFromFile("Media/Fonts/Sansation.ttf");

	this->stats_text = new sf::Text();
	this->stats_text->setFont(*font);
	this->stats_text->setPosition(Game::getInstance()->WINDOW_WIDTH - 150, Game::getInstance()->WINDOW_HEIGHT - 70);
	this->stats_text->setOutlineColor(sf::Color(1.0f, 1.0f, 1.0f));
	this->stats_text->setOutlineThickness(2.5f);
	this->stats_text->setCharacterSize(35);

	std::cout << "FPSCounter declared as " << this->getName() << "\n";
}

void FPSCounter::processInput(sf::Event event)
{
}

void FPSCounter::update(sf::Time delta_time)
{
	this->updateFPS(delta_time);
}

void FPSCounter::draw(sf::RenderWindow* target_window)
{
	AGameObject::draw(target_window);

	if (this->stats_text != nullptr)
		target_window->draw(*this->stats_text);
}

void FPSCounter::updateFPS(sf::Time elapsed_time)
{
	int curr_fps;
	this->update_time += elapsed_time;

	if (this->update_time >= sf::seconds(0.25f)) {
		curr_fps = floor(Game::getInstance()->getFPS());  // NOLINT(clang-diagnostic-float-conversion)
		if (curr_fps > 60)
		{
			curr_fps = 60;
		}
		std::string fps_string = std::to_string(curr_fps);
		this->stats_text->setString("FPS: " + fps_string);
		this->update_time = sf::seconds(0.0f);
	}
}